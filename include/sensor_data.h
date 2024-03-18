#pragma once

struct SensorDataIMU {
    int16_t IMU[3]; // XYZ
    int16_t gyro[3]; // XYZ
};