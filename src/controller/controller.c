/**
 * Implementation of the controller module for running Snake.
 *
 * @author Kevin Cruse
 */

#include "controller/controller.h"

#include <stdbool.h>

#include "controller/input.h"
#include "controller/system_time.h"

#include "model/model.h"
#include "view/view.h"

// Calculate how much time is remaining in tick and sleep for that duration
static void sleep_for_remaining_tick_time(SystemTime start_time);

void run(void) {

  input_init();
  view_init();

  struct Model *p_model = model_create();
  enum InputType last_input = NONE;

  unsigned ticks_between_renders = CONTROLLER_MAIN_TICK_RATE / CONTROLLER_RENDER_TICK_RATE;
  unsigned ticks_until_next_render = 0;

  while (true) {
    SystemTime start_time = system_time_get();

    enum MoveType move_type;
    switch (input_get(&move_type)) {
      case MOVE:
        if (last_input != MOVE) {
          model_move(p_model, move_type);
          view_play_movement_sound();
        }
        last_input = MOVE;
        break;
      case NONE:
        last_input = NONE;
        break;
      case EXIT:
        model_destroy(&p_model);
        return;
      default:
        break;
    }

    if (ticks_until_next_render == 0) {
      view_render(p_model);
      ticks_until_next_render = ticks_between_renders;
    } else {
      ticks_until_next_render--;
    }

    sleep_for_remaining_tick_time(start_time);
  }
}

static void sleep_for_remaining_tick_time(SystemTime start_time) {

  SystemTime remaining_time = 1000 / CONTROLLER_MAIN_TICK_RATE - (system_time_get() - start_time);
  if (remaining_time > 0) {
    system_time_sleep(remaining_time);
  }
}