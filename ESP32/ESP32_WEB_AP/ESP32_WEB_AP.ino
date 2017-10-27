#include "./Config.h"

#include <dht.h>
#include "SSD1306.h"
#include <WiFiClient.h>
#include <ESP32WebServer.h>
#include "WiFi.h"

dht DHT;
SSD1306 display(OLED_ADDRESS, SDA_PIN, SCL_PIN);
ESP32WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();

  // Initialising LED
  pinMode(LED_PIN, OUTPUT);  
  digitalWrite(LED_BUILTIN, LOW);
  
  // Initialising the display too.
  SetupOLED();
  delay(100);

  drawText("Creating WiFi AP...", "", "");
  
  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);
        
  Serial.println();
  Serial.println();
  Serial.print("Creating WiFi AP ");
  Serial.println(ssid);

  WiFi.softAP(ssid, password);

  Serial.println("");
  Serial.println("WiFi is available.");
  Serial.println("IP address: ");
  Serial.println(WiFi.softAPIP());
  drawText("AP: " + String(ssid), "Pw: " + String(password), "IP: " +  WiFi.softAPIP().toString());
    
  server.on("/", handleRoot);
  server.on("/hello", handleHello);
  server.onNotFound(handleNotFound);

  server.on("/dhttxt", handleDHTTXT);
  server.on("/dhtjson", handleDHTJSON);

  server.on("/ledon", handleLEDon);
  server.on("/ledoff", handleLEDoff);
  
  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  server.handleClient();
}

