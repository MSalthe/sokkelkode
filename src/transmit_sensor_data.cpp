#include <ESP8266WiFi.h>
#include "sensor_data.h"
#include "config.h" // wificlient

void transmit_sensor_data(SensorData sensor_data) {
    client.print(String("IMU: ") + sensor_data.IMU[0] + "," + sensor_data.IMU[1] + "," + sensor_data.IMU[2] + "\r\n");
    client.print(String("Gyro: ") + sensor_data.gyro[0] + "," + sensor_data.gyro[1] + "," + sensor_data.gyro[2] + "\r\n");
}