////////////////////////////////////////////////////////////////////////////////
//                            INCLUDE
///////////////////////////////////////////////////////////////////////////////
#include <SPI.h>
#include <SD.h>
#include "Nextion.h"
#include "RTCLib.h"
#include <Ethernet.h>
#include <avr/wdt.h>
#include <NewEEPROM.h>
#include <NetEEPROM.h>
#include <EEPROMex.h>
#include <dht.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PubSubClient.h>
#include <EmonLib.h>

///////////////////////////////////////////////////////////////////////////////
//                            NEXTION Component
///////////////////////////////////////////////////////////////////////////////

// Déclaration des objets Nextion: [page id:x,component id:x, component name: "x0"]

// page 0
NexPage page0 = NexPage(0, 0, "page0");
NexButton P0_b0 = NexButton(0, 21, "b0");
NexButton P0_b1 = NexButton(0, 22, "b1");
NexButton P0_b2 = NexButton(0, 2, "b2");
NexText P0_t0 = NexText(0, 1, "t0");
NexText P0_t1 = NexText(0, 5, "t1");
NexText P0_t2 = NexText(0, 4, "t2");
NexText P0_t4 = NexText(0, 6, "t4");
NexText P0_t7 = NexText(0, 9, "t7");
NexText P0_t8 = NexText(0, 10, "t8");
NexText P0_t9 = NexText(0, 11, "t9");
NexText P0_t10 = NexText(0, 12, "t10");
NexText P0_t12 = NexText(0, 14, "t12");
NexText P0_t14 = NexText(0, 23, "t14");
NexText P0_t17 = NexText(0, 18, "t17");
NexText P0_t22 = NexText(0, 30, "t22");
NexText P0_t26 = NexText(0, 34, "t26");
NexNumber P0_n0 = NexNumber(0, 15, "n0");
NexNumber P0_n1 = NexNumber(0, 19, "n1");
NexNumber P0_n2 = NexNumber(0, 20, "n2");
NexNumber P0_n3 = NexNumber(0, 26, "n3");
NexNumber P0_n4 = NexNumber(0, 32, "n4");

// page 1
NexPage page1 = NexPage(1, 0, "page1");
NexButton P1_b0 = NexButton(1, 1, "b0_p1");
NexButton P1_b1 = NexButton(1, 2, "b1_p1");
NexButton P1_b2 = NexButton(1, 3, "b2_p1");
NexButton P1_b3 = NexButton(1, 4, "b3_p1");
NexButton P1_b4 = NexButton(1, 5, "b4_p1");
NexButton P1_b5 = NexButton(1, 6, "b5_p1");
NexButton P1_b6 = NexButton(1, 8, "b6_p1");
NexButton P1_b7 = NexButton(1, 10, "b7_p1");
NexButton P1_b8 = NexButton(1, 11, "b8_p1");
NexButton P1_b9 = NexButton(1, 12, "b9_p1");
NexButton P1_b10 = NexButton(1, 13, "b10_p1");
NexButton P1_b11 = NexButton(1, 14, "b11_p1");
NexButton P1_b12 = NexButton(1, 16, "b12_p1");
NexButton P1_b13 = NexButton(1, 17, "b13_p1");
NexButton P1_b14 = NexButton(1, 18, "b14_p1");
NexButton P1_b15 = NexButton(1, 26, "b15_p1");
NexNumber P1_n1 = NexNumber(1, 20, "n1_p1");
NexNumber P1_n3 = NexNumber(1, 22, "n3_p1");
NexNumber P1_n4 = NexNumber(1, 23, "n4_p1");
NexNumber P1_n5 = NexNumber(1, 25, "n5_p1");
NexText P1_t8 = NexText(1, 29, "t8_p1");
NexText P1_t11 = NexText(1, 30, "t11_p1");
NexText P1_t13 = NexText(1, 34, "t13_p1");

// page 2
NexPage page2 = NexPage(2, 0, "page2");
NexButton P2_b0 = NexButton(2, 6, "b0_p2");
NexButton P2_b1 = NexButton(2, 7, "b1_p2");
NexButton P2_b2 = NexButton(2, 8, "b2_p2");
NexNumber P2_n0 = NexNumber(2, 14, "n0_p2");
NexNumber P2_n1 = NexNumber(2, 15, "n1_p2");
NexNumber P2_n2 = NexNumber(2, 18, "n2_p2");
NexNumber P2_n3 = NexNumber(2, 19, "n3_p2");
NexNumber P2_n4 = NexNumber(2, 23, "n4_p2");
NexText P2_t4 = NexText(2, 9, "t4_p2");
NexText P2_t6 = NexText(2, 11, "t6_p2");
NexText P2_t8 = NexText(2, 13, "t8_p2");

// page 3
NexPage page3 = NexPage(3, 0, "page3");
NexButton P3_b0 = NexButton(3, 1, "b0_p3");
NexButton P3_b1 = NexButton(3, 2, "b1_p3");
NexButton P3_b2 = NexButton(3, 3, "b2_p3");
NexText P3_t2 = NexText(3, 12, "t2_p3");
NexText P3_t4 = NexText(3, 4, "t4_p3");
NexText P3_t6 = NexText(3, 6, "t6_p3");
NexText P3_t8 = NexText(3, 8, "t8_p3");
NexText P3_t9 = NexText(3, 14, "t9_p3");

