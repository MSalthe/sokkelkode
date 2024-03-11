#include "transmission_routine.h"
#include "config.h"

SensorDataIMU sensor_data;

String package_sensor_data_HTTP(SensorDataIMU* sensor_data, WiFiClient* client) {
    if (DEBUG) Serial.println("Packaging sensor data for HTTP");
    
    String package = 
        "GET /data?IMU=" 
            + String(sensor_data -> IMU[0]) 
            + "," + String(sensor_data -> IMU[1]) 
            + "," + String(sensor_data -> IMU[2]) 
        + "&gyro=" 
            + String(sensor_data -> gyro[0]) 
            + "," + String(sensor_data -> gyro[1]) 
            + "," + String(sensor_data -> gyro[2])
        + " HTTP/1.1\r\n" 
        + "Host: " + SERVER_IP_STRING + "\r\n" 
        + "Connection: close\r\n\r\n";

    if (DEBUG) Serial.println("Sensor data packaged for HTTP: ");
    if (DEBUG) Serial.println(package);

    return package;
}

String package_sensor_data_JSON(SensorDataIMU* sensor_data) {
    if (DEBUG) Serial.println("Packaging sensor data for JSON");
    
    String package = 
        "{"
            "\"IMU\": [" 
                + String(sensor_data -> IMU[0]) 
                + "," + String(sensor_data -> IMU[1]) 
                + "," + String(sensor_data -> IMU[2]) 
            + "],"
            "\"gyro\": [" 
                + String(sensor_data -> gyro[0]) 
                + "," + String(sensor_data -> gyro[1]) 
                + "," + String(sensor_data -> gyro[2]) 
            + "]"
        "}";

    if (DEBUG) Serial.println("Sensor data packaged for JSON: ");
    if (DEBUG) Serial.println(package);

    return package;
}

void transmit_sensor_data(SensorDataIMU sensor_data, WiFiClient* client) {
    if (DEBUG) Serial.println("Transmitting sensor data");
    String package = package_sensor_data_JSON(&sensor_data);
    client -> print(package);
    if (DEBUG) Serial.println("Sensor data transmitted");
} // Todo error type

Transmission transmission_routine(WiFiClient* client) {
    sensor_data = simulate_sensor_sample();
    transmit_sensor_data(sensor_data, client);
    return TRANSMISSION_SUCCESS; // Todo error handling
}