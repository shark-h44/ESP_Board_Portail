

void commandePortail() {
  Serial.println("-> Commande du portail");
  digitalWrite(PIN_COMMANDE_PORTAIL, HIGH);
  delay (TEMPO_CMD_RELAIS);
  digitalWrite(PIN_COMMANDE_PORTAIL, LOW);
}

