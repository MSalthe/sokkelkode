#ifndef CONFIG_H
#define CONFIG_H 1

// Debugging
#define DEBUG 0
#define TELEMETRY_DEBUG 0

// Wifi credentials
#define SSID_STRING "esptest"
#define WIFI_PASSWORD "12345678"

// Server credentials
#define SERVER_IP_STRING "192.168.123.206"
#define SERVER_PORT      5050

// Sensor sampling defaults
#define ACCEL_MOVING_AVERAGE_LENGTH 5
#define GYRO_MOVING_AVERAGE_LENGTH 10

// Timing defaults
#define RECONNECT_DELAY 1000 // ms
#define SENSOR_UPDATE_INTERVAL 1 // ms
#define TRANSMISSION_INTERVAL 10 // ms

// Lights
#define LIGHT_PIN 1
#define LIGHT_INTERVAL 1000 // ms
#define LIGHT_FRAME_COUNT 100

#endif