#include <ESP8266WiFi.h>
#include "WiFiClient.h"
#include "sensor_simulator.h"
#include "sensor_data.h"

typedef enum Transmission {
    TRANSMISSION_SUCCESS,
    TRANSMISSION_FAILURE_NO_JSON,
    TRANSMISSION_FAILURE_NO_TRANSMISSION
} Transmission;

typedef enum JSON_packaging_status {
    JSON_PACKAGING_SUCCESS,
    JSON_PACKAGING_FAILURE_ASSIGNMENT_FAILED,
    JSON_PACKAGING_FAILURE_SERIALIZATION_FAILED
} JSON_packaging_status;

Transmission transmit_IMU_sensor_reading(IMU_sensor_reading* IMU_sensor_reading, WiFiClient* client);