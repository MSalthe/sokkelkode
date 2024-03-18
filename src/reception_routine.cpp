#include "reception_routine.h"
#include "config.h"
#include <ArduinoJson.h>
#include "command_handler.h"

JsonDocument deserialize_command(String raw_command) {
    JsonDocument deserialized_command;
    deserializeJson(deserialized_command, raw_command);

    String command      = deserialized_command["command"];
    String flag         = deserialized_command["flag"];
    int value           = deserialized_command["value"];

    if (TELEMETRY_DEBUG) {
        Serial.println("Deserialized command: ");
        Serial.println(command);
        Serial.println(flag);
        Serial.println(value);
    }

    return deserialized_command;
}

Reception reception_routine(WiFiClient* client, SensorDataContainer_IMU* sensor_data) {
    if (client -> peek() == -1) {
        if (TELEMETRY_DEBUG) Serial.println("Received no data.");
        return RECEPTION_NO_DATA;
    }
    
    String buffer = "";
    while (client -> available()) {
        buffer += char(client -> read());
    }

    if (TELEMETRY_DEBUG) Serial.println("Received data: ");
    if (TELEMETRY_DEBUG) Serial.println(buffer);

    JsonDocument deserialized_command = deserialize_command(buffer);
    if (command_handler(deserialized_command, sensor_data) == COMMAND_NOT_RECOGNIZED) {
        if (DEBUG) Serial.println("Command not recognized.");
    }

    return RECEPTION_SUCCESS;
}