// page 4
NexPage page4 = NexPage(4, 0, "page4");
NexButton P4_b0 = NexButton(4, 11, "b0_p4");
NexButton P4_b1 = NexButton(4, 12, "b1_p4");
NexButton P4_b2 = NexButton(4, 13, "b2_p4");
NexButton P4_b3 = NexButton(4, 14, "b3_p4");
NexButton P4_b4 = NexButton(4, 15, "b4_p4");
NexButton P4_b5 = NexButton(4, 16, "b5_p4");
NexButton P4_b6 = NexButton(4, 17, "b6_p4");
NexButton P4_b7 = NexButton(4, 18, "b7_p4");
NexButton P4_b8 = NexButton(4, 19, "b8_p4");
NexButton P4_b9 = NexButton(4, 20, "b9_p4");
NexNumber P4_n0 = NexNumber(4, 7, "n0_p4");
NexNumber P4_n1 = NexNumber(4, 8, "n1_p4");
NexNumber P4_n2 = NexNumber(4, 9, "n2_p4");
NexNumber P4_n3 = NexNumber(4, 10, "n3_p4");

// page 5
NexPage page5 = NexPage(5, 0, "page5");
NexButton P5_b0 = NexButton(5, 3, "b0_p5");
NexButton P5_b1 = NexButton(5, 4, "b1_p5");
NexButton P5_b2 = NexButton(5, 5, "b2_p5");
NexText P5_t1 = NexText(5, 2, "t1_p5");

// page 6
NexPage page6 = NexPage(6, 0, "page6");
NexButton P6_b0 = NexButton(6, 1, "b0_p6");
NexButton P6_b1 = NexButton(6, 4, "b1_p6");
NexButton P6_b2 = NexButton(6, 6, "b2_p6");
NexButton P6_b3 = NexButton(6, 10, "b3_p6");
NexText P6_t4 = NexText(6, 9, "t4_p6");
NexText P6_t6 = NexText(6, 11, "t6_p6");
NexText P6_t7 = NexText(6, 13, "t7_p6");
NexNumber P6_n0 = NexNumber(6, 7, "n0_p6");

// page 9
NexPage page9 = NexPage(9, 0, "page9");
NexButton P9_b0 = NexButton(9, 1, "b0_p9");
NexButton P9_b1 = NexButton(9, 2, "b1_p9");
NexButton P9_b2 = NexButton(9, 3, "b2_p9");
NexButton P9_b3 = NexButton(9, 20, "b3_p9");
NexNumber P9_n0 = NexNumber(9, 15, "n0_p9");
NexNumber P9_n1 = NexNumber(9, 16, "n1_p9");
NexNumber P9_n2 = NexNumber(9, 22, "n2_p9");
NexNumber P9_n3 = NexNumber(9, 23, "n3_p9");
NexText P9_t4 = NexText(9, 4, "t4_p9");
NexText P9_t6 = NexText(9, 6, "t6_p9");
NexText P9_t8 = NexText(9, 8, "t8_p9");
NexText P9_t9 = NexText(9, 14, "t9_p9");
NexText P9_t14 = NexText(9, 17, "t14_p9");
NexText P9_t18 = NexText(9, 25, "t18_p9");

// page 10
NexPage page10 = NexPage(10, 0, "page10");
NexButton P10_b0 = NexButton(10, 1, "b0_p10");
NexButton P10_b1 = NexButton(10, 2, "b1_p10");
NexButton P10_b2 = NexButton(10, 4, "b2_p10");
NexButton P10_b3 = NexButton(10, 6, "b3_p10");
NexButton P10_b4 = NexButton(10, 7, "b4_p10");
NexText P10_t2 = NexText(10, 8, "t2_p10");

// page 11
NexPage page11 = NexPage(11, 0, "page11");
NexButton P11_b0 = NexButton(11, 1, "b0_p11");
NexButton P11_b1 = NexButton(11, 2, "b1_p11");
NexButton P11_b2 = NexButton(11, 3, "b2_p11");
NexButton P11_b3 = NexButton(11, 20, "b3_p11");
NexNumber P11_n0 = NexNumber(11, 15, "n0_p11");
NexNumber P11_n1 = NexNumber(11, 16, "n1_p11");
NexNumber P11_n2 = NexNumber(11, 22, "n2_p11");
NexNumber P11_n3 = NexNumber(11, 23, "n3_p11");
NexText P11_t4 = NexText(11, 4, "t4_p11");
NexText P11_t6 = NexText(11, 6, "t6_p11");
NexText P11_t8 = NexText(11, 8, "t8_p11");
NexText P11_t9 = NexText(11, 14, "t9_p11");
NexText P11_t14 = NexText(11, 17, "t14_p11");
NexText P11_t18 = NexText(11, 25, "t18_p11");

// page 12
NexPage page12 = NexPage(12, 0, "page12");
NexButton P12_b0 = NexButton(12, 1, "b0_p12");
NexButton P12_b1 = NexButton(12, 2, "b1_p12");
NexButton P12_b2 = NexButton(12, 4, "b2_p12");
NexButton P12_b3 = NexButton(12, 6, "b3_p12");
NexButton P12_b4 = NexButton(12, 7, "b4_p12");
NexText P12_t2 = NexText(12, 8, "t2_p12");

