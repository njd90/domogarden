void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print(F("Attempting MQTT connection..."));
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println(F("connected"));
      Serial.println(F("Publication en cours"));
    } else {
      Serial.print(F("failed, rc="));
      Serial.print(client.state());
      Serial.println(F(" try again in 5 seconds"));
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

//Status : 70% wet(3), below 30 Dry(2), between 30 and 45 Normal (0), and 45 and 70 comfortable (1).
int humidityStatus(int hum) {
  int status;
  if (hum < 30) {
    status = 2;
  } else if (hum >= 30 && hum <= 45) {
    status = 0;
  } else if (hum >= 45 && hum <= 70) {
    status = 1;
  } else {
    status = 3;
  }
  return status;
}
 
