/**
 * Implementation of the sound module for the Arduino Mega 2560, using a passive buzzer.
 *
 * @author Kevin Cruse
 */

#ifdef __AVR_ATmega2560__
#include "view/sound.h"

#include <Arduino.h>
#include <errno.h>
#include <stdbool.h>
#include <Tone.cpp>

#include "controller/controller.h"

#define SOUND_BUZZER_PIN 36

// Is the sound device uninitialized?
static bool uninitialized = true;

void sound_init(void) {

  pinMode(SOUND_BUZZER_PIN, OUTPUT);

  uninitialized = false;
}

void sound_movement_play(void) {

  if (uninitialized) {
    errno = EIO;
    return;
  }

  tone(SOUND_BUZZER_PIN, 220, 500 / CONTROLLER_RENDER_TICK_RATE);
}

#endif  // __AVR_ATmega2560__