/////////////////////////////////////////////////////////////////////////////////
//                          Page Hors gel
/////////////////////////////////////////////////////////////////////////////////
void P3_b0PopCallback(void *ptr) // Bouton page suivante (appel page 9)
{
page9.show();
  num_page = 9;
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
  P9_b3.setText(buffer);
  P9_t4.setText(buffer_hour);
  P9_t6.setText(buffer_minute);  
}
  
void P3_b1PopCallback(void *ptr) // Bouton page précedente (appel page 2)
{
  page2.show();
  num_page = 2;
  P2_n0.setValue(depart_filtration);
  P2_n2.setValue(duree_filtration);
  P2_n1.setValue(depart_robot);
  P2_n3.setValue(duree_robot);
  P2_n4.setValue(conso);
  P2_t4.setText(buffer_hour);
  P2_t6.setText(buffer_minute);
}

void P3_b2PopCallback(void *ptr)
{
  page5.show();
  num_page = 5;
  dtostrf(conshorsgel, 5, 1, buffer);
  P5_t1.setText(buffer);
}

/////////////////////////////////////////////////////////////////////////////////
//                          Fonctions Diverses
/////////////////////////////////////////////////////////////////////////////////
void P3Display()
{

    switch (chk)
    {
      case DHTLIB_OK:  
            if (temp <= conshorsgel){
              P3_t9.setText("ON");
            }
            else {
              P3_t9.setText("OFF");
            }
           break;
      case DHTLIB_ERROR_CHECKSUM: 
          P3_t9.setText("Err.");     
          break;
      case DHTLIB_ERROR_TIMEOUT: 
          P3_t9.setText("Err.");       
          break;
      default: 
          P3_t9.setText("Err.");   
          break;
    }

}
void timeDisplay_p3()
{
  
    memset(buffer, 0, sizeof(buffer)); 
    number = rtc.hour();
    itoa(number, buffer, 10);
    if (strcmp(buffer_hour, buffer))
    {
        P3_t4.setText(buffer);
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
        P3_t6.setText(buffer);
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
            P3_t8.setText(buffer);
            strcpy(buffer_second, buffer);
         }
    } 
    else
    {
        if (strcmp(buffer_temp, buffer_second))
        {
            P3_t8.setText(buffer_temp);
            strcpy(buffer_second, buffer_temp);
        }
    }
}
