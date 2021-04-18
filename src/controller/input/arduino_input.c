/*
 * Copyright 2021 Kevin Matthew Cruse
 * This file is part of Portable Games.
 *
 * Portable Games is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Portable Games is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Portable Games. If not, see <https://www.gnu.org/licenses/>.
 */


/**
 * Implementation of the input module for the Arduino Mega 2560.
 *
 * @author Kevin Cruse
 */
#ifdef __AVR_ATmega2560__
#include "input.h"


#include <Arduino.h>


// Pin mappings to input buttons
#define INPUT_ACTION_PIN 28
#define INPUT_UP_PIN 29
#define INPUT_LEFT_PIN 30
#define INPUT_RIGHT_PIN 31
#define INPUT_DOWN_PIN 32


void input_init(void) {
    pinMode(INPUT_ACTION_PIN, INPUT_PULLUP);
    pinMode(INPUT_UP_PIN, INPUT_PULLUP);
    pinMode(INPUT_LEFT_PIN, INPUT_PULLUP);
    pinMode(INPUT_RIGHT_PIN, INPUT_PULLUP);
    pinMode(INPUT_DOWN_PIN, INPUT_PULLUP);
}


InputType input_get(Direction* direction) {
    // Read input pins and return corresponding enum value
    if (digitalRead(INPUT_ACTION_PIN) == LOW) {
        return INPUT_TYPE_ACTION;
    }
    if (digitalRead(INPUT_UP_PIN) == LOW) {
        *direction = DIRECTION_UP;
        return INPUT_TYPE_MOVE;
    }
    if (digitalRead(INPUT_LEFT_PIN) == LOW) {
        *direction = DIRECTION_LEFT;
        return INPUT_TYPE_MOVE;
    }
    if (digitalRead(INPUT_RIGHT_PIN) == LOW) {
        *direction = DIRECTION_RIGHT;
        return INPUT_TYPE_MOVE;
    }
    if (digitalRead(INPUT_DOWN_PIN) == LOW) {
        *direction = DIRECTION_DOWN;
        return INPUT_TYPE_MOVE;
    }

    return INPUT_TYPE_NONE;
}


#endif
