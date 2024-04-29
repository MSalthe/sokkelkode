#pragma once

#include <ESP8266WiFi.h>
#include "WiFiClient.h"

void wait_for_connection(wl_status_t previous_status);
void connect_to_host(WiFiClient* client);
void disconnect_error_handling(WiFiClient* client);
void handshake_protocol(WiFiClient* client);