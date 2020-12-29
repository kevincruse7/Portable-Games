#ifdef __AVR_ATmega2560__

#include "view/display.h"

#include <Arduino.h>

#define DISPLAY_DIN_PIN 22
#define DISPLAY_CS_PIN 23
#define DISPLAY_CLK_PIN 24

// Dot matrix display brightness (0-15)
#define DISPLAY_SCREEN_BRIGHTNESS 0

static void displayWriteData(byte address, byte data);

void initDisplay(void) {

  pinMode(DISPLAY_DIN_PIN, OUTPUT);
  pinMode(DISPLAY_CS_PIN, OUTPUT);
  pinMode(DISPLAY_CLK_PIN, OUTPUT);

  displayWriteData(0x09, 0);  // No data decoding
  displayWriteData(0x0A, DISPLAY_SCREEN_BRIGHTNESS);  // Screen brightness
  displayWriteData(0x0B, MODEL_BOARD_NUM_COLS - 1);  // Column scan limit
  displayWriteData(0x0C, 1);  // Normal operation (shutdown mode)
  displayWriteData(0x0F, 0);  // Normal operation (display test mode)
}

void displayBoard(unsigned char board[MODEL_BOARD_NUM_ROWS][MODEL_BOARD_NUM_COLS]) {

  for (int row = 0; row < MODEL_BOARD_NUM_ROWS; row++) {
    byte rowData = 0;
    for (int col = 0; col < MODEL_BOARD_NUM_COLS; col++) {
      if (board[row][col] == 1) {
        rowData += B10000000 >> col;
      }
    }

    displayWriteData(row + 1, rowData);
  }
}

static void displayWriteData(byte address, byte data) {

  digitalWrite(DISPLAY_CS_PIN, LOW);

  shiftOut(DISPLAY_DIN_PIN, DISPLAY_CLK_PIN, MSBFIRST, address);
  shiftOut(DISPLAY_DIN_PIN, DISPLAY_CLK_PIN, MSBFIRST, data);

  digitalWrite(DISPLAY_CS_PIN, HIGH);
}

#endif