// page 13
NexPage page13 = NexPage(13, 0, "page13");
NexButton P13_b0 = NexButton(13, 2, "b0_p13");
NexButton P13_b1 = NexButton(13, 1, "b1_p13");
NexButton P13_b2 = NexButton(13, 3, "b2_p13");
NexButton P13_b3 = NexButton(13, 4, "b3_p13");
NexText P13_t4 = NexText(13, 6, "t4_p13");
NexText P13_t6 = NexText(13, 8, "t6_p13");
NexText P13_t8 = NexText(13, 10, "t8_p13");

///////////////////////////////////////////////////////////////////////////////
//                            Définition des variables
///////////////////////////////////////////////////////////////////////////////
const int DS3231_RTC_ADDR = 0x68;
const int DS3231_TEMP_MSB = 0x11;

// Version Domogarden
const char *vers  = "3.4.1";
const char *revision  = "003";
#define DHT22_PIN A10

// Create an instance
EnergyMonitor emon1;

//-- mqtt
const char *topicin  = "domoticz/in";
const char *topicoutFiltrationDepart = "Home/Piscine/Pompe/Filtration/Depart";
const char *topicoutFiltrationDuree = "Home/Piscine/Pompe/Filtration/Duree";
const char *topicoutPompe = "Home/Piscine/Pompe";
const char *topicoutLumGarage = "Home/Garage/Lumiere";
const char *topicoutLumPiscine = "Home/Piscine/Lumiere";
String mqtt;

char EtatLum[3] = {0};
char EtatFiltration[3] = {0};

// Attribution des sorties

#define DS18B20 24
#define Buzzer 26

// Bornier inferieur
#define relais_ph 36
#define relais_filtration 29 //38
#define relais_robot 40
#define relais_chlore 42

// Bornier Lumière
#define relais_lum_garage 25
#define relais_lum_piscine 27

// *******************
//      Mesure Pression
// *******************
uint8_t pin_pression = A11;                    // Pin Capteur pression
float val_pression;
float psi_pression;
float bar_pression;

// *******************
//      Mesure PH
// *******************
uint8_t pin_ph = A8;                    // Pin Sonde pH
float ph_sensor_value = 0.0;            // Valeur Ph lue en Volt (0 to 5)
float ph_value_float = 0.0;             // valeur pH entre 0.0 to 14.0 en float
char ph_value_char[5];                  // valeur pH entre from 0 to 14 en char
int val_acide;
int val_base;
float etalon_ph_acide = 4.0;
float etalon_ph_base = 6.9;
float a_ph;
float b_ph;
float seuil_ph = 7.4;

// *******************
//      Mesure redox
// *******************
uint8_t pin_redox = A9;                 // Pin Sonde Redox
float redox_sensor_value = 0.0;         // Valeur Redox lue en Volt (0 to 5)
float redox_value_float = 0.0;          // valeur redox entre -2000 to 2000 mV en float
char redox_value_char[5];               // Valeur redox entre -2000 to 2000 en char
int redox_max = 550;                    // Definition de la valeur maxi redox
int redox_min = 500;                    // Definition de la valeur mini redox
int delta_redox = 50;
int seuil_redox = 500;
uint16_t etalon_redox = 0;

// *******************
//      Conso pompes
// *******************
double Irms = 0;
double conso = 0;

// *******************
// Pompes
// *******************
uint8_t depart_filtration;
uint8_t duree_filtration;
uint8_t depart_robot;
uint8_t duree_robot;
bool filtrationON = 0;
bool InitfiltrationON = 0;
bool robotON = 0;
int ModeFiltration = 1;
int level = 0;

// *******************
// Hors gel
// *******************
float conshorsgel = -2.5;
bool horsgelON = 0;

// *******************
// injection chlore
// *******************
bool injection_chloreON = 0;
bool StartInjection = 0;
bool SecuOfaChlore = 0;
int Ton = 0;
int Toff = 0;
int val_bouton_chlore = 0;
int ConsTpsSecuOfaChlore = 240;                     // durée avant déclenchement sécurité OFA 240 minutes = 4 heures
int TpsSecuOfaChlore;
int CycleChlore;
float debit_pompe_chlore = 2.1;          // débit en l/h
float qte_hbdo = 0;

// *******************
// injection Ph
// *******************
bool injection_phON = 0;
bool StartInjectionPh = 0;
bool SecuOfaPh = 0;
int TonPh = 0;
int ToffPh = 0;
int val_bouton_ph = 0;
int ConsTpsSecuOfaPh = 240;                     // durée avant déclenchement sécurité OFA 240 minutes = 4 heures
int TpsSecuOfaPh;
int CyclePh;
float debit_pompe_ph = 2.1;          // débit en l/h
float qte_hbdo_ph = 0;

// *******************
// Eclairage
// *******************
int val_bouton_lum_piscine = 0;
int val_bouton_lum_garage = 0;

// *******************
// Mesure de temps
// *******************
char buffer_temp[10] = {0};
char buffer_year[10] = {0};
char buffer_month[10] = {0};
char buffer_day[10] = {0};
char buffer_hour[10] = {0};
char buffer_minute[10] = {0};
char buffer_second[10] = {0};
char buffer_week[10] = {0};

