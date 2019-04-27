
String getPage(){
  String page = F("<html lang=fr-FR><head><meta http-equiv='refresh' content='10'/>");
  page += F("<title>ESP8266 Portail </title>");
  page += F("<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>");
  page += F("</head><body><h1>ESP8266 Portail</h1>");
  page += F("<h3>PORTAIL</h3>");
  page += F("<form action='/' method='POST'>");
  page += F("<ul><li>Portail ");

  if (etat_portail) {
    page += F("ouvert");
  }else{
    page += F("fermé  ");
  }
  
  page += F("<INPUT type='button' value='Commande' onClick=COMMAND</li></ul>");
  page += F("<INPUT type='submit' value='Actualiser'>");
  page += F("</body></html>");
  return page;
}

