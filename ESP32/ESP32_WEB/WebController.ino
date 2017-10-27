void handleRoot() {
  server.send(200, "text/plain", "GROOOOOT!");
}

void handleHello() {
  server.send(200, "text/plain", "Hello from ESP32!");
}

void handleDHT() {
  int chk = DHT.read22(DHT22_PIN);

  String message = "";
  if (chk == DHTLIB_OK) {
    PrintDHT();

    message += DHTtoHTML(DHT.temperature, DHT.humidity);
  } else {
    drawText("DHT read error!!!", "", "");
    message += "<html><body>DHT read error!!!</body></html>";
  }
  
  server.send(200, "text/html", message);
}

void handleDHTTXT() {
  int chk = DHT.read22(DHT22_PIN);

  String message = "";
  if (chk == DHTLIB_OK) {
    String tempStr = "Temp: " + String(DHT.temperature) + " C";
    String humStr = "Hum: " + String(DHT.humidity) + " %";
    drawText(tempStr, humStr, "");

    message += tempStr + "\n";
    message += humStr + "\n";
    
  } else {
    drawText("DHT read error!!!", "", "");
    message += "DHT read error!!!";
  }
  
  server.send(200, "text/plain", message);
}

void handleDHTJSON() {
  int chk = DHT.read22(DHT22_PIN);

  String message = "";
  if (chk == DHTLIB_OK) {
    PrintDHT();

    message += "{\"dht\": {\n";
    message += "  \"temperature\": " + String(DHT.temperature) + ",\n";
    message += "  \"humidity\": " + String(DHT.humidity) + "\n";
    message += "  }\n";
    message += "}\n";
    
  } else {
    drawText("DHT read error!!!", "", "");
    message += "{ \"error\" : \"true\" }";
  }
  
  server.send(200, "application/json", message);
}

void handleLEDon(){
  digitalWrite(LED_PIN, HIGH);
  server.send(200, "text/plain", "on");
}

void handleLEDoff(){
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain", "off");
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

