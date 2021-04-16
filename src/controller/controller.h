/**
 * Module defines a controller for running arbitrary pixel games.
 *
 * @author Kevin Cruse
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "model/model.h"


/**
 * Runs the pixel game with the given model functions and parameters.
 *
 * @param model_functions Collection of model functions to use.
 * @param tick_rate Rate in ticks per second at which the input device should be polled.
 * @param ticks_per_frame Rate in ticks per frame at which the view should be updated.
 * @param ... Additional game-specific arguments.
 *
 * @throws ENOMEM Device is out of memory.
 */
void run(ModelFunctions model_functions, int tick_rate, int ticks_per_frame, ...);


#endif