int8_t settime_type = -1;
int8_t settime_up = -1;
int8_t number_settime_year = 0;
int8_t number_settime_month = 0;
int8_t number_settime_day = 0;
int8_t number_settime_hour = 0;
int8_t number_settime_minute = 0;
int8_t number_settime_week = 0;

// *******************
// adresse de stockage données en eeprom
// *******************
int addr_eeprom_redox = 310;
int addr_seuil_redox = 320;
int addr_delta_redox = 330;
int addr_depart_filtration = 340;
int addr_duree_filtration = 350;
int addr_depart_robot = 360;
int addr_duree_robot = 370;
int addr_conshorsgel = 380;
int addr_a_ph = 90;
int addr_b_ph = 100;
int addr_etalon_ph_acide = 110;
int addr_etalon_ph_base = 120;
int addr_seuil_ph = 170;
int addr_on_day = 230;
int addr_val_bouton_chlore = 237;
int addr_qte_hbdo = 238;
int addr_debit_pompe_chlore = 248;
int addr_val_bouton_ph = 258;
int addr_qte_hbdo_ph = 259;
int addr_debit_pompe_ph = 269;
int addr_ModeFiltration = 279;
int addr_val_bouton_lum_piscine = 280;
int addr_val_bouton_lum_garage = 281;

// *******************
// Divers
// *******************
unsigned long lastReadingTime = 0;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
int val_temp_system;
int num_page = 0;
int chk;
int ValTimer1 = 0;
int PresetTimer1 = 10;   // Valeur du Timer 1 en minutes (frequence ecriture carte Sd)
char buffer[10] = {0};
int8_t SetPhRedoxType = -1;
int8_t SetPhRedoxUp = -1;
uint8_t number = 0;
float humd;
float temp;
float TEau = 0;

RTCLib rtc;


///////////////////////////////////////////////////////////////////////////////
//                            INIT
///////////////////////////////////////////////////////////////////////////////
File fichierSD;


byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
// Adresse IP et Port
// Piscine
IPAddress ip(192, 168, 1, 179);
IPAddress servermqtt(192, 168, 1, 75); // IP Serveur mqtt
EthernetServer server(2854);

// Banc de test
// IPAddress ip(192, 168, 1, 179);
// EthernetServer server(2855);

//mqtt
char message_buff[50];

// MQTT / Message souscrit
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message arrived");

  int i = 0;

  Serial.println("Message arrived, Topic : " + String(topic));
  Serial.println("Length: " + String(length, DEC));

  // create character buffer with ending null terminator (string)
  for (i = 0; i < length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';

  String msgString = String(message_buff);

  Serial.println("Payload: " + msgString);
  if (String(topic) == "Home/Piscine/Lumiere") {
    if (msgString == "0ff") {
      strcpy(buffer, "OFF");
      digitalWrite(relais_lum_piscine, HIGH);
      val_bouton_lum_piscine = 0;
      strcpy(EtatLum, "Off");
      P13_b3.setText(buffer);
    }

    if (msgString == "On") {
      strcpy(buffer, "ON");
      digitalWrite(relais_lum_piscine, LOW);
      val_bouton_lum_piscine = 1;
      strcpy(EtatLum, "On");
      P13_b3.setText(buffer);
    }
  }

  if (String(topic) == "Home/Garage/Lumiere") {
    if (msgString == "0ff") {
      strcpy(buffer, "OFF");
      digitalWrite(relais_lum_garage, HIGH);
      val_bouton_lum_garage = 0;
      strcpy(EtatLum, "Off");
      P13_b2.setText(buffer);
    }

    if (msgString == "On") {
      strcpy(buffer, "ON");
      digitalWrite(relais_lum_garage, LOW);
      val_bouton_lum_garage = 1;
      strcpy(EtatLum, "On");
      P13_b2.setText(buffer);
    }
  }

  if (String(topic) == "Home/Piscine/Pompe") {
    dbSerialPrintln(EEPROM.read(addr_ModeFiltration));
    ModeFiltration = atoi(message_buff);
    EEPROM.write(addr_ModeFiltration, atoi(message_buff));
    if (atoi(message_buff) == 1) {
      P4_b9.setText("AUTO");
      duree_filtration = (int)TEau / 2;
      P4_n1.setValue(duree_filtration);
      if (EEPROM.readDouble(addr_duree_filtration) != duree_filtration) {
        // Mqtt Filtration Duree
        mqtt_SendSwitch(75, "On", (int)duree_filtration * 10);
      }
      EEPROM.writeDouble(addr_duree_filtration, duree_filtration);
    } else {
      P4_b9.setText("MANU");
    }
  }

  if (String(topic) == "Home/Piscine/Pompe/Filtration/Depart") {
    depart_filtration = atoi(message_buff);
    P4_n0.setValue(depart_filtration);
    P2_n0.setValue(depart_filtration);
    EEPROM.writeDouble(addr_depart_filtration, atoi(message_buff));
  }

  if (String(topic) == "Home/Piscine/Pompe/Filtration/Duree") {
    duree_filtration = atoi(message_buff);
    P2_n2.setValue(duree_filtration);
    P4_n1.setValue(duree_filtration);

    //      ModeFiltration = 0;
    //      EEPROM.write(addr_ModeFiltration, ModeFiltration);
    //      P4_b9.setText("MANU");
    if (EEPROM.readDouble(addr_duree_filtration) != duree_filtration) {
      mqtt_FiltrationMode();
    }
    EEPROM.writeDouble(addr_duree_filtration, duree_filtration);
  }
}


