#include "sensor_data.h"
#include <vector>

// Constructor, destructor

SensorDataContainer_IMU::SensorDataContainer_IMU(DFRobot_BMI160* bmi160) 
    : bmi160(bmi160) {
    for (int i = 0; i < 3; i++) {
        accel[i] = new int16_t[accel_moving_average_length];
        gyro[i] = new int16_t[gyro_moving_average_length];
    }
}

SensorDataContainer_IMU::~SensorDataContainer_IMU() {
    for (int i = 0; i < 3; i++) {
        delete[] accel[i];
        delete[] gyro[i];
    }
}

// Settings

void SensorDataContainer_IMU::set_accel_moving_average_length(int length) {
    accel_moving_average_length = length;
}

void SensorDataContainer_IMU::set_gyro_moving_average_length(int length) {
    gyro_moving_average_length = length;
}

// Functionality

// Sample IMU, update arrays.
// Moves the array pointer to the next position, and if the array is full, it resets the pointer to 0.
// This saves processing power by not moving more than one element in the array for each sample.
SensorStatus SensorDataContainer_IMU::sample_IMU() {
    int16_t IMU_sample[6];
    if (bmi160 -> getSensorData(3, IMU_sample)) {
        return SENSOR_SAMPLE_FAILURE; 
    }

    array_pointer++;
    if (array_pointer >= accel_moving_average_length) {
        array_pointer = 0;
    }

    for (int i = 0; i < 3; i++) {
        accel[i][array_pointer] = IMU_sample[i];
        gyro[i][array_pointer] = IMU_sample[i+3];
    }

    return SENSOR_SAMPLE_SUCCESS;
}

// Update reading. Runs on demand to save processing power [can sample IMU without updating reading].
void SensorDataContainer_IMU::update_reading(IMU_sensor_reading* sensor_reading_container) { 
    for (int i = 0; i < 3; i++) {
        sensor_reading_container -> accel[i] = get_average_of_axis(accel[i], accel_moving_average_length);
        sensor_reading_container -> gyro[i] = get_average_of_axis(gyro[i], gyro_moving_average_length);
    }
}

// Adheres to functional programming principles, but is probably slower.
IMU_sensor_reading SensorDataContainer_IMU::get_reading() { 
    IMU_sensor_reading sensor_reading_container;
    update_reading(&sensor_reading_container);
    return sensor_reading_container;
}

// Helper functions
int16_t SensorDataContainer_IMU::get_average_of_axis(int16_t* sensor_moving_average, int len) { // Can be generalized in the future
    int32_t sum = 0;

    for (int i = 0; i < len; i++) {
        sum += sensor_moving_average[i];
    }

    return sum / len;
}