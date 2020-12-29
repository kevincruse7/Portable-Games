#include "controller/controller.h"

#include <Arduino.h>

#include "controller/input.h"
#include "controller/system_time.h"

#include "model/model.h"

#include "view/display.h"
#include "view/sound.h"

void run(void) {

  initInput();
  initDisplay();
  initSound();

  pinMode(13, OUTPUT);

  Model model = createModel();
  unsigned char board[MODEL_BOARD_NUM_ROWS][MODEL_BOARD_NUM_COLS];

  while (1) {
    SystemTime tick_start_time = getSystemTime();

    enum MoveType move_type;
    switch (getMoveInput(&move_type)) {
      case MOVE:
        modelMove(model, move_type);
        playMovementSound();
        break;
      case EXIT:
        destroyModel(&model);
        return;
      default:
        break;
    }

    getModelBoard(model, board);
    displayBoard(board);

    // Calculate how much time is remaining in tick and sleep for that duration
    SystemTime tick_remaining_time = 1000 / TICK_RATE - (getSystemTime() - tick_start_time);
    if (tick_remaining_time > 0) {
      digitalWrite(13, LOW);
      systemTimeSleep(tick_remaining_time);
    } else {
      digitalWrite(13, HIGH);
    }
  }
}