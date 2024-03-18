#ifndef CONFIG_H
#define CONFIG_H 1

// Debugging
#define DEBUG 1
#define TELEMETRY_DEBUG 0

// Wifi credentials
#define SSID_STRING "esptest"
#define WIFI_PASSWORD "12345678"

// Server credentials
#define SERVER_IP_STRING "192.168.177.206"
#define SERVER_PORT 7090

// Sensor sampling defaults
#define ACCEL_MOVING_AVERAGE_LENGTH 10
#define GYRO_MOVING_AVERAGE_LENGTH 50

// Timing defaults
#define RECONNECT_DELAY 1000 // ms
#define SENSOR_UPDATE_INTERVAL 100 // ms
#define TRANSMISSION_INTERVAL 1000 // ms

#endif