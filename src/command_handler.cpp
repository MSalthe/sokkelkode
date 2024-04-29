#include "command_handler.h"

extern int session_id;
extern int client_id;
extern bool handshake_complete;
extern int sensor_update_interval;
extern int transmission_interval;

void dummy_function() {
    if (DEBUG)Serial.println("Dummy function");
}

void dummy_function_2(int value) {
    if (DEBUG)Serial.println("Dummy function");
    if (DEBUG)Serial.println(value);
}

void set_moving_average(String flag, int value, SensorDataContainer_IMU* sensor_data_container) {
    if (DEBUG) Serial.print("\nSet moving average for " + flag + " to " + value + "\n");
    
    if (flag == "accel") {
        sensor_data_container -> set_accel_moving_average_length(value);
    }else if (flag == "gyro") {
        sensor_data_container -> set_accel_moving_average_length(value);
    }
}

void set_update_interval(String flag, int value, SensorDataContainer_IMU* sensor_data_container) {
    if (DEBUG) Serial.print("\nSet update interval for " + flag + " to " + value + "\n");
    
    if (flag == "sampling") {
        sensor_update_interval = value;
    }else if (flag == "transmission") {
        transmission_interval = value;
    }
}

void request_id(WiFiClient* client) {
    client -> print(session_id);
    client -> print(",");
    client -> print(client_id);
    
    if (DEBUG) Serial.print("\nSent session and client id: \n");
    if (DEBUG) Serial.print(session_id);
    if (DEBUG) Serial.print(",");
    if (DEBUG) Serial.print(client_id);
}

void set_id(int value) {
    client_id = value;
    if (DEBUG) Serial.print("\nSet client id to ");
    if (DEBUG) Serial.print(value);
    if (DEBUG) Serial.print("\n");

    if (DEBUG) Serial.print("Client id: ");
    if (DEBUG) Serial.print(client_id);
}

void set_session_id(int value) {
    session_id = value;
    if (DEBUG) Serial.print("\nSet session id to ");
    if (DEBUG) Serial.print(value);
    if (DEBUG) Serial.print("\n");

    if (DEBUG) Serial.print("Session id: ");
    if (DEBUG) Serial.print(session_id);
}

void start() {
    handshake_complete = true;
}

CommandLine command_handler(JsonDocument deserialized_command, SensorDataContainer_IMU* sensor_data, WiFiClient* client) { // This is ugly af but since we're only implementing a few commands, the if chain with 1000 parameters should be fine
    String command      = deserialized_command["command"];
    String flag         = deserialized_command["flag"];
    int value           = deserialized_command["value"];

    if (command == "dummy") {
        dummy_function();
        return COMMAND_SUCCESS;
    }else if (command == "dummy_2") {
        dummy_function_2(value);
        return COMMAND_SUCCESS;
    }else if(command == "setmovingaverage") {
        set_moving_average(flag, value, sensor_data);
        return COMMAND_SUCCESS;
    }else if(command == "setupdateinterval") {
        set_update_interval(flag, value, sensor_data);
        return COMMAND_SUCCESS;
    }else if(command == "request_id") {
        request_id(client);
        return COMMAND_SUCCESS;
    }else if (command == "set_id") {
        set_id(value);
        return COMMAND_SUCCESS;
    }else if (command == "set_session_id") {
        set_session_id(value);
        return COMMAND_SUCCESS;
    }else if (command == "start") {
        start();
        return COMMAND_SUCCESS;
    }
    return COMMAND_NOT_RECOGNIZED;
}