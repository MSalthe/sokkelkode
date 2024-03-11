#include <ESP8266WiFi.h>
#include "config.h"
#include "wifi_client.h"
#include "sensor_simulator.h"
#include "sensor_data.h"
#include "transmit_sensor_data.h"

void setup() {
  if (DEBUG) { 
    Serial.begin(115200);
    delay(10);
  }

  if (DEBUG) Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA); // Set to client (station) mode
  WiFi.begin(ssid, password);
  wait_for_connection();
}

WiFiClient client;
SensorDataIMU sensor_data;

void loop() {
  if (DEBUG) Serial.println("loop() start");

  //connect_to_host();

  while (client.connected()) { // Main functionality loop
    //client.print(String("Hello from ESP8266") + "\r\n");
    sensor_data = simulate_sensor_sample();
    transmit_sensor_data(sensor_data);
    delay(1000);
  } 
  
  disconnect_error_handling();

  delay(1000);
}