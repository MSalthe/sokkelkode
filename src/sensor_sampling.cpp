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

// SensorStatus sample_bmi160(SensorDataIMU* sensor_data, int oversamples = 5) {
//     int16_t bmi160_samples[6] = {0, 0, 0, 0, 0, 0};
//     int32_t bmi160_average[6] = {0, 0, 0, 0, 0, 0};

//     // Oversample the sensor data
//     for (int i = 0; i < oversamples; i++) {
//         if (bmi160.getSensorData(3, bmi160_samples)) { // 3 = both accel and gyro
//             return SENSOR_INIT_FAILURE; // Returns 1 if failure
//         }
//         for (int j = 0; j < 6; j++) {
//             bmi160_average[j] += bmi160_samples[j];
//         }
//     }   

//     // Average the oversampled data
//     for (int i = 0; i < 6; i++) {
//         bmi160_samples[i] = bmi160_average[i] / oversamples;
//     }

//     // Assign the averaged data to the sensor_data struct
//     for (int i = 0; i < 3; i++) {
//         sensor_data -> IMU[i] = bmi160_average[i];
//         sensor_data -> gyro[i] = bmi160_average[i + 3];
//     }

//     return SENSOR_INIT_SUCCESS;
// }

// SensorStatus sample_sensors(SensorDataIMU* sensor_data) {
//     return sample_bmi160(sensor_data);
// }