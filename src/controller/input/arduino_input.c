/**
 * Implementation of the input module for the Arduino Mega 2560.
 *
 * @author Kevin Cruse
 */

#ifdef __AVR_ATmega2560__

#include "input.h"

#include <Arduino.h>
#include <errno.h>
#include <stdint.h>

// Pin mappings to input buttons
#define INPUT_ACTION_PIN 28
#define INPUT_UP_PIN 29
#define INPUT_LEFT_PIN 30
#define INPUT_RIGHT_PIN 31
#define INPUT_DOWN_PIN 32

// Is the input device uninitialized?
static uint8_t uninitialized = 1;

void input_init(void) {

  pinMode(INPUT_ACTION_PIN, INPUT_PULLUP);
  pinMode(INPUT_UP_PIN, INPUT_PULLUP);
  pinMode(INPUT_LEFT_PIN, INPUT_PULLUP);
  pinMode(INPUT_RIGHT_PIN, INPUT_PULLUP);
  pinMode(INPUT_DOWN_PIN, INPUT_PULLUP);

  uninitialized = 0;
}

enum InputType input_get(enum Direction *p_direction) {

  if (uninitialized) {
    errno = EIO;
    return INPUT_TYPE_NONE;
  }
  if (p_direction == NULL) {
    errno = EINVAL;
    return INPUT_TYPE_NONE;
  }

  if (digitalRead(INPUT_ACTION_PIN) == LOW) {
    return INPUT_TYPE_ACTION;
  }
  if (digitalRead(INPUT_UP_PIN) == LOW) {
    *p_direction = DIRECTION_UP;
    return INPUT_TYPE_MOVE;
  }
  if (digitalRead(INPUT_LEFT_PIN) == LOW) {
    *p_direction = DIRECTION_LEFT;
    return INPUT_TYPE_MOVE;
  }
  if (digitalRead(INPUT_RIGHT_PIN) == LOW) {
    *p_direction = DIRECTION_RIGHT;
    return INPUT_TYPE_MOVE;
  }
  if (digitalRead(INPUT_DOWN_PIN) == LOW) {
    *p_direction = DIRECTION_DOWN;
    return INPUT_TYPE_MOVE;
  }

  return INPUT_TYPE_NONE;
}

#endif  // __AVR_ATmega2560__