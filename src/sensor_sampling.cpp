#include "sensor_sampling.h"

DFRobot_BMI160 bmi160;

SensorStatus init_sensors() {
    if (bmi160.I2cInit(BMI160_I2C_ADDR) != 0) {
        Serial.println("BMI160 init failed!");
        return SENSOR_INIT_FAILURE;
    }
    Serial.println("BMI160 init SUCCESS!");
    return SENSOR_INIT_SUCCESS;
}

SensorStatus sample_bmi160(SensorDataIMU* sensor_data) {
    int16_t bmi160_samples[6];
    if (bmi160.getSensorData(3, bmi160_samples)) { // 3 = both accel and gyro
        return SENSOR_INIT_FAILURE; // Returns 1 if failure
    } 

    for (int i = 0; i < 3; i++) {
        sensor_data -> IMU[i] = bmi160_samples[i];
        sensor_data -> gyro[i] = bmi160_samples[i + 3];
    }
    return SENSOR_INIT_SUCCESS;
}

SensorStatus sample_sensors(SensorDataIMU* sensor_data) {
    return sample_bmi160(sensor_data);
}