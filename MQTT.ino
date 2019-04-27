

void MQTT_Setup() {
  client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);    //Configuration de la connexion au serveur MQTT
}


//Reconnexion
void MQTT_Reconnect() {
  //Boucle jusqu'à obtenir une reconnexion ou depassement du nombre max de tentative
  while (!client.connected()&& (MQTT_retry <= MQTT_MAX_RETRY)) {
    MQTT_retry++;
    Serial.println ( F("Connexion au serveur MQTT perdue") );
    Serial.print ( F("Essai de reconnexion N") );
    Serial.println (MQTT_retry);
    Serial.print(F("Connexion au serveur MQTT..."));
    
    if (client.connect("ESP8266Client", MQTT_USER, MQTT_PASSW)) {
      Serial.println(F("OK"));
    } else {
      Serial.print(F("KO, erreur : "));
      Serial.print(client.state());
      if (MQTT_retry <= MQTT_MAX_RETRY){
        // Serveur injoignable
        Serial.println(F("Arrêt des tentatives de connexions au serveur MQTT"));
        Serial.println(F("Fonctionnalité de mise à jour de l'état du portail indisponible"));
      }else{
        Serial.println(F(" On attend 5 secondes avant de recommencer"));
        delay(5000);
      }

    }
  }
}
