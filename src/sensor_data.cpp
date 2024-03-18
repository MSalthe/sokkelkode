#include "sensor_data.h"

extern DFRobot_BMI160 bmi160;

SensorDataContainer_IMU::SensorDataContainer_IMU() {
    // Initialize the arrays to 0
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < MOVING_AVERAGE_LENGTH; j++) {
            accel[i][j] = 0;
            gyro[i][j] = 0;
        }
    }
}

int16_t SensorDataContainer_IMU::get_average(int16_t* array[MOVING_AVERAGE_LENGTH]) {
    int32_t sum = 0;

    for (int i = 0; i < MOVING_AVERAGE_LENGTH; i++) {
        sum += *array[i];
    }

    return sum / MOVING_AVERAGE_LENGTH;
}


SensorStatus SensorDataContainer_IMU::sample_IMU() {
    int16_t IMU_sample[6];
    if (bmi160.getSensorData(3, IMU_sample)) { // Returns 1 if failed
        return SENSOR_SAMPLE_FAILURE; 
    }

    for (int i = 0; i < 3; i++) {
        accel[i][array_pointer] = IMU_sample[i];
        gyro[i][array_pointer] = IMU_sample[i+3];
    }

    return SENSOR_SAMPLE_SUCCESS;
}

IMU_sensor_reading SensorDataContainer_IMU::get_reading(IMU_sensor_reading* sensor_reading_container) {
    IMU_sensor_reading reading;

    for (int i = 0; i < 3; i++) {
        reading.accel[i] = get_average(&accel[i]);
        reading.gyro[i] = get_average(&gyro[i]);
    }

    return reading;
}