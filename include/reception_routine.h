#pragma once

#include <ESP8266WiFi.h>

#include "sensor_data.h"

typedef enum Reception {
    RECEPTION_SUCCESS,
    RECEPTION_FAILURE,
    RECEPTION_NO_DATA
} Reception;

Reception reception_routine(WiFiClient* client, SensorDataContainer_IMU* sensor_data);