EthernetClient ethClient;
PubSubClient client(servermqtt, 1883, callback, ethClient);


// Register object to the touch event list.
NexTouch *nex_listen_list[] =
{
  &page0,
  &P0_b0, &P0_b1, &P0_b2,
  &P0_t0, &P0_t1, &P0_t2, &P0_t4, &P0_t7, &P0_t8, &P0_t9, &P0_t10, &P0_t26,
  &page1,
  &P1_b0, &P1_b1, &P1_b2, &P1_b3, &P1_b4, &P1_b5, &P1_b6, &P1_b7,
  &P1_b8, &P1_b9, &P1_b10, &P1_b11, &P1_b12, &P1_b13, &P1_b14, &P1_b15,
  &P1_n1, &P1_n4, &P1_n5, &P1_t8, &P1_t11, &P1_t13,
  &page2,
  &P2_b0, &P2_b1, &P2_b2,
  &page3,
  &P3_b0, &P3_b1, &P3_b2,
  &page4,
  &P4_b8, &P4_b0, &P4_b1, &P4_b2, &P4_b3, &P4_b4, &P4_b5, &P4_b6, &P4_b7, &P4_b9,
  &page5,
  &P5_b2, &P5_b0, &P5_b1,
  &page6,
  &P6_b0, &P6_b1, &P6_b2, &P6_b3,
  &page9,
  &P9_b0, &P9_b1, &P9_b2, &P9_b3,
  &page10,
  &P10_b0, &P10_b1, &P10_b2, &P10_b3, &P10_b4,
  &page11,
  &P11_b0, &P11_b1, &P11_b2, &P11_b3,
  &page12,
  &P12_b0, &P12_b1, &P12_b2, &P12_b3, &P12_b4,
  &page13,
  &P13_b0, &P13_b1, &P13_b2, &P13_b3,
  NULL
};

dht DHT;

OneWire oneWire(DS18B20); //Bus One Wire sur la pin 24 de l'arduino
DallasTemperature sensors(&oneWire); //Utilistion du bus Onewire pour les capteurs
DeviceAddress sensorDeviceAddress; //Vérifie la compatibilité des capteurs avec la librairie

///////////////////////////////////////////////////////////////////////////////
//                            SETUP
///////////////////////////////////////////////////////////////////////////////

