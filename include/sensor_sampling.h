#pragma once

#include <DFRobot_BMI160.h>
#include "sensor_data.h"

enum SensorStatus {
    SENSOR_INIT_SUCCESS,
    SENSOR_INIT_FAILURE
};

SensorStatus init_sensors();

//SensorStatus sample_sensors(SensorDataIMU* sensor_data);