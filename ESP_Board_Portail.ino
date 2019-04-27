/**
 * Procédure d'update
 * ATTENTION : activer le shunt de programmation seulement pour programmer le module
 * debrancher toutes les alims exterieur et port série
 * activer le shunt de programmation
 * brancher l'alim externe
 * brancher l'alim port serie
 * Lancer la mise à jour
 * une fois la mise a jour démarré led module bleu clignote rapidement, on peut retirer le shunt de prog
 * retirer l'alim du port série
 * debrancher et rebrancher l'alim externe pour redemarrer le module
 **/
 #include <PrintEx.h>   // https://github.com/Chris--A/PrintEx#printex-library-for-arduino-
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
 
#define WL_SSID  "myssid"       // WiFi WL_SSID
#define WL_PSWD  "mypass"  // WiFi WL_PSWD

#define MODULE_PORT 4444
#define LEDPIN    3          // Led
#define PIN_COMMANDE_PORTAIL    4
#define PIN_ETAT_PORTAIL    5
#define TEMPO_CMD_RELAIS 500

#define MQTT_SERVER_IP "192.168.0.100"
#define MQTT_SERVER_PORT 1883
#define MQTT_USER "jeedom"  //s'il a été configuré sur Mosquitto
#define MQTT_PASSW "jeedom" //idem
#define MQTT_MAX_RETRY  3

#define etat_topic "portail/etat"  //Topic etat

//Buffer qui permet de décoder les messages MQTT reçus
char message_buff[100];

volatile byte state_change = false;
byte etat_portail = LOW;
byte MQTT_retry = 0;
String  etatLed = "OFF";

// Indispensable pour utiliser : Serial << text << endl 
using namespace ios;

// Création des objets / create Objects
ESP8266WebServer server ( MODULE_PORT );
StreamEx mySerial = Serial;
WiFiClient espClient;
PubSubClient client(espClient);

// Déclaration des prototypes
void MQTT_Setup();
void MQTT_Reconnect(); 
void handleRoot();
void handleSubmit();
void handleGenericArgs();
void handleJeedom();
void commandePortail();

// Routine d'interruption du changement d'état du portail  
void ISR_Portail () {
  state_change = HIGH;
}

 
void setup() {

  // Initialisation du port série
  Serial.begin ( 115200 );
  delay(2000);
  Serial.println(F("Setup start")); 
  Serial.printf("\nThe compile time & date is: %s, %s\n", __TIME__, __DATE__);
  Serial.printf("File : %s\n", __FILE__);

  // Paramétrage des GPIO
  pinMode(PIN_COMMANDE_PORTAIL, OUTPUT);
  pinMode(PIN_ETAT_PORTAIL, INPUT_PULLUP);

  // Lecture de l'etat du portail
  etat_portail = digitalRead(PIN_ETAT_PORTAIL);

  // Getion de l'interruption pour le changement d'état du portail
  attachInterrupt(digitalPinToInterrupt(PIN_ETAT_PORTAIL), ISR_Portail, CHANGE);
  
  // Connexion au réseau Wifi
  Serial.println (F("Connexion au reseau Wifi")); 
  WiFi.begin ( WL_SSID, WL_PSWD );
  // Attente de la connexion au réseau WiFi / Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 ); Serial.print ( "." );
  }

  MQTT_Setup();
  
  // Connexion WiFi établie / WiFi connexion is OK
  Serial.println ( "" ); 
  Serial.print ( F("Connected to ") ); Serial.println ( WL_SSID );
  Serial.print ( F("IP address: ") ); Serial.println ( WiFi.localIP() );

  // Capture par le serveur web
  server.on ( "/", handleRoot );
  server.on("/genericArgs", handleGenericArgs);   //Associate the handler function to the path
  server.on("/jeedom", handleJeedom);  //Associate the handler function to the path 

  // Démarrage du serveur web 
  server.begin();
  Serial.println ( F("Serveur web demarre") );  
  Serial.println ( F("Fin du setup -> enter Loop") );
}
 
void loop() {

  if ( !client.connected() ) {
      MQTT_Reconnect();
  }
  client.loop();

  // On regarde si l'état du portail n'a pas changé
  if (state_change) {
    // On léve le flag d'interruption
    state_change = LOW;
    // Récupération de l'état du portail
    etat_portail = digitalRead(PIN_ETAT_PORTAIL);   
    // MAJ du topic MQTT
    client.publish(etat_topic, String(etat_portail).c_str(), true);
  }

  // Surveillance du serveur web
  server.handleClient();
  //  Serial.println("--");
  // Attente
  delay(1000);
}
