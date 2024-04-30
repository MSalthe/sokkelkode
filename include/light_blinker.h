#include <Arduino.h>

class Light_blinker {
    private:
        unsigned long timestamp = millis();
        int led_pin = 1;
        int led_state = 0;
        unsigned long interval[2] = {50, 950}; // on_time, off_time; ms

    public:
        Light_blinker(int led_pin);

        void fastupdate(unsigned long* milliseconds, unsigned long* light_period);
        void set_interval(int on_time, int off_time);
};