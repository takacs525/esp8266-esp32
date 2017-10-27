void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    
    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
      client.subscribe("/v1.6/devices/"DEVICE_LABEL"/"VARIABLE_LED_LABEL"/lv");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}

void PublishData(float temp, float hum, float error) {
  // Space to store values to send
  char str_data[10];

  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload

  if (error == 0) {

    sprintf(payload, "{");
    
    dtostrf(temp, 4, 2, str_data);
    sprintf(payload, "%s \"%s\":%s,", payload, VARIABLE_TEMP_LABEL, str_data);

    dtostrf(hum, 4, 2, str_data);
    sprintf(payload, "%s \"%s\":%s,", payload, VARIABLE_HUM_LABEL, str_data);

    dtostrf(error, 4, 2, str_data);
    sprintf(payload, "%s \"%s\":%s", payload, VARIABLE_ERROR_LABEL, str_data);

    sprintf(payload, "%s }", payload);
    
  } else {
    sprintf(payload, "{\"%s\":", VARIABLE_ERROR_LABEL); // Adds the variable label
    dtostrf(error, 4, 2, str_data);
    sprintf(payload, "%s {\"value\": %s}}", payload, str_data); // Adds the value
  }

  Serial.println("Publishing data to Ubidots Cloud - " + String(payload));
  
  client.publish(topic, payload);
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);

  if (message == "0") {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  
  Serial.write(payload, length);
  Serial.println(topic);
}

