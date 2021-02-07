/**
 * Implementation of the controller module for running Snake.
 *
 * @author Kevin Cruse
 */

#include "controller/controller.h"

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "controller/input/input.h"
#include "controller/system_time/system_time.h"

#include "model/model.h"

#include "view/display/display.h"
#include "view/sound/sound.h"

// Calculate how much time is remaining in tick and sleep for that duration
static void sleep_for_remainder_of_tick(SystemTime start_time);

void run(const struct ModelFunctions *p_model_functions) {

  // Error out if passed functions structure is malformed
  if (p_model_functions == NULL
      || p_model_functions->create == NULL
      || p_model_functions->destroy == NULL
      || p_model_functions->move == NULL
      || p_model_functions->next_frame == NULL) {
    errno = EINVAL;
    return;
  }

  // Initialize system devices
  input_init();
  display_init();
  sound_init();

  srand(time(NULL));
  struct Model *p_model = p_model_functions->create();

  enum Direction current_direction = DIRECTION_NONE;
  enum Direction last_direction = DIRECTION_NONE;
  enum InputType last_input = INPUT_TYPE_NONE;

  const unsigned TICKS_BETWEEN_FRAMES = CONTROLLER_TICK_RATE / CONTROLLER_FRAME_RATE;
  const unsigned TICKS_BETWEEN_ACTIONS = TICKS_BETWEEN_FRAMES;
  const unsigned TICKS_BETWEEN_REPEAT_MOVES = TICKS_BETWEEN_FRAMES;

  unsigned ticks_until_next_frame = 0;
  unsigned ticks_until_next_action = 0;
  unsigned ticks_until_next_repeat_move = 0;

  while (true) {
    SystemTime start_time = system_time_get();

    // Get user input, if there is any
    switch (input_get(&current_direction)) {
      case INPUT_TYPE_ACTION:
        // Only register an action if the cooldown has finished
        if (ticks_until_next_action == 0) {
          last_input = INPUT_TYPE_ACTION;
          ticks_until_next_action = TICKS_BETWEEN_ACTIONS;
        }
        break;
      case INPUT_TYPE_MOVE:
        // Only register a move if the cooldown has finished
        if (current_direction != last_direction || ticks_until_next_repeat_move == 0) {
          last_input = INPUT_TYPE_MOVE;
          ticks_until_next_repeat_move = TICKS_BETWEEN_REPEAT_MOVES;
        }
        break;
      case INPUT_TYPE_EXIT:
        p_model_functions->destroy(&p_model);
        return;
      default:
        break;
    }

    // Update cooldowns
    if (ticks_until_next_action != 0) {
      ticks_until_next_action--;
    }
    if (ticks_until_next_repeat_move != 0) {
      ticks_until_next_repeat_move--;
    }

    // Render new frame on frame ticks
    if (ticks_until_next_frame == 0) {
      // Send input to model
      if (last_input == INPUT_TYPE_ACTION) {
        p_model_functions->action(p_model);
      } else if (last_input == INPUT_TYPE_MOVE) {
        p_model_functions->move(p_model, current_direction);
        last_direction = current_direction;
      }

      // Advance to next frame and push to devices
      p_model_functions->next_frame(p_model);
      sound_play(p_model);
      display_render(p_model);

      // Reset input and frame cooldown
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