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
    int accel_moving_average_length = ACCEL_MOVING_AVERAGE_LENGTH;
    int gyro_moving_average_length = GYRO_MOVING_AVERAGE_LENGTH;

    int16_t* accel[3];
    int16_t* gyro[3];

    int array_pointer = 0;

    DFRobot_BMI160* bmi160;

    int16_t get_average_of_axis(int16_t* sensor_axis_moving_average, int len);

    public: 
        // Constructor, destructor
        SensorDataContainer_IMU(DFRobot_BMI160* bmi160);
        ~SensorDataContainer_IMU();

        // Settings
        void set_accel_moving_average_length(int length);
        void set_gyro_moving_average_length(int length);

        // Functionality        
        SensorStatus sample_IMU(); // Sample the IMU sensor and add the sample to the moving average

        void update_reading(IMU_sensor_reading* sensor_reading_container); 
        IMU_sensor_reading get_reading(); // Get the current reading from the IMU sensor
};