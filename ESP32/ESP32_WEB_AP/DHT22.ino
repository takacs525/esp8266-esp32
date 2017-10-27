// USE THIS: https://github.com/RobTillaart/Arduino/tree/master/libraries/DHTstable

void PrintDHT() {
  String tempStr = "Temp: " + String(DHT.temperature) + " C";
  String humStr = "Hum: " + String(DHT.humidity) + " %";
  drawText(tempStr, humStr, "");
}

