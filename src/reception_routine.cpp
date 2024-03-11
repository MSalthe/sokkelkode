#include "reception_routine.h"
#include "config.h"

Reception reception_routine(WiFiClient* client) {
    if (client -> read() != -1) {
        if (DEBUG) Serial.println("Received data.");
        return RECEPTION_SUCCESS;
    } else {
        if (DEBUG) Serial.println("Received no data.");
        return RECEPTION_FAILURE;
    }
}