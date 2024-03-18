#include <ESP8266WiFi.h>
#include "config.h"
#include "wifi_client.h"
#include "sensor_simulator.h"
#include "sensor_data.h"
#include "transmission_routine.h"
#include "reception_routine.h" 

// Devices
WiFiClient client;
DFRobot_BMI160 bmi160;

// Containers
SensorDataContainer_IMU sensor_data_container;
IMU_sensor_reading sensor_reading_container; // Holds one reading from the IMU sensor

void setup() {

  if (DEBUG) { 
    delay(1000);
    Serial.begin(115200);
    delay(10);
  }

  if (DEBUG) Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA); // Set to client (station) mode
  WiFi.begin(SSID, WIFI_PASSWORD);

  while (bmi160.I2cInit() != BMI160_OK) {
    if (DEBUG) Serial.println("Sensor initialization failed. Retrying in 1000ms.");
    delay(1000);
  }
}

void loop() {

  connect_to_host(&client);

  while (client.connected()) {
    sensor_data_container.sample_IMU();
    sensor_data_container.get_reading(&sensor_reading_container);
    if (transmit_IMU_sensor_reading(&sensor_reading_container, &client) != TRANSMISSION_SUCCESS) {
      if (DEBUG) Serial.println("Transmission failed.");
    }
    delay(1);
  }

  delay(1000);
}