#include "transmission_routine.h"
#include "config.h"
#include <ArduinoJson.h>
#include "sensor_sampling.h"

SensorDataIMU sensor_data;

String package_sensor_data_JSON_lib(SensorDataIMU* sensor_data) {
    if (DEBUG) Serial.println("Packaging sensor data for JSON lib");
    
    JsonDocument doc;

    doc["accel"][0] = sensor_data -> IMU[0];
    doc["accel"][1] = sensor_data -> IMU[1];
    doc["accel"][2] = sensor_data -> IMU[2];

    doc["gyro"][0] = sensor_data -> gyro[0];
    doc["gyro"][1] = sensor_data -> gyro[1];
    doc["gyro"][2] = sensor_data -> gyro[2];

    String package;
    serializeJson(doc, package);

    if (DEBUG) Serial.println("Sensor data packaged for JSON lib: ");
    if (DEBUG) Serial.println(package);

    return package;
}

void transmit_sensor_data(SensorDataIMU sensor_data, WiFiClient* client) {
    if (DEBUG) Serial.println("Transmitting sensor data");
    String package = package_sensor_data_JSON_lib(&sensor_data);
    client -> print(package);
    if (DEBUG) Serial.println("Sensor data transmitted");
} 

Transmission transmission_routine(WiFiClient* client) {
    sample_sensors(&sensor_data);
    transmit_sensor_data(sensor_data, client);
    return TRANSMISSION_SUCCESS;
}