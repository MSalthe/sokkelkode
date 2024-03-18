#pragma once

#include <Arduino.h>
#include <DFRobot_BMI160.h>

#include "config.h"

enum SensorStatus {
    SENSOR_INIT_SUCCESS,
    SENSOR_INIT_FAILURE,

    SENSOR_SAMPLE_SUCCESS,
    SENSOR_SAMPLE_FAILURE
};

struct IMU_sensor_reading {
    int16_t accel[3];
    int16_t gyro[3];
};

// Optimized for fewer operations -> better battery life
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

    int16_t get_average(int16_t* array[MOVING_AVERAGE_LENGTH]);

    public: 
        // Constructor
        SensorDataContainer_IMU();
        
        SensorStatus sample_IMU(); // Sample the IMU sensor and add the sample to the moving average

        IMU_sensor_reading get_reading(IMU_sensor_reading* sensor_reading_container); // Returns the moving average of the sensor data
};