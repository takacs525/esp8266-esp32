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

  drawText("Connecting...", "", "");
  
  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);
        
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  drawText("WiFi: " + String(ssid), "Server IP:", WiFi.localIP().toString());
    
  server.on("/", handleRoot);
  server.on("/hello", handleHello);
  server.onNotFound(handleNotFound);

  server.on("/dht", handleDHT);
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

