/**
 * Implementation of the controller module for running Snake.
 *
 * @author Kevin Cruse
 */

#include "controller/controller.h"

#include <stdbool.h>

#include "controller/input/input.h"
#include "controller/system_time/system_time.h"

#include "model/model.h"

#include "view/display/display.h"
#include "view/sound/sound.h"

// Calculate how much time is remaining in tick and sleep for that duration
static void sleep_for_remainder_of_tick(SystemTime start_time);

void run(void) {

  input_init();
  display_init();
  sound_init();

  struct Model *p_model = model_create();

  enum MoveType current_move = MOVE_TYPE_NONE;
  enum MoveType last_move = MOVE_TYPE_NONE;
  enum InputType last_input = INPUT_TYPE_NONE;

  const unsigned TICKS_BETWEEN_FRAMES = CONTROLLER_TICK_RATE / CONTROLLER_FRAME_RATE;
  const unsigned TICKS_BETWEEN_REPEAT_MOVES = TICKS_BETWEEN_FRAMES;

  unsigned ticks_until_next_frame = 0;
  unsigned ticks_until_next_repeat_move = 0;

  while (true) {
    SystemTime start_time = system_time_get();

    switch (input_get(&current_move)) {
      case INPUT_TYPE_ACTION:
        last_input = INPUT_TYPE_ACTION;
        break;
      case INPUT_TYPE_MOVE:
        if (current_move != last_move || ticks_until_next_repeat_move == 0) {
          last_input = INPUT_TYPE_MOVE;
          ticks_until_next_repeat_move = TICKS_BETWEEN_REPEAT_MOVES;
        }
        break;
      case INPUT_TYPE_EXIT:
        model_destroy(&p_model);
        return;
      default:
        break;
    }

    if (ticks_until_next_repeat_move != 0) {
      ticks_until_next_repeat_move--;
    }

    if (ticks_until_next_frame == 0) {
      if (last_input == INPUT_TYPE_MOVE) {
        model_move(p_model, current_move);
        sound_movement_play();

        last_move = current_move;
      }

      display_render(p_model);

      last_input = INPUT_TYPE_NONE;
      ticks_until_next_frame = TICKS_BETWEEN_FRAMES;
    } else {
      ticks_until_next_frame--;
    }

    sleep_for_remainder_of_tick(start_time);
  }
}

static void sleep_for_remainder_of_tick(SystemTime start_time) {

  SystemTime remaining_time = 1000 / CONTROLLER_TICK_RATE - (system_time_get() - start_time);
  if (remaining_time > 0) {
    system_time_sleep(remaining_time);
  }
}