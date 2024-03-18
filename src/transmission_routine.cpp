#include "transmission_routine.h"
#include "config.h"
#include <ArduinoJson.h>

extern SensorDataContainer_IMU sensor_data;

String json_string;

static JSON_packaging_status package_IMU_sensor_reading_JSON(IMU_sensor_reading* sensor_reading, String* json_string) {    
    JsonDocument doc;

    doc["accel"][0] = sensor_reading -> accel[0];
    doc["accel"][1] = sensor_reading -> accel[1];
    doc["accel"][2] = sensor_reading -> accel[2];

    doc["gyro"][0] = sensor_reading -> gyro[0];
    doc["gyro"][1] = sensor_reading -> gyro[1];
    doc["gyro"][2] = sensor_reading -> gyro[2];

    String package;
    
    serializeJson(doc, package); // Warning: no error checking

    if (TELEMETRY_DEBUG) Serial.println("Sensor data packaged for JSON lib: ");
    if (TELEMETRY_DEBUG) Serial.println(package);

    *json_string = package;

    return JSON_PACKAGING_SUCCESS;
}

Transmission transmit_IMU_sensor_reading(IMU_sensor_reading* sensor_reading, WiFiClient* client) {
    if (package_IMU_sensor_reading_JSON(sensor_reading, &json_string) != JSON_PACKAGING_SUCCESS) {
        return TRANSMISSION_FAILURE_NO_JSON;
    }
    
    if (client -> print(json_string) == 0) {
        return TRANSMISSION_FAILURE_NO_TRANSMISSION;
    }

    return TRANSMISSION_SUCCESS;
} 