#include <ESP8266WiFi.h>
#include "wifi_client.h"
#include "config.h"
#include "wifi_client.h"

void wait_for_connection() {
    if (DEBUG) Serial.println("Waiting for WiFi connection.");
    while (WiFi.status() != WL_CONNECTED) {
        if (DEBUG) Serial.print(".");

        // Blink LED while we wait for WiFi
        digitalWrite(LED_BUILTIN, HIGH);
        delay(250);
        digitalWrite(LED_BUILTIN, LOW);
        delay(250);
    }
}

void connect_to_host(WiFiClient* client) {
  while(!client -> connect(host, httpPort)) {
    if (DEBUG) Serial.println("Server connection failed. Retrying...");
    wait_for_connection(); // Ensure we have a WiFi connection before attempting to connect to the server

    // Unique LED blink pattern to indicate host connection failure
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);

    delay(500);
  }
  if (DEBUG) Serial.println("Connected to server.");
}

void disconnect_error_handling(WiFiClient* client) {
    digitalWrite(LED_BUILTIN, HIGH); // Solid LED to indicates error state
    if (DEBUG) Serial.println("Disconnected from server. Error code: " + String(client -> getWriteError()));
    delay(50);
}