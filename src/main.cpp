#include <ESP8266WiFi.h>
#include "config.h"
#include "wifi_client.h"
#include "sensor_simulator.h"
#include "sensor_data.h"
#include "transmission_routine.h"
#include "reception_routine.h" 
#include "main_routine.h"

// Devices
WiFiClient client;
DFRobot_BMI160 bmi160;

// Containers
SensorDataContainer_IMU sensor_data_container(&bmi160); // Holds data from the IMU sensor (accelerometer and gyroscope
IMU_sensor_reading sensor_reading_container; // Holds one reading from the IMU sensor

// Timing
int update_delay = min(TRANSMISSION_INTERVAL, SENSOR_UPDATE_INTERVAL); // ms

void setup() {

  if (DEBUG) { 
    delay(1000);
    Serial.begin(115200);
    delay(10);
  }

  if (DEBUG) Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA); // Set to client (station) mode
  WiFi.begin(SSID_STRING, WIFI_PASSWORD);

  while (bmi160.I2cInit() != BMI160_OK) {
    if (DEBUG) Serial.println("Sensor initialization failed. Retrying in 1000ms.");
    delay(1000);
  }
}

void loop() {
  connect_to_host(&client);

  while (client.connected()) {
    

    main_routine(&client, &bmi160, &sensor_data_container, &sensor_reading_container);
    
    delay(update_delay);
  }

  // Todo separate timers for sensor sampling and transmission

  delay(RECONNECT_DELAY);
}