#include "sensor_data.h"

SensorDataContainer_IMU::SensorDataContainer_IMU() {
    // Initialize the arrays to 0
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < MOVING_AVERAGE_LENGTH; j++) {
            accel[i][j] = 0;
            gyro[i][j] = 0;
        }
    }
}

int16_t SensorDataContainer_IMU::get_average(int16_t array[MOVING_AVERAGE_LENGTH]) {
    int32_t sum = 0;
    for (int i = 0; i < MOVING_AVERAGE_LENGTH; i++) {
        sum += array[i];
    }
    return sum / MOVING_AVERAGE_LENGTH;
}

void SensorDataContainer_IMU::add_sample(int16_t accel_reading[3], int16_t gyro_reading[3]) {

}