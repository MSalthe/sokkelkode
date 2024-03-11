#include "command_handler.h"

void dummy_function() {
    Serial.println("Dummy function");
}

void dummy_function_2(int value) {
    Serial.println("Dummy function");
    Serial.println(value);
}

CommandLine command_handler(JsonDocument deserialized_command) { // This is ugly af but since we're only implementing a few commands, the if chain should be fine
    String command      = deserialized_command["command"];
    int value           = deserialized_command["value"];

    if (command == "dummy") {
        dummy_function();
        return COMMAND_SUCCESS;
    }
    else if (command == "dummy_2") {
        dummy_function_2(value);
        return COMMAND_SUCCESS;
    }
    else if (command == "panic") {
        return COMMAND_PANIC;
    }
    
    return COMMAND_NOT_RECOGNIZED;
}