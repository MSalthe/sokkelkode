#include <Arduino.h>
#include "sensor_data.h"
#include "sensor_simulator.h"
#include "config.h"

// SensorDataIMU simulate_sensor_sample() {
//     if (DEBUG) Serial.println("Simulating sensor sample");
//     SensorDataIMU sensor_data;
//     for (auto IMU_value : sensor_data.IMU) {
//         IMU_value = random(0, 100);
//     }
//     for (auto gyro_value : sensor_data.gyro) {
//         gyro_value = random(0, 100);
//     }
//     return sensor_data;
// }