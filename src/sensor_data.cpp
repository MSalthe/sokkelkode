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

int16_t SensorDataContainer_IMU::get_average_of_axis(int16_t* sensor_moving_average, int len) { // Can be generalized
    int32_t sum = 0;

    for (int i = 0; i < len; i++) {
        sum += sensor_moving_average[i];
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

void SensorDataContainer_IMU::update_reading(IMU_sensor_reading* sensor_reading_container) { // Updates a container instead of returning a reading. Faster.
    for (int i = 0; i < 3; i++) {
        sensor_reading_container -> accel[i] = get_average_of_axis(accel[i], MOVING_AVERAGE_LENGTH);
        sensor_reading_container -> gyro[i] = get_average_of_axis(gyro[i], MOVING_AVERAGE_LENGTH);
    }
}

IMU_sensor_reading SensorDataContainer_IMU::get_reading() { // Returns current reading instead of updating a container. Slower.
    IMU_sensor_reading sensor_reading_container;
    update_reading(&sensor_reading_container);
    return sensor_reading_container;
}