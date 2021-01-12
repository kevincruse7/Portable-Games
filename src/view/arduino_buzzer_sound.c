#ifdef __AVR_ATmega2560__

#include "view/sound.h"

#include <Arduino.h>
#include <Tone.cpp>

#include "controller/controller.h"

#define SOUND_BUZZER_PIN 38

void initSound(void) {

  pinMode(SOUND_BUZZER_PIN, OUTPUT);
}

void playMovementSound(void) {

  tone(SOUND_BUZZER_PIN, 440, 500 / CONTROLLER_MAIN_TICK_RATE);
}

#endif