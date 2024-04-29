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
        for (int frame = 0; frame < LIGHT_FRAME_COUNT; frame++) {
            if (pattern -> strength > frame * 10 / LIGHT_FRAME_COUNT) {
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
        digitalWrite(3, !state);
    } else {
        digitalWrite(3, state);
    }
}

void LightController::set_pattern(LightPattern* pattern) {
    if (DEBUG) Serial.println("Generating pattern...");
    generate_light_frames(pattern);
    //current_frame = 0;
}

void LightController::update() {
    current_frame += 1;
    if (DEBUG) Serial.print("Current frame: ");
    if (DEBUG) Serial.println(current_frame);

    // Ensure static lights don't flicker
    if (light_frames[current_frame] == light_frames[previous_frame]) {
        return;
    }

    previous_frame = current_frame;

    if (light_frames[current_frame]) {
        set_LED(ON);
    } else {
        set_LED(OFF);
    }
    
    if (DEBUG) Serial.println(light_frames[current_frame]);

    for (int frame = 0; frame < LIGHT_FRAME_COUNT; frame++) {
        if (DEBUG) Serial.print(light_frames[frame]);
    }

    if (DEBUG) Serial.println();
    if (DEBUG) Serial.print("New frame: ");
    if (DEBUG) Serial.print(current_frame);
    if (DEBUG) Serial.println();
    // if (current_frame >= LIGHT_FRAME_COUNT) {
    //     current_frame = 0;
    // }
}

void LightController::dump_pattern() {
    for (int frame : light_frames) {
        Serial.print(frame);
    }
    Serial.println();
}