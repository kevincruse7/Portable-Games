#ifdef __AVR_ATmega2560__

#include "controller/input.h"

#include "Arduino.h"

#define KEYPAD_FIRST_ROW_PIN 28
#define KEYPAD_FIRST_COL_PIN 32

#define KEYPAD_NUM_ROWS 4
#define KEYPAD_NUM_COLS 4

static const char KEYS[KEYPAD_NUM_ROWS][KEYPAD_NUM_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

#define KEYPAD_UP '2'
#define KEYPAD_DOWN '5'
#define KEYPAD_LEFT '4'
#define KEYPAD_RIGHT '6'

void initInput(void) {

  for (int i = 0; i < KEYPAD_NUM_ROWS; i++) {
    pinMode(KEYPAD_FIRST_ROW_PIN + i, OUTPUT);
    digitalWrite(KEYPAD_FIRST_ROW_PIN + i, HIGH);
  }

  for (int i = 0; i < KEYPAD_NUM_COLS; i++) {
    pinMode(KEYPAD_FIRST_COL_PIN + i, INPUT_PULLUP);
  }
}

enum InputType getMoveInput(enum MoveType *move_type) {

  for (int row = 0; row < KEYPAD_NUM_ROWS; row++) {
    digitalWrite(KEYPAD_FIRST_ROW_PIN + row, LOW);

    for (int col = 0; col < KEYPAD_NUM_COLS; col++) {
      if (digitalRead(KEYPAD_FIRST_COL_PIN + col) == LOW) {
        digitalWrite(KEYPAD_FIRST_ROW_PIN + row, HIGH);

        switch (KEYS[row][col]) {
          case KEYPAD_UP:
            *move_type = UP;
            break;
          case KEYPAD_DOWN:
            *move_type = DOWN;
            break;
          case KEYPAD_LEFT:
            *move_type = LEFT;
            break;
          case KEYPAD_RIGHT:
            *move_type = RIGHT;
            break;
          default:
            return NONE;
        }

        return MOVE;
      }
    }

    digitalWrite(KEYPAD_FIRST_ROW_PIN + row, HIGH);
  }

  return NONE;
}

#endif