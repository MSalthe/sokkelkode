#pragma once

#include <Arduino.h>

#include "config.h"

struct IMU_sensor_reading {
    int16_t accel[3];
    int16_t gyro[3];
};

class SensorDataContainer_IMU {

    int16_t accel_x[MOVING_AVERAGE_LENGTH];
    int16_t accel_y[MOVING_AVERAGE_LENGTH];
    int16_t accel_z[MOVING_AVERAGE_LENGTH];
    int16_t* accel[3] = {accel_x, accel_y, accel_z};

    int16_t gyro_x[MOVING_AVERAGE_LENGTH];
    int16_t gyro_y[MOVING_AVERAGE_LENGTH];
    int16_t gyro_z[MOVING_AVERAGE_LENGTH];
    int16_t* gyro[3] = {gyro_x, gyro_y, gyro_z};

    int array_pointer = 0;

    int16_t get_average(int16_t array[MOVING_AVERAGE_LENGTH]);

    public: 
        // Constructor
        SensorDataContainer_IMU();

        void add_sample(int16_t accel_reading[3], int16_t gyro_reading[3]);
        
        IMU_sensor_reading get_reading(); // Returns the moving average of the sensor data
};