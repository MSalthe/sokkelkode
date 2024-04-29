#include <ESP8266WiFi.h>
#include "config.h"
#include "wifi_client.h"
#include "sensor_simulator.h"
#include "sensor_data.h"
#include "transmission_routine.h"
#include "reception_routine.h" 
#include "light_controller.h"

// Devices
WiFiClient client;
DFRobot_BMI160 bmi160;

// Containers
SensorDataContainer_IMU sensor_data_container(&bmi160); // Holds data from the IMU sensor (accelerometer and gyroscope
IMU_sensor_reading sensor_reading_container; // Holds one reading from the IMU sensor

// Timing
int update_delay = min(TRANSMISSION_INTERVAL, SENSOR_UPDATE_INTERVAL); // ms

// Identifiers
int session_id = -1;
int client_id = -1;

void setup() {

  if (DEBUG) { 
    delay(1000);
    Serial.begin(115200);
    delay(10);
  }

  pinMode(1, OUTPUT);

  if (DEBUG) Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA); // Set to client (station) mode
  WiFi.begin(SSID_STRING, WIFI_PASSWORD);

  while (bmi160.I2cInit() != BMI160_OK) {
    if (DEBUG) Serial.println("Sensor initialization failed. Retrying in 1000ms.");
    delay(1000);
  }
}

LightController light_controller;

// Timing
int sensor_update_interval = SENSOR_UPDATE_INTERVAL; // ms
unsigned long sensor_last_update = 0;

int transmission_interval = TRANSMISSION_INTERVAL; // ms
unsigned long transmission_last_update = 0;

//int light_period = LIGHT_INTERVAL / LIGHT_FRAME_COUNT; // ms
int light_period = 10; // ms
unsigned long light_last_update = 0;

void loop() {
  connect_to_host(&client);

  while (client.connected()) {

    // Sample sensors
    if (millis() - sensor_last_update > sensor_update_interval) {
        sensor_last_update = millis();
        
        sensor_data_container.sample_IMU(); // Todo error checking for debugging
        sensor_data_container.update_reading(&sensor_reading_container); // Todo error checking for debugging
    }
    
    // Transmit, receive
    if (millis() - transmission_last_update > transmission_interval) {
        transmission_last_update = millis();
    
        transmit_IMU_sensor_reading(&sensor_reading_container, &client); // todo class
        reception_routine(&client, &sensor_data_container); // Todo class
    }    

    // Update lights
    if (millis() - light_last_update > light_period) {
        light_last_update = millis();

        light_controller.update();
        if (DEBUG) Serial.println("Light update");
        light_controller.set_pattern(&light_controller.CONNECTED_IDLE);
        light_controller.dump_pattern();
    }
    
    delay(update_delay);
  }

  // Todo separate timers for sensor sampling and transmission

  delay(RECONNECT_DELAY);
}