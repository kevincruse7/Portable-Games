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
 * Implementation of the sound module for the Arduino Mega 2560 using a passive buzzer.
 *
 * @author Kevin Cruse
 */
#ifdef __AVR_ATmega2560__
#include "sound.h"


#include <Arduino.h>
#include <Tone.cpp>


#define SOUND_BUZZER_PIN 36


void sound_init(void) {
    pinMode(SOUND_BUZZER_PIN, OUTPUT);
}


void sound_play(const Model* model, int frame_rate) {
    tone(SOUND_BUZZER_PIN, model->current_note, 1000 / frame_rate);
}


#endif
