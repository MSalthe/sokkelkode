#ifndef CONFIG_H
#define CONFIG_H 1

// Debugging
#define DEBUG 0
#define TELEMETRY_DEBUG 0

// Wifi credentials
#define SSID_STRING "Dexteritas"
#define WIFI_PASSWORD "12345678"

// Server credentials
#define SERVER_IP_STRING "10.42.0.1"
#define SERVER_PORT      5001

// Sensor sampling defaults
#define ACCEL_MOVING_AVERAGE_LENGTH 5
#define GYRO_MOVING_AVERAGE_LENGTH 10

// Timing defaults
#define RECONNECT_DELAY 1000 // ms
#define SENSOR_UPDATE_INTERVAL 10 // ms
#define TRANSMISSION_INTERVAL 100 // ms // Note: should be increased during runtime by Game Master

// Lights
#define LIGHT_PIN 1
#define LIGHT_INTERVAL 1000 // ms
#define LIGHT_FRAME_COUNT 100
#define LIGHT_IDLE_TIMOUT 50 // ms
#define LIGHT_ACTIVE_TIMOUT 1000 // ms

#endif