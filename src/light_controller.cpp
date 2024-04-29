#include "light_controller.h"

LightController::LightController() {
    generate_light_frames(&WAITING_FOR_CONNECTION);
    current_frame = 0;
}

void LightController::generate_light_frames(LightPattern* pattern) {
    for (int frame = 0; frame < LIGHT_FRAME_COUNT; frame++) {
        light_frames[frame] = 0;
    }
    
    if (pattern -> type == BLINK) {
        int on_frames = (pattern -> on_time / LIGHT_INTERVAL) * LIGHT_FRAME_COUNT;
        if(DEBUG) Serial.println(on_frames);

        for (int frame = 0; frame < LIGHT_FRAME_COUNT; frame++) {
            if (frame < on_frames) {
                light_frames[frame] = 1;
            } else {
                light_frames[frame] = 0;
            }
        }
    }

    if (pattern -> type == STATIC) {
        // Alternate between on and off at frequency specified by strength
        for(int frame = 0; frame < LIGHT_FRAME_COUNT; frame++) {
            if (frame % (11 - pattern -> strength) == 0) {
                light_frames[frame] = 1;
            } else {
                light_frames[frame] = 0;
            }
        }
    }

    // Todo add subdivisions for more complex patterns
}

void LightController::set_LED(LED_state state) {
    if (setting == ACTIVE_LOW) {
        digitalWrite(1, !state);
    } else {
        digitalWrite(1, state);
    }
}

void LightController::set_pattern(LightPattern* pattern) {
    if (DEBUG) Serial.println("Generating pattern...");
    generate_light_frames(pattern);
    //current_frame = 0;
}

void LightController::update() {
    current_frame += 1;
    if (current_frame >= LIGHT_FRAME_COUNT) {
        current_frame = 0; // jank
    }

    // Ensure static lights don't flicker
    if (light_frames[current_frame] == light_frames[previous_frame]) {
        return;
    }
    previous_frame = current_frame;

    if (light_frames[current_frame]) {
        digitalWrite(1, HIGH);
    } else {
        digitalWrite(1, LOW);
    }
}

void LightController::dump_pattern() {
    for (int frame : light_frames) {
        Serial.print(frame);
    }
    Serial.println();
}