void setup() {

  //  Initialisation des variables EEPROM arduino vierge (a executer une seule fois):

  //  debit_pompe_chlore = 2.1;
  //  EEPROM.writeDouble(addr_debit_pompe_chlore, debit_pompe_chlore);
  //  debit_pompe_ph = 2.1;
  //  EEPROM.writeDouble(addr_debit_pompe_ph, debit_pompe_ph);
  //  seuil_ph = 7.4;
  //  EEPROM.writeDouble(addr_seuil_ph, seuil_ph);
  //    conshorsgel = 18.0;
  //    EEPROM.writeDouble(addr_conshorsgel, conshorsgel);

//      etalon_ph_acide = 4.01;
//      EEPROM.writeDouble(addr_etalon_ph_acide, etalon_ph_acide);
//      etalon_ph_base = 7,01;
//      EEPROM.writeDouble(addr_etalon_ph_base, etalon_ph_base);

  // Démarre la connection ethernet et le serveur
  Ethernet.begin(mac, ip);
  server.begin();

  // Initialisation des variables stockées en eeprom
  etalon_redox = EEPROM.readDouble(addr_eeprom_redox);
  seuil_redox = EEPROM.readDouble(addr_seuil_redox);
  delta_redox = EEPROM.readDouble(addr_delta_redox);
  depart_filtration = EEPROM.readDouble(addr_depart_filtration);
  duree_filtration = EEPROM.readDouble(addr_duree_filtration);
  depart_robot = EEPROM.readDouble(addr_depart_robot);
  duree_robot = EEPROM.readDouble(addr_duree_robot);
  conshorsgel = EEPROM.readDouble(addr_conshorsgel);
  a_ph = EEPROM.readFloat(addr_a_ph);
  b_ph = EEPROM.readFloat(addr_b_ph);
  etalon_ph_acide = EEPROM.readFloat(addr_etalon_ph_acide);
  etalon_ph_base = EEPROM.readFloat(addr_etalon_ph_base);
  seuil_ph = EEPROM.readFloat(addr_seuil_ph);

  val_bouton_chlore = EEPROM.read(addr_val_bouton_chlore);
  debit_pompe_chlore = EEPROM.readDouble(addr_debit_pompe_chlore);

  val_bouton_ph = EEPROM.read(addr_val_bouton_ph);
  debit_pompe_ph = EEPROM.readDouble(addr_debit_pompe_ph);

  ModeFiltration = EEPROM.read(addr_ModeFiltration);

  /* Set the baudrate which is for debug and communicate with Nextion screen. */
  nexInit();
  P0_b0.attachPop(P0_b0PopCallback);
  P0_b1.attachPop(P0_b1PopCallback);
  P0_b2.attachPop(P0_b2PopCallback);

  P1_b0.attachPop(P1_b0PopCallback);
  P1_b1.attachPop(P1_b1PopCallback);
  P1_b2.attachPop(P1_b2PopCallback);
  P1_b3.attachPop(P1_b3PopCallback);
  P1_b4.attachPop(P1_b4PopCallback);
  P1_b5.attachPop(P1_b5PopCallback);
  P1_b6.attachPop(P1_b6PopCallback);
  P1_b8.attachPop(P1_b8PopCallback);
  P1_b9.attachPop(P1_b9PopCallback);
  P1_b10.attachPop(P1_b10PopCallback);
  P1_b11.attachPop(P1_b11PopCallback);
  P1_b12.attachPop(P1_b12PopCallback);
  P1_b13.attachPop(P1_b13PopCallback);
  P1_b14.attachPop(P1_b14PopCallback);
  P1_b15.attachPop(P1_b15PopCallback);
  P1_n1.attachPop(P1_n1PopCallback);
  P1_n4.attachPop(P1_n4PopCallback);
  P1_n5.attachPop(P1_n5PopCallback);
  P1_t8.attachPop(P1_t8PopCallback);
  P1_t11.attachPop(P1_t11PopCallback);
  P1_t13.attachPop(P1_t13PopCallback);

  P2_b0.attachPop(P2_b0PopCallback);
  P2_b1.attachPop(P2_b1PopCallback);
  P2_b2.attachPop(P2_b2PopCallback);

  P3_b0.attachPop(P3_b0PopCallback);
  P3_b1.attachPop(P3_b1PopCallback);
  P3_b2.attachPop(P3_b2PopCallback);

  P4_b0.attachPop(P4_b0PopCallback);
  P4_b1.attachPop(P4_b1PopCallback);
  P4_b2.attachPop(P4_b2PopCallback);
  P4_b3.attachPop(P4_b3PopCallback);
  P4_b4.attachPop(P4_b4PopCallback);
  P4_b5.attachPop(P4_b5PopCallback);
  P4_b6.attachPop(P4_b6PopCallback);
  P4_b7.attachPop(P4_b7PopCallback);
  P4_b8.attachPop(P4_b8PopCallback);
  P4_b9.attachPop(P4_b9PopCallback);

  P5_b0.attachPop(P5_b0PopCallback);
  P5_b1.attachPop(P5_b1PopCallback);
  P5_b2.attachPop(P5_b2PopCallback);

  P6_b0.attachPop(P6_b0PopCallback);
  P6_b1.attachPop(P6_b1PopCallback);
  P6_b2.attachPop(P6_b2PopCallback);
  P6_b3.attachPop(P6_b3PopCallback);

  P9_b0.attachPop(P9_b0PopCallback);
  P9_b1.attachPop(P9_b1PopCallback);
  P9_b2.attachPop(P9_b2PopCallback);
  P9_b3.attachPop(P9_b3PopCallback);

  P10_b0.attachPop(P10_b0PopCallback);
  P10_b1.attachPop(P10_b1PopCallback);
  P10_b2.attachPop(P10_b2PopCallback);
  P10_b3.attachPop(P10_b3PopCallback);
  P10_b4.attachPop(P10_b4PopCallback);

  P11_b0.attachPop(P11_b0PopCallback);
  P11_b1.attachPop(P11_b1PopCallback);
  P11_b2.attachPop(P11_b2PopCallback);
  P11_b3.attachPop(P11_b3PopCallback);

  P12_b0.attachPop(P12_b0PopCallback);
  P12_b1.attachPop(P12_b1PopCallback);
  P12_b2.attachPop(P12_b2PopCallback);
  P12_b3.attachPop(P12_b3PopCallback);
  P12_b4.attachPop(P12_b4PopCallback);

  P13_b0.attachPop(P13_b0PopCallback);
  P13_b1.attachPop(P13_b1PopCallback);
  P13_b2.attachPop(P13_b2PopCallback);
  P13_b3.attachPop(P13_b3PopCallback);

  dbSerialPrint(F("server is at "));
  dbSerialPrintln(Ethernet.localIP());
  dbSerialPrintln(F("setup done"));


  if (client.connect("arduinoClient")) {
    // Mqtt Envoie Off aux lumières
    mqtt_SendSwitch(71, "Off", 100);
    mqtt_SendSwitch(72, "Off", 100);

    client.subscribe(topicoutFiltrationDepart);
    client.subscribe(topicoutFiltrationDuree);
    client.subscribe(topicoutLumPiscine);
    client.subscribe(topicoutLumGarage);
    client.subscribe(topicoutPompe);
    //      dbSerialPrintln("Message souscrit");
  }

  /* RTCLib::set(byte second, byte minute, byte hour,
    byte dayOfWeek, byte dayOfMonth, byte month, byte year);
  */
  // rtc.set(0, 26, 22, 3, 31, 5, 17);

  pinMode(relais_filtration, OUTPUT);     //Configure la broche relais filtration en sortie
  pinMode(relais_robot, OUTPUT);          //Configure la broche relais robot en sortie
  pinMode(relais_ph, OUTPUT);        //Configure la broche relais horgel en sortie
  pinMode(relais_chlore, OUTPUT);        //Configure la broche relais chlore en sortie
  pinMode(relais_lum_garage, OUTPUT);  //Configure la broche relais lumière garage en sortie
  pinMode(relais_lum_piscine, OUTPUT);  //Configure la broche relais lumière piscine en sortie
  pinMode(Buzzer, OUTPUT);     //Configure la Buzzer en sortie

  digitalWrite(relais_filtration, HIGH);  // par défaut, la relais n'est pas collé
  digitalWrite(relais_robot, HIGH);       // par défaut, la relais n'est pas collé
  digitalWrite(relais_ph, HIGH);     // par défaut, la relais n'est pas collé
  digitalWrite(relais_chlore, HIGH);     // par défaut, la relais n'est pas collé
  digitalWrite(relais_lum_garage, HIGH);     // par défaut, la relais n'est pas collé
  digitalWrite(relais_lum_piscine, HIGH);     // par défaut, la relais n'est pas collé

  TpsSecuOfaChlore = ConsTpsSecuOfaChlore; // initialisation temps OFA Chlore
  TpsSecuOfaPh = ConsTpsSecuOfaPh; // initialisation temps OFA Ph
  ValTimer1 = PresetTimer1;                         // initialisation du timer 1
  qte_hbdo = 0;

  // Init capteur OneWire
  sensors.getAddress(sensorDeviceAddress, 0); //Demande l'adresse du capteur à l'index 0 du bus
  sensors.setResolution(sensorDeviceAddress, 12); //Résolutions possibles: 9,10,11,12

  sensors.requestTemperatures(); //Demande la température aux capteurs
//  sensors.setWaitForConversion(false);
  TEau = sensors.getTempCByIndex(0);

  // Init capteur ampermetrique
  emon1.current(1, 29); // Current: input pin, calibration. Cur Const= Ratio/BurdenR. 1800/62 = 29.

  // Initialisation de la carte SD
  if (!SD.begin(4)) {
    dbSerialPrintln(F("Init carte SD impossible !"));
    return;
  }
  dbSerialPrintln(F("Init carte SD OK"));

  //////////// ATTENTION: ne rien mettre aprés (return) si pas d'init carte SD //////////////
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                            Programme principal
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void loop() {

  unsigned long currentMillis = millis();
  unsigned long currentMillis2 = millis();


  ////////////////////////// Temporisation de 1 seconde /////////////////////////
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    // pH
//    Serial.println();
//    Serial.print("pin_ph: ");
//    Serial.print(analogRead(pin_ph));
    
    ph_sensor_value = analogRead(pin_ph);
    ph_value_float = (a_ph * ph_sensor_value) + b_ph;     	// calcule du pH
//    Serial.println();
//    Serial.print("ph_sensor_value: ");
//    Serial.print(ph_sensor_value);
//    Serial.print(" - a_ph: ");
//    Serial.print(a_ph);
//    Serial.print(" - b_ph: ");
//    Serial.print(b_ph);
//    Serial.print(" - ph_value_float: ");
//    Serial.print(ph_value_float);

        
    if (ph_value_float < 0) {								// On borne le Ph entre 0 et 14
      ph_value_float = 0;
    }
    if (ph_value_float > 14) {
      ph_value_float = 14;
    }
    //Mqtt Envoi PH
    if ((rtc.minute() % 5 == 0) && (rtc.second() == 0)) {
      mqtt_Send(170, "\"" + (String)ph_value_float + "\"");
    }

    // Redox
//    Serial.println();
//    Serial.print("pin_redox: ");
//    Serial.print(analogRead(pin_redox));
//    Serial.println();
    redox_sensor_value = analogRead(pin_redox) * 5000.0 / 1023.0 / 1000.0;   // Convertit 0.0 to 5.0 V
//    Serial.print("redox_sensor_value: ");
//    Serial.print(redox_sensor_value);
//    Serial.println();
    redox_value_float = (((2.5 - redox_sensor_value) / 1.037) * 1000.0) + (etalon_redox - 250);     // calibration entre -2000 to 2000 mV
//    Serial.print("etalon_redox: ");
//    Serial.print(etalon_redox);
//    Serial.println();
//    Serial.print("redox_value_float: ");
//    Serial.print(redox_value_float);
//    Serial.println();
    /*    	if (redox_value_float < 0){
    			redox_value_float = 0;
    		}
    		if (redox_value_float > 2000){
    			redox_value_float = 2000;
    		}
    */
    // calcul du min-max redox accepté
    redox_min = seuil_redox - delta_redox / 2;
    redox_max = seuil_redox + delta_redox / 2;
    //Mqtt Envoi Redox
    if ((rtc.minute() % 5 == 0) && (rtc.second() == 0)) {
      mqtt_Send(171, "\"" + (String)redox_value_float + "\"");
    }

    rtc.refresh();

    if (num_page == 0) {
      P0Display();
      timeDisplay();
    }

    if (num_page == 2) {
      P2Display();
      timeDisplay_p2();
    }

    if (num_page == 3) {
      P3Display();
      timeDisplay_p3();
    }

    if (num_page == 6) {
      P6Display();
    }

    if (num_page == 9) {
      P9Display();
      timeDisplay_p9();
    }

    if (num_page == 11) {
      P11Display();
      timeDisplay_p11();
    }

    if (num_page == 13) {
      P13Display();
      timeDisplay_p13();
    }

    // Connexion / Reconnexion serveur mqtt
    if (!client.connected()) {
      reconnect();
    }
    
    // Calcul pression en bar
    uint16_t val_pression = analogRead(pin_pression);
//    Serial.print("Pin Pression: ");
//    Serial.print(analogRead(pin_pression));
//    Serial.print(" - Sensor Value: ");
//    Serial.print(val_pression);    
    float bar_pression = encode_pressure(val_pression);
//    Serial.print(" - Pressure = "); 
//    Serial.print(bar_pression); 
//    Serial.println();
//    Serial.println(" bars"); 
    //Mqtt Envoi pression
    if ((rtc.minute() % 5 == 0) && (rtc.second() == 0)) {
      mqtt_Send(169, "\"" +  (String)bar_pression + "\"");
    }
    
    // Consommation électrique pompe
    Irms = emon1.calcIrms(1480);  // Calculate Irms only
    //dbSerialPrint(Irms*230.0);           // Apparent power
    //dbSerialPrint(F(" "));
    //dbSerialPrint(Irms);             // Irms
    conso = Irms * 230.0;
    //Mqtt Envoi consommation pompe
    if ((rtc.minute() % 5 == 0) && (rtc.second() == 0)) {
      mqtt_Send(78, "\"" +  (String)conso + "\"");
    }

    // lecture du DHT22
    chk = DHT.read22(DHT22_PIN);
    temp = (DHT.temperature);
    humd = (DHT.humidity);
    //Mqtt Envoi température & humidité
    if ((rtc.minute() % 5 == 0) && (rtc.second() == 0)) {
      mqtt_Send(63, "\"" + (String)temp + ";" + (String)humd + ";" + (String)humidityStatus(humd) + "\"");
    }

    // Temperature Eau
    sensors.requestTemperatures(); //Demande la température aux capteurs
    TEau = sensors.getTempCByIndex(0);
    dbSerialPrint(F("Teau : "));
    dbSerialPrint(TEau);
    //Mqtt Envoi température Eau
    if ((rtc.minute() % 5 == 0) && (rtc.second() == 0)) {
      mqtt_Send(176, "\"" + (String)TEau + "\"");
    }

    pompes();    // Appel routine gestion des pompes
    horsgel();   // Appel routine gestion du hors-gel

    //Mqtt Envoi Text départ & durée filtration
    if ((rtc.minute() % 5 == 0) && (rtc.second() == 0)) {
      mqtt_Send(73, "\"Heure démarrage : " + (String)depart_filtration + " - Durée : " + (String)duree_filtration + "\"");
    }

    if ((rtc.hour() == 1) && (rtc.minute() == 0)) {
      qte_hbdo = 0; // à 1 heure du matin, on réinitialise la quantité de chlore hebdo injectée
    }

    injection_chlore();
    injection_ph();
    temp_sytem();

    // Sécurité OFA
    if (TpsSecuOfaChlore == 0) {
      SecuOfaChlore = 1;
    }
    if (redox_value_float >= seuil_redox) {
      TpsSecuOfaChlore = ConsTpsSecuOfaChlore;
    }

    if (TpsSecuOfaPh == 0) {
      SecuOfaPh = 1;
    }
    if (ph_value_float <= seuil_ph) {
      TpsSecuOfaPh = ConsTpsSecuOfaPh;
    }

    // Démarage pompe filtration
    if ((filtrationON == 1) || (horsgelON == 1)) {
      digitalWrite(relais_filtration, LOW);
    }
    else {
      digitalWrite(relais_filtration, HIGH);
    }

    client.subscribe(topicoutFiltrationDepart);
    client.subscribe(topicoutFiltrationDuree);
    client.subscribe(topicoutPompe);
    client.subscribe(topicoutLumGarage);
    client.subscribe(topicoutLumPiscine);
    //    dbSerialPrintln("Message souscrit");
    //    dbSerialPrintln("-----------------------------------------");


  }

  ////////////////////////// Fin Temporisation de 1 seconde/////////////////////////

  ////////////////////////// Temporisation de 1 minute /////////////////////////
  if (currentMillis2 - previousMillis2 >= 60000) {
    previousMillis2 = currentMillis2;

    // Décompte timer 1 et ecriture sur la carte SD
    ValTimer1 -= 1;
    if (ValTimer1 == 0) {
      SDCard();
      ValTimer1 = PresetTimer1;
    }

    // Sécurité OFA
    if (StartInjection == 1) {
      TpsSecuOfaChlore -= 1;
    }
    if (TpsSecuOfaChlore <= 0) {
      TpsSecuOfaChlore = 0;
    }

    if (StartInjectionPh == 1) {
      TpsSecuOfaPh -= 1;
    }
    if (TpsSecuOfaPh <= 0) {
      TpsSecuOfaPh = 0;
    }

    if (filtrationON == 1) {
      sensors.requestTemperatures(); //Demande la température aux capteurs
      TEau = sensors.getTempCByIndex(0);
    }

  }
  ////////////////////////// Fin Temporisation de 1 minute/////////////////////////

  ethernet();
  nexLoop(nex_listen_list);
  client.loop();
}
