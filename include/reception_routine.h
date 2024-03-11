#include <ESP8266WiFi.h>

typedef enum Reception {
    RECEPTION_SUCCESS,
    RECEPTION_FAILURE
} Reception;

Reception reception_routine(WiFiClient* client);