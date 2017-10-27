/****************************************
 * Include Libraries
 ****************************************/
#include <WiFi.h>
#include <PubSubClient.h>
#include <dht.h>

/****************************************
 * Define Constants
 ****************************************/
#include "./Config.h"

char mqttBroker[]  = "things.ubidots.com";
char payload[255];
char topic[150];

/****************************************
 * Auxiliar Functions
 ****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);
dht DHT;

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  Serial.begin(115200);

  // LED init
  pinMode(LED_BUILTIN, OUTPUT);  

  // Restart and connect to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);
  WiFi.begin(WIFISSID, PASSWORD);

  Serial.println();
  Serial.print("Connecting to " + String(WIFISSID));
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  
  Serial.println("WiFi Connected :-)");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  // MQTT init
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);  
  client.subscribe("/v1.6/devices/"DEVICE_LABEL"/"VARIABLE_LED_LABEL"/lv");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  int chk = DHT.read22(DHT22_PIN);

  if (chk == DHTLIB_OK) {
    PublishData(DHT.temperature, DHT.humidity, 0);
  } else {
    Serial.println("DHT read error!!!");
    PublishData(0, 0, 1);
  }

  delay(5000);
}
