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
