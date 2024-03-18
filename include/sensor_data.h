#pragma once

#include <Arduino.h>
#include <DFRobot_BMI160.h>

#include "config.h"

typedef enum SensorStatus {
    SENSOR_INIT_SUCCESS,
    SENSOR_INIT_FAILURE,

    SENSOR_SAMPLE_SUCCESS,
    SENSOR_SAMPLE_FAILURE
} SensorStatus;

typedef struct IMU_sensor_reading {
    int16_t accel[3];
    int16_t gyro[3];
} IMU_sensor_reading;

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

    int16_t get_average_of_axis(int16_t* sensor_axis_moving_average, int len);

    public: 
        // Constructor
        SensorDataContainer_IMU();
        
        SensorStatus sample_IMU(); // Sample the IMU sensor and add the sample to the moving average

        void update_reading(IMU_sensor_reading* sensor_reading_container); 

        IMU_sensor_reading get_reading(); // Get the current reading from the IMU sensor
};