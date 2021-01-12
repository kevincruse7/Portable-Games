#pragma once

#include <stdbool.h>

#include "controller/input.h"
#include "controller/system_time.h"

#include "model/model.h"

#include "view/display.h"
#include "view/sound.h"

/**
 * Positive integer tick rate in ticks per second.
 */
#define CONTROLLER_MAIN_TICK_RATE 60

/**
 * Runs the snake game.
 */
void run(void);

void run(void) {

  input_init();
  initDisplay();
  initSound();

  struct Model *p_model = model_create();

  while (true) {
    SystemTime tick_start_time = system_time_get();

    enum MoveType move_type;
    switch (input_get(&move_type)) {
      case MOVE:
        model_move(p_model, move_type);
        playMovementSound();
        break;
      case EXIT:
        model_destroy(&p_model);
        return;
      default:
        break;
    }

    displayBoard(p_model->board);

    // Calculate how much time is remaining in tick and sleep for that duration
    SystemTime tick_remaining_time = 1000 / CONTROLLER_MAIN_TICK_RATE - (system_time_get() - tick_start_time);
    if (tick_remaining_time > 0) {
      system_time_sleep(tick_remaining_time);
    }
  }
}