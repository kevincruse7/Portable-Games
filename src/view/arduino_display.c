/**
 * Implementation of the display module for the Arduino Mega 2560, using a dot matrix LED display.
 *
 * @author Kevin Cruse
 */

#ifdef __AVR_ATmega2560__
#include "view/display.h"

#include <Arduino.h>
#include <errno.h>
#include <stdbool.h>

#include "model/model.h"

#define DISPLAY_DIN_PIN 22
#define DISPLAY_CS_PIN 23
#define DISPLAY_CLK_PIN 24

// Is the display device uninitialized?
static bool uninitialized = true;

// Serially writes the given data to the given address on the display
static void display_write_data(byte address, byte data);

void display_init(void) {

  pinMode(DISPLAY_DIN_PIN, OUTPUT);
  pinMode(DISPLAY_CS_PIN, OUTPUT);
  pinMode(DISPLAY_CLK_PIN, OUTPUT);

  display_write_data(0x09, 0x00);  // No data decoding
  display_write_data(0x0A, 0x00);  // Screen brightness (0 - F)
  display_write_data(0x0B, MODEL_BOARD_COLS - 1);  // Column scan limit
  display_write_data(0x0C, 0x01);  // Normal operation (shutdown mode)
  display_write_data(0x0F, 0x00);  // Normal operation (display test mode)

  uninitialized = false;
}

void display_render(struct Model *p_model) {

  if (uninitialized) {
    errno = EIO;
    return;
  }
  if (p_model == NULL) {
    errno = EINVAL;
    return;
  }

  for (int row = 0; row < MODEL_BOARD_ROWS; row++) {
    byte rowData = 0;
    for (int col = 0; col < MODEL_BOARD_COLS; col++) {
      if (p_model->board[row][col] == true) {
        rowData += B10000000 >> col;
      }
    }

    display_write_data(row + 1, rowData);
  }
}

static void display_write_data(byte address, byte data) {

  digitalWrite(DISPLAY_CS_PIN, LOW);

  shiftOut(DISPLAY_DIN_PIN, DISPLAY_CLK_PIN, MSBFIRST, address);
  shiftOut(DISPLAY_DIN_PIN, DISPLAY_CLK_PIN, MSBFIRST, data);

  digitalWrite(DISPLAY_CS_PIN, HIGH);
}

#endif  // __AVR_ATmega2560__