void ethernet()
{

   // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println(F("HTTP/1.1 200 OK"));
          client.println(F("Content-Type: text/html"));
          client.println(F("Connection: close"));  // the connection will be closed after completion of the response
          client.println(F("Refresh: 5"));  // refresh the page automatically every 5 sec
          client.println();
          client.println(F("<!DOCTYPE HTML>"));
          client.println(F("<html><style>table, th, td {border: 1px solid black; border-collapse:collapse;}</style>"));
          client.println(F("<font size=7>"));
          client.print(F("***********************************"));
          client.println(F("<br />"));
          client.print(F("* Domogarden "));
          client.print(vers);
          client.print(F(" - Rev :  "));
          client.print(revision);
          client.print(F(" *"));
          client.println(F("<br />"));
          client.print(F("***********************************"));
          client.println(F("<br />"));
          client.println(F("</font>"));

          client.println(F("<font size=5>"));
          
          switch (rtc.dayOfWeek())
          {
            case 1:
                client.print(F("Lundi "));
                break;
            case 2: 
                client.print(F("Mardi "));
                break;
            case 3:
                client.print(F("Mercredi "));
                break;
            case 4:
                client.print(F("Jeudi "));
                break;
            case 5:
                client.print(F("Vendredi "));
                break;
            case 6:
                client.print(F("Samedi "));
                break;
            case 7:
                client.print(F("Dimanche "));
                break;
            default:
                client.print(F("Erreur "));
                break;
          }
          client.print(rtc.hour());
          client.print(":");
          client.print(rtc.minute()/10);
          client.println(rtc.minute()%10);
          client.print(F("<br />"));
          client.print(F("<br />"));
          client.println(F("<font size=4>"));
          client.print(F("<table border=1><tr>"));
          client.print(F("<td>Valeur Ph : </td><td>"));
          client.println(ph_value_float);
          client.println(F("</td></tr>"));
          
          client.print(F("<tr><td>Valeur Chlore : </td><td>"));
          client.println(redox_value_float);
          client.println(F("</td></tr>"));

          client.print(F("<tr><td>Temperature Eau: </td><td>"));
          client.println(TEau);
          client.println(F("</td></tr>"));

          client.print(F("<tr><td>Temperature Ext: </td><td>"));
          client.println(temp);
          client.println(F("</td></tr>"));

          client.print(F("<tr><td>Humidite Ext: </td><td>"));
          client.println(humd);
          client.println(F("</td></tr>"));

          client.print(F("<tr><td>Irms: </td><td>"));
          client.println(Irms);
          client.println(F("</td></tr>"));

          client.print(F("<tr><td>Apparent power: </td><td>"));
          client.println(Irms*230);
          client.println(F("</td></tr>"));
                                        
          client.print(F("<tr><td>Temperature Systeme: </td><td>"));
          client.println(val_temp_system);
          client.println(F("</td></tr>"));

          client.print(F("<tr><td>Pression Filtre (BAR): </td><td>"));
          client.println(bar_pression);
//          client.println(" / ");
//          client.println(psi_pression);
          client.println(F("</td></tr></table>"));
          client.println(F("<br />"));
          client.println(F("</font>"));

          ///////////////////////// Filtration /////////////////////////
          client.println(F("<font size=5>"));
          client.println(F("Filtration : "));
          if (filtrationON == 1){
            client.println(F("ON"));
          }
          else {
              client.println(F("OFF"));
          }
          client.println(F("<br />"));
          client.println(F("</font>"));
          client.println(F("<font size=4>"));
          client.println(F("<table><tr><td>"));
          client.println(F("Depart : </td><td>"));
          client.println(depart_filtration);
          client.println(F("</td></tr><tr><td>"));
          client.println(F("Duree : </td><td>"));
          client.println(duree_filtration);       
          client.println(F("</td></tr></table>"));
          client.println(F("</font>"));
          client.println(F("<br />"));


          ///////////////////////// Injection Chlore /////////////////////////
          client.println(F("<font size=5>"));
          client.println(F("Injection Chlore : "));
          if (injection_chloreON == 1){
            client.println(F("ON"));
          }
          else {
              client.println(F("OFF"));
          }

          client.println(F("<br />"));
          client.println(F("</font>"));
          client.println(F("<font size=4>"));
          client.println(F("<table><tr><td>"));
          client.println(F("Ton : </td><td>"));
          client.println(Ton);
          client.println(F("</td></tr><tr><td>"));
          client.println(F("Toff : </td><td>"));
          client.println(Toff);
          client.println(F("</td></tr><tr><td>"));
          client.println(F("Ratio : </td><td>"));
          client.println(CycleChlore);
          client.println(F("%"));
          client.println(F("</td></tr><tr><td>"));
          client.println(F("Qte Hebdo : </td><td>"));
          client.println(qte_hbdo);
          client.println(F("</td></tr><tr><td>"));
          client.println(F("Temps OFA : </td><td>"));
          client.println(TpsSecuOfaChlore);
          client.println(F("</td></tr></table>"));
          client.println(F("</font>"));
          client.println(F("<br />"));
          client.println(F("<br />"));
          
          ///////////////////////// Injection Ph /////////////////////////
          client.println(F("<font size=5>"));
          client.println(F("Injection Ph : "));
          if (injection_phON == 1){
            client.println(F("ON"));
          }
          else {
              client.println(F("OFF"));
          }

          client.println(F("<br />"));
          client.println(F("</font>"));
          client.println(F("<font size=4>"));
          client.println(F("<table><tr><td>"));
          client.println(F("Ton : </td><td>"));
          client.println(TonPh);
          client.println(F("</td></tr><tr><td>"));
          client.println(F("Toff : </td><td>"));
          client.println(ToffPh);
          client.println(F("</td></tr><tr><td>"));
          client.println(F("Ratio : </td><td>"));
          client.println(CyclePh);
          client.println(F("%"));
          client.println(F("</td></tr><tr><td>"));
          client.println(F("Qte Hebdo : </td><td>"));
          client.println(qte_hbdo_ph);
          client.println(F("</td></tr><tr><td>"));
          client.println(F("Temps OFA : </td><td>"));
          client.println(TpsSecuOfaPh);
          client.println(F("</td></tr></table>"));
          client.println(F("</font>"));
          client.println(F("<br />"));
          client.println(F("<br />"));
          
          ///////////////////////// Robot /////////////////////////
          client.println(F("<font size=5>"));
          client.println(F("Robot : "));
          if (robotON == 1){
            client.println(F("ON"));
          }
          else {
              client.println(F("OFF"));
          }
          client.println(F("<br />"));
          client.println(F("</font>"));
          client.println(F("<font size=4>"));
          client.println(F("<table><tr><td>"));
          client.println(F("Depart : </td><td>"));
          client.println(depart_robot);
          client.println(F("</td></tr><tr><td>"));
          client.println(F("Duree : </td><td>"));
          client.println(duree_robot);
          client.println(F("</td></tr></table>"));
          client.println(F("</font>"));
          client.println(F("<br />"));
          client.println(F("<br />"));

          ///////////////////////// Hors Gel /////////////////////////
          client.println(F("<font size=5>"));
          client.println(F("Hors Gel : "));
          if (horsgelON == 1){
            client.println(F("ON"));
          }
          else {
              client.println(F("OFF"));
          }
          client.println(F("<br />"));
          client.println(F("</font>"));
          client.println(F("<font size=4>"));
          client.println(F("<table><tr><td>"));
          client.println(F("Consigne : </td><td>"));
          client.println(conshorsgel);
          client.println(F("</td></tr></table>"));
          client.println(F("</font>"));
          client.println(F("<br />"));
          client.println(F("<br />"));
          
          client.println(F("</font>"));
          client.println(F("</html>"));
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println(F("client disconnected"));
  }
}


