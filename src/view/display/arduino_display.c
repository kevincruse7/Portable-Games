/**
 * Implementation of the display module for the Arduino Mega 2560 using a dot matrix LED display.
 *
 * @author Kevin Cruse
 */
#ifdef __AVR_ATmega2560__
#include "display.h"


#include <Arduino.h>
#include "model/model.h"


// Pin mappings to display inputs
#define DISPLAY_DIN_PIN 22
#define DISPLAY_CS_PIN 23
#define DISPLAY_CLK_PIN 24


/**
 * Serially writes the given data to the given address on the display.
 *
 * @param address Address to write to.
 * @param data Data to write.
 */
static void display_write_data(uint8_t address, uint8_t data);


void display_init(void) {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(DISPLAY_DIN_PIN, OUTPUT);
    pinMode(DISPLAY_CS_PIN, OUTPUT);
    pinMode(DISPLAY_CLK_PIN, OUTPUT);

    display_write_data(0x09, 0);  // No data decoding
    display_write_data(0x0A, 1);  // Screen brightness (0 - F)
    display_write_data(0x0B, MODEL_COLS - 1);  // Column scan limit
    display_write_data(0x0C, 1);  // Normal operation (shutdown mode)
    display_write_data(0x0F, 0);  // Normal operation (display test mode)
}


void display_render(const Model* model) {
    // Convert row on board to byte and send out to display
    for (int row = 0; row < MODEL_ROWS; row++) {
        byte row_data = 0;
        for (int col = 0; col < MODEL_COLS; col++) {
            if (model->board[row][col]) {
                row_data += 0x80 >> col;
            }
        }

        display_write_data(row + 1, row_data);
    }
}


static void display_write_data(uint8_t address, uint8_t data) {
    digitalWrite(DISPLAY_CS_PIN, LOW);

    shiftOut(DISPLAY_DIN_PIN, DISPLAY_CLK_PIN, MSBFIRST, address);
    shiftOut(DISPLAY_DIN_PIN, DISPLAY_CLK_PIN, MSBFIRST, data);

    digitalWrite(DISPLAY_CS_PIN, HIGH);
}


#endif
