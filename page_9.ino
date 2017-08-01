/////////////////////////////////////////////////////////////////////////////////
//                          Page gestion Pompe doseuse Chlore
/////////////////////////////////////////////////////////////////////////////////

void P9_b0PopCallback(void *ptr) // Bouton page suivante (appel page 0)
{
  page11.show();
  num_page = 11;
  switch (val_bouton_ph)
  {
    case 0:
    strcpy(buffer, "OFF");
    break;
    case 1:
    strcpy(buffer, "AUTO");
    break;
    case 2:
    strcpy(buffer, "FOR.");
    break;
    }
  P11_b3.setText(buffer);
  P11_t4.setText(buffer_hour);
  P11_t6.setText(buffer_minute);
  }

void P9_b1PopCallback(void *ptr) // Bouton page précedente (appel page 3)
{
  page3.show();
  num_page = 3;
  P3_t4.setText(buffer_hour);
  P3_t6.setText(buffer_minute);
  dtostrf(conshorsgel, 5, 1, buffer);
  P3_t2.setText(buffer);

}

void P9_b2PopCallback(void *ptr) // Bouton page Réglages (page 10)
{
  page10.show();
  num_page = 10;
  dtostrf(debit_pompe_chlore, 5, 1, buffer);
  P10_t2.setText(buffer);
}


// Bouton OFF/Auto/Forcé
void P9_b3PopCallback(void *ptr)
{
  val_bouton_chlore++;
  if (val_bouton_chlore > 2){
    val_bouton_chlore = 0;
  }
  
  switch (val_bouton_chlore)
  {
    case 0:
    strcpy(buffer, "OFF");
    break;
    case 1:
    strcpy(buffer, "AUTO");
    break;
    case 2:
    strcpy(buffer, "FOR.");
    break;
    }
  EEPROM.write(addr_val_bouton_chlore, val_bouton_chlore);
  P9_b3.setText(buffer);

}

/////////////////////////////////////////////////////////////////////////////////
//                          Fonctions Diverses
/////////////////////////////////////////////////////////////////////////////////
void P9Display() 
{
    P9_n0.setValue(Ton);
    P9_n1.setValue(Toff);
    P9_n2.setValue(TpsSecuOfaChlore);
    P9_n3.setValue(CycleChlore);
    if (StartInjection == 1){
      P9_t9.setText("ON"); 
    }
    else{
      P9_t9.setText("OFF"); 
    }
    dtostrf (qte_hbdo, 3, 2, buffer);
    P9_t14.setText(buffer);
    if (SecuOfaChlore == 1){
      P9_t18.setText("ALARME OFA");
    }
    else {
      P9_t18.setText(" ");
    }
}

void timeDisplay_p9()
{
  
    memset(buffer, 0, sizeof(buffer)); 
    number = rtc.hour();
    itoa(number, buffer, 10);
    if (strcmp(buffer_hour, buffer))
    {
        P9_t4.setText(buffer);
        strcpy(buffer_hour, buffer); 
    }

    memset(buffer, 0, sizeof(buffer));
    memset(buffer_temp, 0, sizeof(buffer_temp));
    number = rtc.minute();
    itoa(number, buffer_temp, 10);
    if (rtc.minute() < 10)
    {
        strcat(buffer, "0");
    }
    strcat(buffer, buffer_temp);
    if (strcmp(buffer_minute, buffer))
    {
        P9_t6.setText(buffer);
        strcpy(buffer_minute, buffer); 
    }
    
    
    memset(buffer, 0, sizeof(buffer)); 
    memset(buffer_temp, 0, sizeof(buffer_temp)); 
    number = rtc.second();
    itoa(number, buffer_temp, 10);
    if (number < 10)
    {
        strcpy(buffer, "0");
        strcat(buffer, buffer_temp);
        if (strcmp(buffer, buffer_second))
        {
            P9_t8.setText(buffer);
            strcpy(buffer_second, buffer);
         }
    } 
    else
    {
        if (strcmp(buffer_temp, buffer_second))
        {
            P9_t8.setText(buffer_temp);
            strcpy(buffer_second, buffer_temp);
        }
    }
}
