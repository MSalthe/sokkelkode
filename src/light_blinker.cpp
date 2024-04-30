#include "light_blinker.h"

Light_blinker::Light_blinker(int led_pin) {
    this -> led_pin = led_pin;
    pinMode(led_pin, OUTPUT);
}

void Light_blinker::set_interval(int off_time, int on_time) {
    interval[0] = off_time;
    interval[1] = on_time;
}

void Light_blinker::fastupdate(unsigned long* current_time, unsigned long* light_period) { // saves time on millis() calls
    if (*current_time - timestamp > interval[led_state]) {

        if (interval[!led_state] == 0) {
            return;
        } // Ensure stable lights stay stable

        led_state = !led_state;

        digitalWrite(led_pin, led_state);
        timestamp = *current_time;
    }
}

