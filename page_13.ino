/////////////////////////////////////////////////////////////////////////////////
//                          Page gestion Eclairage
/////////////////////////////////////////////////////////////////////////////////
void P13_b0PopCallback(void *ptr) // Bouton page suivante (appel page 0)
{
  page0.show();
  num_page = 0;
  P0_t2.setText(buffer_hour);
  P0_t4.setText(buffer_minute);
  P0_t8.setText(buffer_day);
  P0_t9.setText(buffer_week);
  P0_t10.setText(buffer_month);
  P0_t12.setText(buffer_year);
}

void P13_b1PopCallback(void *ptr) // Bouton page précedente (appel page 11)
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

// Bouton OFF/ON
void P13_b2PopCallback(void *ptr)
{
  val_bouton_lum_garage++;
  if (val_bouton_lum_garage > 1){
    val_bouton_lum_garage = 0;
  }
  switch (val_bouton_lum_garage)
  {
    case 0:
    strcpy(buffer, "OFF");
    delay (200);
    digitalWrite(relais_lum_garage, HIGH);
    strcpy(EtatLum, "Off");
    break;
    case 1:
    strcpy(buffer, "ON");
    delay (200);
    digitalWrite(relais_lum_garage, LOW);
    strcpy(EtatLum, "On");
    break;
    }
    // Mqtt Etat Lumière garage
    mqtt_SendSwitch(71, EtatLum,100);
    P13_b2.setText(buffer);

}

// Bouton OFF/ON
void P13_b3PopCallback(void *ptr)
{
  val_bouton_lum_piscine++;
  if (val_bouton_lum_piscine > 1){
    val_bouton_lum_piscine = 0;
  }
  switch (val_bouton_lum_piscine)
  {
    case 0:
    strcpy(buffer, "OFF");
    // delay (200);
    digitalWrite(relais_lum_piscine, HIGH);
    strcpy(EtatLum, "Off");
    break;
    case 1:
    strcpy(buffer, "ON");
    // delay (200);
    digitalWrite(relais_lum_piscine, LOW);
    strcpy(EtatLum, "On");
    break;
    }
    // Mqtt Etat lumière piscine
    mqtt_SendSwitch(72, EtatLum,100);
    P13_b3.setText(buffer);
}

/////////////////////////////////////////////////////////////////////////////////
//                          Fonctions Diverses
/////////////////////////////////////////////////////////////////////////////////
void P13Display() 
{
}

void timeDisplay_p13()
{
  
    memset(buffer, 0, sizeof(buffer)); 
    number = rtc.hour();
    itoa(number, buffer, 10);
    if (strcmp(buffer_hour, buffer))
    {
        P13_t4.setText(buffer);
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
        P13_t6.setText(buffer);
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
            P13_t8.setText(buffer);
            strcpy(buffer_second, buffer);
         }
    } 
    else
    {
        if (strcmp(buffer_temp, buffer_second))
        {
            P13_t8.setText(buffer_temp);
            strcpy(buffer_second, buffer_temp);
        }
    }
}

