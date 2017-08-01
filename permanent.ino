//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              Pompes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pompes()
{

  if (rtc.hour() >= depart_filtration && rtc.hour() < (depart_filtration + duree_filtration)) {
    filtrationON = 1;
  }
  else {
    filtrationON = 0;
  }
  if (InitfiltrationON != filtrationON) {
    mqtt_FiltrationStatut();
    InitfiltrationON = filtrationON;
  }

  if (rtc.hour() >= depart_robot && rtc.hour() < (depart_robot + duree_robot)) {
    digitalWrite(relais_robot, LOW);
    robotON = 1;
  }
  else {
    digitalWrite(relais_robot, HIGH);
    robotON = 0;
  }

  if ((ModeFiltration == 1) && (filtrationON == 1)) { // Si le mode choisi est Auto, la durée de filtration est la moitié de la température de l'eau
    duree_filtration = TEau / 2;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              MQTT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mqtt_SendSwitch(int idx, String Etat, int Level)
{
      mqtt = "{\"command\": \"switchlight\", \"idx\": " + (String)idx + ", \"switchcmd\": \"" + Etat + "\", \"level\": " + (String)Level + "}";
      const char *msgmqtt  = mqtt.c_str();
      client.publish(topicin, msgmqtt);
}


void mqtt_Send(int idx, String svalue)
{
      mqtt = "{\"idx\" : " + (String)idx + ", \"nvalue\" : 0,  \"svalue\" : " + svalue + "}";
      const char *msgmqtt  = mqtt.c_str();
      client.publish(topicin, msgmqtt);  
}

void mqtt_FiltrationMode() {
  switch (ModeFiltration)
  {
    case 0 :
      level = 10;
      break;
    case 1 :
      level = 20;
      break;
  }
  //Mqtt Mode de filtration Pompe (Manu ou Auto)
  mqtt_SendSwitch(64, "On", level);
}

void mqtt_FiltrationStatut() {
  if (filtrationON == 0) {
    strcpy(EtatFiltration,"Off");
  } else {
    strcpy(EtatFiltration,"On");
  }
  //Mqtt Etat pompe filtration
  mqtt_SendSwitch(76, EtatFiltration, 100);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                            Hors Gel
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void horsgel()
{
  switch (chk)
  {
    case DHTLIB_OK:
      if (temp <= (conshorsgel - 0.1)) {
        horsgelON = 1;
      }
      else if (temp >= (conshorsgel + 0.1)) {
        horsgelON = 0;
      }
      break;
    case DHTLIB_ERROR_CHECKSUM:
      dbSerialPrintln(F("Erreur DHT regul Checksum,\t"));
      break;
    case DHTLIB_ERROR_TIMEOUT:
      dbSerialPrintln(F("Erreur DHT regul Time out,\t"));
      horsgelON = 1;
      break;
    default:
      dbSerialPrintln(F("Erreur DHT regul Unknown error,\t"));
      break;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Mesure température systeme (Via le RTC DS3232)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void temp_sytem() {
  union int16_byte {
    int i;
    byte b[2];
  } rtcTemp;

  Wire.beginTransmission(DS3231_RTC_ADDR);
  Wire.write(DS3231_TEMP_MSB);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_RTC_ADDR, 2);
  rtcTemp.b[1] = Wire.read();
  rtcTemp.b[0] = Wire.read();
  long tempC100 = (rtcTemp.i >> 6) * 25;    //degrees celsius times 100
  val_temp_system = tempC100 / 100;
  //Mqtt Envoi température système
  if((rtc.minute()%5==0) && (rtc.second() == 0)) {
    mqtt_Send(106,"\"" + (String)val_temp_system + "\"");
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                Ecriture SDcard
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SDCard() {

  //Ouverture du fichier
  fichierSD = SD.open("log.txt", FILE_WRITE);
  if (fichierSD) {
    dbSerialPrintln(F("Ecriture Data"));
    fichierSD.print(rtc.hour());
    fichierSD.print(":");
    fichierSD.print(rtc.minute() / 10);
    fichierSD.println(rtc.minute() % 10);
    fichierSD.print("Ph:");
    fichierSD.println(ph_value_float);
    fichierSD.print("Redox:");
    fichierSD.println(redox_value_float);
    fichierSD.println("   ");
    fichierSD.close();
  }

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                Injection chlore
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void injection_chlore() {
  ///////////////////// Injection, consigne 740 /////////////////
  // si 670 =< redox <740 (20% injection) Ton=120 Toff=480
  if ((filtrationON == 1) && (redox_value_float >= (seuil_redox - 70)) && (redox_value_float < seuil_redox) && (StartInjection == 0)) {
    Ton = 120;
    Toff = 480;
    StartInjection = 1;
    CycleChlore = 20;
  }
  // si 600 =< redox <670 (50% injection )Ton=300 Toff=300
  if ((filtrationON == 1) && (redox_value_float >= (seuil_redox - 140)) && (redox_value_float < (seuil_redox - 70)) && (StartInjection == 0)) {
    Ton = 300;
    Toff = 300;
    StartInjection = 1;
    CycleChlore = 50;
  }
  // si 530 =< redox <600 (75% injection) Ton=450 Toff=150
  if ((filtrationON == 1) && (redox_value_float >= (seuil_redox - 210)) && (redox_value_float < (seuil_redox - 140)) && (StartInjection == 0)) {
    Ton = 450;
    Toff = 150;
    StartInjection = 1;
    CycleChlore = 75;
  }
  // si redox <530 (100% injection) Ton=600 Toff=1
  if ((filtrationON == 1) && (redox_value_float < (seuil_redox - 210)) && (StartInjection == 0)) {
    Ton = 600;
    Toff = 1;
    StartInjection = 1;
    CycleChlore = 100;
  }
  // si redox > seuil, on stop l'injection
  if ((redox_value_float >= seuil_redox) && (StartInjection == 0)) {
    injection_chloreON = 0;
    CycleChlore = 0;
  }

  // Décompte temps injection
  if (StartInjection == 1) {
    if (Ton > 0) {
      Ton -= 1;
      injection_chloreON = 1;
    }
    if (Ton == 0) {
      Toff -= 1;
      injection_chloreON = 0;
    }
    if (Toff <= 0) {
      StartInjection = 0;
      injection_chloreON = 0;
    }
  }

  if ((val_bouton_chlore == 0) || (SecuOfaChlore == 1) || (filtrationON == 0)) { // Bouton chlore sur OFF ou sécu OFA ou pompe arrêtée, stop injection et init variables
    Ton = 0;
    Toff = 0;
    StartInjection = 0;
    injection_chloreON = 0;
    CycleChlore = 0;
  }

  // Pilotage Relais Pompe Injection chlore
  if ((((injection_chloreON == 1) && (SecuOfaChlore == 0)) || (val_bouton_chlore == 2)) && (filtrationON == 1)) {
    digitalWrite(relais_chlore, LOW);
    qte_hbdo = qte_hbdo + (debit_pompe_chlore / 3600);
  }
  else {
    digitalWrite(relais_chlore, HIGH);
  }

  //    Activation sortie buzzer
  if (SecuOfaChlore == 1) {
    digitalWrite(Buzzer, LOW);
  }
  else {
    digitalWrite(Buzzer, HIGH);
  }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                Injection Ph
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void injection_ph() {
  ///////////////////// Injection, consigne 7.4 /////////////////
  // si 7.4 < ph =<7.55 (20% injection) Ton=120 Toff=480
  if ((filtrationON == 1) && (ph_value_float <= (seuil_ph + 0.15)) && (ph_value_float > seuil_ph) && (StartInjectionPh == 0)) {
    TonPh = 120;
    ToffPh = 480;
    StartInjectionPh = 1;
    CyclePh = 20;
  }
  // si 7.55 < ph =<7.70 (50% injection )Ton=300 Toff=300
  if ((filtrationON == 1) && (ph_value_float <= (seuil_ph + 0.30)) && (ph_value_float > (seuil_ph + 0.15)) && (StartInjectionPh == 0)) {
    TonPh = 300;
    ToffPh = 300;
    StartInjectionPh = 1;
    CyclePh = 50;
  }
  // si 7.70 < ph =<7.85 (75% injection) Ton=450 Toff=150
  if ((filtrationON == 1) && (ph_value_float <= (seuil_ph + 0.45)) && (ph_value_float > (seuil_ph + 0.30)) && (StartInjectionPh == 0)) {
    TonPh = 450;
    ToffPh = 150;
    StartInjectionPh = 1;
    CyclePh = 75;
  }
  // si ph > 7.85  (100% injection) Ton=600 Toff=1
  if ((filtrationON == 1) && (ph_value_float > (seuil_ph + 0.45)) && (StartInjectionPh == 0)) {
    TonPh = 600;
    ToffPh = 1;
    StartInjectionPh = 1;
    CyclePh = 100;
  }
  // si ph < seuil ph  -> pas d'injection
  if ((ph_value_float <= seuil_ph) && (StartInjectionPh == 0)) {
    injection_phON = 0;
    CyclePh = 0;
  }

  // Décompte temps injection
  if (StartInjectionPh == 1) {
    if (TonPh > 0) {
      TonPh -= 1;
      injection_phON = 1;
    }
    if (TonPh == 0) {
      ToffPh -= 1;
      injection_phON = 0;
    }
    if (ToffPh <= 0) {
      StartInjectionPh = 0;
      injection_phON = 0;
    }
  }

  if ((val_bouton_ph == 0) || (SecuOfaPh == 1) || (filtrationON == 0)) { // Bouton Ph sur OFF ou sécu OFA ou pompe arrêtée, stop injection et init variables
    TonPh = 0;
    ToffPh = 0;
    StartInjectionPh = 0;
    injection_phON = 0;
    CyclePh = 0;
  }

  // Pilotage Relais Pompe Injection Ph
  if ((((injection_phON == 1) && (SecuOfaPh == 0)) || (val_bouton_ph == 2)) && (filtrationON == 1)) {
    digitalWrite(relais_ph, LOW);
    qte_hbdo_ph = qte_hbdo_ph + (debit_pompe_ph / 3600);
  }
  else {
    digitalWrite(relais_ph, HIGH);
  }

  //    Activation sortie buzzer
  if (SecuOfaPh == 1) {
    digitalWrite(Buzzer, LOW);
  }
  else {
    digitalWrite(Buzzer, HIGH);
  }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                Mesure Pression
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float encode_pressure(uint16_t pressureReading)
{
  // multiply MPa by 145.0377 to get PSI
  // the sensor has an output range of 0.5V to 4.5V for a
  // MPa range of 0~1.2MPa
  
  // TODO
  // try to remember to calibrate this against the pressure guage

  // the Amazon product description:
  // Working voltage: DC 5V;
  // Output voltage: 0.5~4.5V DC;
  // Working current: <=10mA;
  // Working pressure: 0~1.2MPa;
  // Max. pressure: 2.4MP;
  // Damage pressure: 3.0MP;

  // 0 to 5V at 10-bit resolution
  // 0.5 = 102  ==> 0.0 MPa
  // 4.5 = 922  ==> 1.2 MPa
  //  (so the 1.2 MPa range is 820 range in analog reading)

  const int minReading = 91;
  const int analogRange = 830;
  const float maxMPa = 1.2;
  const float psiPerMPa = 145.0377;
  
  float reading = constrain(pressureReading, minReading, (minReading+analogRange));
  float mpa = (reading - minReading) / analogRange * maxMPa;
  
  float psi = mpa * psiPerMPa;
  float bar = psi * 0.0689475729;

  return bar;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
