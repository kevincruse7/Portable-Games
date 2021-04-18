/*
 * Copyright 2021 Kevin Matthew Cruse
 * This file is part of Portable Games.
 *
 * Portable Games is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Portable Games is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Portable Games. If not, see <https://www.gnu.org/licenses/>.
 */


/**
 * Implementation of the controller module.
 *
 * @author Kevin Cruse
 */
#include "controller/controller.h"


#include <errno.h>


#include "controller/input/input.h"
#include "controller/system_time/system_time.h"


#include "model/model.h"


#include "view/display/display.h"
#include "view/sound/sound.h"


/**
 * Calculate how much time is remaining in tick and sleep for that duration.
 *
 * @param start_time Time at which tick started.
 * @param tick_rate Tick rate to determine tick length from.
 */
static void sleep_for_remainder_of_tick(SystemTime start_time, int tick_rate);


void run(ModelFunctions model_functions, int tick_rate, int ticks_per_frame, ...) {
    // Initialize system devices
    input_init();
    display_init();
    sound_init();

    // Create model using passed arguments
    va_list args;
    va_start(args, ticks_per_frame);
    Model* model = model_functions.create(args);
    va_end(args);
    if (errno == ENOMEM) return;

    int tick = 0;
    int frame_rate = tick_rate / ticks_per_frame;
    InputType queued_input = INPUT_TYPE_NONE;
    Direction queued_direction;
    while (1) {
        SystemTime start_time = system_time_get();

        // Poll input device and queue up input, if received. If exit button is pressed, terminate.
        switch (input_get(&queued_direction)) {
            case INPUT_TYPE_ACTION:
                queued_input = INPUT_TYPE_ACTION;
                break;
            case INPUT_TYPE_MOVE:
                queued_input = INPUT_TYPE_MOVE;
                break;
            case INPUT_TYPE_EXIT:
                model_functions.destroy(&model);
                return;
            default:
                break;
        }

        // Advance frame when tick is congruent to zero modulo ticks per frame
        if (tick == 0) {
            // Terminate if game is over
            if (model->game_over) {
                model_functions.destroy(&model);
                return;
            }

            // Send queued input to model, if there is any
            switch (queued_input) {
                case INPUT_TYPE_ACTION:
                    model_functions.action(model);
                    break;
                case INPUT_TYPE_MOVE:
                    model_functions.move(model, queued_direction);
                    if (errno == ENOMEM) {
                        model_functions.destroy(&model);
                        return;
                    }
                    break;
                default:
                    break;
            }
            queued_input = INPUT_TYPE_NONE;

            // Update model, sound device, and display every frame
            model_functions.next_frame(model);
            sound_play(model, frame_rate);
            display_render(model);
        }

        // Advance tick modulo ticks per frame, sleep for remainder of tick
        tick = (tick + 1) % ticks_per_frame;
        sleep_for_remainder_of_tick(start_time, tick_rate);
    }
}


static void sleep_for_remainder_of_tick(SystemTime start_time, int tick_rate) {
    SystemTime remaining_time = 1000 / tick_rate - (system_time_get() - start_time);
    if (remaining_time > 0) {
        system_time_sleep(remaining_time);
    }
}
