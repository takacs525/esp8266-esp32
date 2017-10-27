// Global variables
int counter = 0;

#include "./Config.h"

#include <dht.h>
#include "SSD1306.h"

dht DHT;
SSD1306 display(OLED_ADDRESS, SDA_PIN, SCL_PIN);

void setup() {
  Serial.begin(115200);
  Serial.println();

  // Initialising the display too.
  SetupOLED();
  
  delay(1000);  
}


void loop() {
  counter++;

  int chk = DHT.read22(DHT22_PIN);

  if (chk == DHTLIB_OK) {
    String tempStr = "Temp: " + String(DHT.temperature) + " C";
    String humStr = "Hum:   " + String(DHT.humidity) + " %";
    String countStr = "Count: " + String(counter);
    drawText3(tempStr, humStr, countStr);
  } else {
    drawText1("DHT read Error!!!");
  }
  
  delay(2000);
}

