#include <ArduinoJson.h>

typedef enum CommandLine {
    COMMAND_SUCCESS,
    COMMAND_NOT_RECOGNIZED,
    VALUE_INVALID,
    COMMAND_PANIC
} CommandLine;

CommandLine command_handler(JsonDocument deserialized_command);