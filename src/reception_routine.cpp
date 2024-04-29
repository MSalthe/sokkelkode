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

    JsonDocument filtered_deserialized_command;
    filtered_deserialized_command["command"] = command;
    if (deserialized_command.containsKey("flag")) {
        if (TELEMETRY_DEBUG) Serial.println("Added non-null flag: " + flag);
        filtered_deserialized_command["flag"] = flag;
    }
    if (deserialized_command.containsKey("value")) {
        if (TELEMETRY_DEBUG) Serial.println("Added non-null value: " + String(value));
        filtered_deserialized_command["value"] = value;
    }

    if (TELEMETRY_DEBUG) {
        Serial.println("Deserialized command: ");
        Serial.println(command);
        Serial.println(flag);
        Serial.println(value);
    }

    return filtered_deserialized_command;
}

Reception reception_routine(WiFiClient* client, SensorDataContainer_IMU* sensor_data) {
    if (client -> peek() == -1) {
        //if (TELEMETRY_DEBUG) Serial.println("Received no data.");
        return RECEPTION_NO_DATA;
    }
    
    String buffer = "";
    while (client -> available()) {
        buffer += char(client -> read());
    }

    if (TELEMETRY_DEBUG) Serial.println("Received data: ");
    if (TELEMETRY_DEBUG) Serial.println(buffer);

    JsonDocument deserialized_command = deserialize_command(buffer);
    if (command_handler(deserialized_command, sensor_data, client) == COMMAND_NOT_RECOGNIZED) {
        if (DEBUG) Serial.print("Command not recognized: ");
        if (DEBUG) Serial.print(String(deserialized_command["command"]));
        if (DEBUG) Serial.print(" ");
        if (DEBUG) Serial.print(String(deserialized_command["flag"]));
        if (DEBUG) Serial.print(" ");
        if (DEBUG) Serial.println(String(deserialized_command["value"]));
        
    }

    return RECEPTION_SUCCESS;
}