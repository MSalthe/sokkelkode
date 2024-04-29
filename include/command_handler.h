#include <ArduinoJson.h>
#include "config.h"
#include "sensor_data.h"
#include <ESP8266WiFi.h>

typedef enum CommandLine {
    COMMAND_SUCCESS,
    COMMAND_NOT_RECOGNIZED,
    VALUE_INVALID,
    COMMAND_PANIC
} CommandLine;

CommandLine command_handler(JsonDocument deserialized_command, SensorDataContainer_IMU* sensor_data, WiFiClient* client);