#ifndef DISPLAY_H
#define DISPLAY_H

#include "model/model.h"

void initDisplay(void);

void displayBoard(unsigned char board[MODEL_BOARD_NUM_ROWS][MODEL_BOARD_NUM_COLS]);

#endif  // DISPLAY_H
