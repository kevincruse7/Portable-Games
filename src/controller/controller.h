/**
 * Module defines a controller for running Snake.
 *
 * @author Kevin Cruse
 */

#pragma once

#include "model/model.h"

/**
 * Defines a tick rate in ticks per second, with possible integer values spanning [1, 65,535].
 * This is used to determine how often the input device should be polled.
 */
#define CONTROLLER_TICK_RATE 64

/**
 * Defines a frame rate in frames per second, with possible integer values spanning
 * [1, 65,535]. This determines how often the view should be updated.
 */
#define CONTROLLER_FRAME_RATE 8

/**
 * Runs the snake game with the given model functions.
 *
 * @param p_model_functions Pointer to model functions to use.
 *
 * @throws EINVAL Structure pointer or function pointers are @c NULL.
 */
void run(const struct ModelFunctions *p_model_functions);