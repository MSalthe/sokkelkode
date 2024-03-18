#include "main_routine.h"

// Timing
int sensor_update_interval = SENSOR_UPDATE_INTERVAL; // ms
unsigned long sensor_last_update = 0;

int transmission_interval = TRANSMISSION_INTERVAL; // ms
unsigned long transmission_last_update = 0;


void main_routine(WiFiClient* client, DFRobot_BMI160* bmi160, SensorDataContainer_IMU* sensor_data_container, IMU_sensor_reading* sensor_reading_container) {
    if (millis() - sensor_last_update > sensor_update_interval) {
        sensor_last_update = millis();
        
        sensor_data_container -> sample_IMU(); // Todo error checking for debugging
        sensor_data_container -> update_reading(sensor_reading_container); // Todo error checking for debugging
    }
    
    if (millis() - transmission_last_update > transmission_interval) {
        transmission_last_update = millis();
    
        transmit_IMU_sensor_reading(sensor_reading_container, client); // todo class
        reception_routine(client, sensor_data_container); // Todo class
    }    
}