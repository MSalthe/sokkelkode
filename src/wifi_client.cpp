#include <ESP8266WiFi.h>
#include "wifi_client.h"
#include "config.h"

void inform_connection_error(wl_status_t status) { // TODO add light patterns
  if (DEBUG) Serial.print("\n");
  switch (status) {
    case WL_IDLE_STATUS : 
      if (DEBUG) Serial.print("IDLE");
      break;

    case WL_SCAN_COMPLETED : 
      if (DEBUG) Serial.print("SCANCOMPLETE");
      break;

    case WL_CONNECT_FAILED : 
      if (DEBUG) Serial.print("No wifi connection. Retrying.");
      break;

    case WL_WRONG_PASSWORD : 
      if (DEBUG) Serial.print("\"");
      if (DEBUG) Serial.print(WIFI_PASSWORD);
      if (DEBUG) Serial.print("\" is the wrong WiFi password! Retrying.");
      break;

    case WL_DISCONNECTED : 
      if (DEBUG) Serial.print("No server connection. Retrying.");
      break;  

    case WL_NO_SSID_AVAIL:
      if (DEBUG) Serial.print("ERROR: Could not find network with SSID \"");
      if (DEBUG) Serial.print(SSID_STRING);
      if (DEBUG) Serial.print("\". Waiting.");
      break;

    case WL_CONNECTION_LOST:
      if (DEBUG) Serial.print("Bruh.");
      break;

    default:
      if (DEBUG) Serial.println("WiFi driver PANICKED!");
      break;
  }
}

void wait_for_connection(wl_status_t previous_status) {

  while (WiFi.status() != WL_CONNECTED) {
    previous_status = WiFi.status();
    inform_connection_error(previous_status);

    while (WiFi.status() == previous_status) {
      if (DEBUG) Serial.print(".");
      delay(500);
    }
  } if (DEBUG) Serial.println(" Server connection established!");

}

void wait_for_client(WiFiClient* client) {
  client -> connect(SERVER_IP_STRING, SERVER_PORT);
  if (DEBUG) Serial.print("\nWaiting for client response on port ");
  if (DEBUG) Serial.print(SERVER_PORT);
  if (DEBUG) Serial.print(".");

  while (!client -> connected()) {
    if (WiFi.status() != WL_CONNECTED) {
      if (DEBUG) Serial.println("Connection to server lost!");
      return;
    }

    client -> connect(SERVER_IP_STRING, SERVER_PORT);
    if (DEBUG) Serial.print(".");
    delay(500);
  } if (DEBUG) Serial.println(" Server connection established!");
}

void connect_to_host(WiFiClient* client) {
  wl_status_t connection_status = WiFi.status();
  if (connection_status != WL_CONNECTED) wait_for_connection(connection_status);

  if (!client -> connected() && WiFi.status() == WL_CONNECTED) wait_for_client(client);
}

void disconnect_error_handling(WiFiClient* client) {
    digitalWrite(LED_BUILTIN, HIGH); // Solid LED to indicates error state
    if (DEBUG) Serial.println("Disconnected from server. Error code: " + String(client -> getWriteError()));
    delay(50);
}