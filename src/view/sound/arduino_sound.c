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
