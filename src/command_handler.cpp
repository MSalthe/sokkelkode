#include "command_handler.h"

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
    
    if (flag == "sensor") {
        sensor_update_interval = value;
    }else if (flag == "transmission") {
        transmission_interval = value;
    }
}

CommandLine command_handler(JsonDocument deserialized_command, SensorDataContainer_IMU* sensor_data) { // This is ugly af but since we're only implementing a few commands, the if chain with 1000 parameters should be fine
    String command      = deserialized_command["command"];
    String flag         = deserialized_command["flag"];
    int value           = deserialized_command["value"];

    if (command == "dummy") {
        dummy_function();
        return COMMAND_SUCCESS;
    }else if (command == "dummy_2") {
        dummy_function_2(value);
        return COMMAND_SUCCESS;
    }else if (command == "panic") {
        return COMMAND_PANIC;
    }else if(command == "setmovingaverage") {
        set_moving_average(flag, value, sensor_data);
        return COMMAND_SUCCESS;
    }else if(command == "setupdateinterval") {
        set_update_interval(flag, value, sensor_data);
        return COMMAND_SUCCESS;
    }
    
    return COMMAND_NOT_RECOGNIZED;
}