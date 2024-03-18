#include <ESP8266WiFi.h>
#include "config.h"
#include "wifi_client.h"
#include "sensor_simulator.h"
#include "sensor_data.h"
#include "transmission_routine.h"
#include "reception_routine.h" 
#include "sensor_sampling.h"

void setup() {
  digitalWrite(1, HIGH); // Turn on the LED
  delay(1000);

  if (DEBUG) { 
    Serial.begin(115200);
    delay(10);
  }

  if (DEBUG) Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA); // Set to client (station) mode
  WiFi.begin(SSID, WIFI_PASSWORD);
  //wait_for_connection();

  while (init_sensors() != SENSOR_INIT_SUCCESS) {
    if (DEBUG) Serial.println("Sensor initialization failed. Retrying in 1s.");
    delay(1000);
  }
}

WiFiClient client;

void loop() {

  connect_to_host(&client);

  while (client.connected()) {
    if (transmission_routine(&client) != TRANSMISSION_SUCCESS) {
      if (DEBUG) Serial.println("Transmission routine failed.");
      // error_handling();
    }

    if (reception_routine(&client) != RECEPTION_SUCCESS) {
      // error_handling();
    }

    if (DEBUG) Serial.println("\r\n");
    delay(1000);
  }

  delay(1000);
}