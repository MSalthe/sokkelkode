#include "Arduino.h"
#include "config.h"

enum light_type {
    STATIC,
    BLINK
};

enum LED_state {
    OFF,
    ON
};

enum LED_setting {
    ACTIVE_LOW,
    ACTIVE_HIGH
};

struct LightPattern {
    light_type type;
    int strength = 10; // 0 - 10, only applies to static lights
    int on_time = 0; // ms, only applies to blink lights
    int off_time = 0; // ms, only applies to blink lights
};

class LightController {
    private:
        int current_frame = 1;
        int previous_frame = 0;
        int light_frames[LIGHT_FRAME_COUNT];
        LED_setting setting = ACTIVE_LOW;
        void generate_light_frames(LightPattern* pattern);
        void set_LED(LED_state state);
    
    public:
        LightPattern WAITING_FOR_CONNECTION = {light_type::BLINK, 0, 50, 950};
        LightPattern CONNECTED_IDLE = {light_type::STATIC, 1, 0, 0};
        LightPattern CONNECTED_ACTIVE = {light_type::STATIC, 10, 0, 0};

        LightController();
        void set_pattern(LightPattern* pattern);
        void update();        
        void dump_pattern();
};