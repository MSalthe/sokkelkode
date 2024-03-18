#include "sensor_data.h"
#include "transmission_routine.h"
#include "reception_routine.h"

// Timing
extern int sensor_update_interval; // ms
extern unsigned long sensor_last_update;

extern int transmission_interval; // ms
extern unsigned long transmission_last_update;

void main_routine(WiFiClient* client, DFRobot_BMI160* bmi160, SensorDataContainer_IMU* sensor_data_container, IMU_sensor_reading* sensor_reading_container);