/**
 *  Appelé à chaque chargement de la page principale
 */
void handleRoot(){
Serial.println("handleRoot");
handleGenericArgs();
  if ( server.hasArg("LED") ) {
    handleSubmit();
  } else {
    server.send ( 200, "text/html", getPage() );
  }  
}

/** 
 *  Appelé aprés chaque soumission de la page principale
 */
void handleSubmit() {
  // Actualise la page principale, traite le bouton commande
  
  String LEDValue;
  LEDValue = server.arg("LED");
  Serial.println("Set GPIO "); Serial.print(LEDValue);
  if ( LEDValue == "1" ) {
    digitalWrite(LEDPIN, 1);
    etatLed = "On";
    server.send ( 200, "text/html", getPage() );
  } else if ( LEDValue == "0" ) {
    digitalWrite(LEDPIN, 0);
    etatLed = "Off";
    server.send ( 200, "text/html", getPage() );
  } else {
    Serial.println("Err Led Value");
  }
}


/**
 *  Test : Appelé à chaque chargement de la page genericArgs
 */
void handleGenericArgs() { //Handler

  String message = "Number of args received:";
  message += server.args();            //Get number of parameters
  message += "\n";                            //Add a new line
  
  for (int i = 0; i < server.args(); i++) {
  
    message += "Arg nº" + (String)i + " –> ";   //Include the current iteration value
    message += server.argName(i) + ": ";     //Get the name of the parameter
    message += server.arg(i) + "\n";              //Get the value of the parameter
  
  } 
  Serial.println(message);
  server.send(200, "text/plain", message);       //Response to the HTTP request

}


///////////////////////////////////////////////////////////////////////

void handleJeedom() { 

  Serial << "Handel Jeedom  Nb arguments : " << server.args() << " Commande recue : " << server.argName(0) << " !" << endl;
  String message = "";
  
  if (server.argName(0).equals("GetState")) {     
    message = etat_portail;       
  }
  else if (server.argName(0).equals("Command")){
    message = "OK"; 
    commandePortail();
  }
  else {
    message = "ERROR";
  }
  Serial << "message HTTP : " << message << endl;
  
  server.send(200, "text/plain", message);          //Returns the HTTP response

}

