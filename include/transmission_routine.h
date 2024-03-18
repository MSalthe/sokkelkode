#include <ESP8266WiFi.h>
#include "WiFiClient.h"
#include "sensor_simulator.h"
#include "sensor_data.h"

typedef enum Transmission {
    TRANSMISSION_SUCCESS,
    TRANSMISSION_FAILURE
} Transmission;

void transmit_sensor_data(SensorDataIMU sensor_data, WiFiClient* client);
Transmission transmission_routine(WiFiClient* client);
void test_sensor_sampling();