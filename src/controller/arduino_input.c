/**
 * Implementation of the input module for the Arduino Mega 2560.
 *
 * @author Kevin Cruse
 */

#ifdef __AVR_ATmega2560__
#include "controller/input.h"

#include <Arduino.h>
#include <errno.h>

// Pin mappings to input buttons
#define INPUT_ACTION_PIN 28
#define INPUT_UP_PIN 29
#define INPUT_LEFT_PIN 30
#define INPUT_RIGHT_PIN 31
#define INPUT_DOWN_PIN 32

// Is the input device uninitialized?
static bool uninitialized = true;

void input_init(void) {

  pinMode(INPUT_ACTION_PIN, INPUT_PULLUP);
  pinMode(INPUT_UP_PIN, INPUT_PULLUP);
  pinMode(INPUT_LEFT_PIN, INPUT_PULLUP);
  pinMode(INPUT_RIGHT_PIN, INPUT_PULLUP);
  pinMode(INPUT_DOWN_PIN, INPUT_PULLUP);

  uninitialized = false;
}

enum InputType input_get(enum MoveType *p_move_type) {

  if (uninitialized) {
    errno = EIO;
    return NONE;
  }
  if (p_move_type == NULL) {
    errno = EINVAL;
    return NONE;
  }

  if (digitalRead(INPUT_ACTION_PIN) == LOW) {
    return ACTION;
  }
  if (digitalRead(INPUT_UP_PIN) == LOW) {
    *p_move_type = UP;
    return MOVE;
  }
  if (digitalRead(INPUT_LEFT_PIN) == LOW) {
    *p_move_type = LEFT;
    return MOVE;
  }
  if (digitalRead(INPUT_RIGHT_PIN) == LOW) {
    *p_move_type = RIGHT;
    return MOVE;
  }
  if (digitalRead(INPUT_DOWN_PIN) == LOW) {
    *p_move_type = DOWN;
    return MOVE;
  }

  return NONE;
}

#endif  // __AVR_ATmega2560__