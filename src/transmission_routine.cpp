#include "transmission_routine.h"
#include "config.h"

SensorDataIMU sensor_data;

void transmit_sensor_data(SensorDataIMU sensor_data, WiFiClient* client) {
    if (DEBUG) Serial.println("Transmitting sensor data");
    client -> print(String("IMU: ") + sensor_data.IMU[0] + "," + sensor_data.IMU[1] + "," + sensor_data.IMU[2]);
    client -> print(String("Gyro: ") + sensor_data.gyro[0] + "," + sensor_data.gyro[1] + "," + sensor_data.gyro[2]);
    if (DEBUG) Serial.println("Sensor data transmitted");
} // Todo error type

Transmission transmission_routine(WiFiClient* client) {
    sensor_data = simulate_sensor_sample();
    transmit_sensor_data(sensor_data, client);
    return TRANSMISSION_SUCCESS; // Todo error handling
}