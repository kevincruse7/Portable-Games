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
 * Module defines functions to retrieve game input from user.
 *
 * @author Kevin Cruse
 */
#ifndef INPUT_H
#define INPUT_H


#include "model/model.h"


/**
 * Defines the possible types of game input to receive from user.
 */
typedef enum InputType {
    INPUT_TYPE_NONE, INPUT_TYPE_ACTION, INPUT_TYPE_MOVE, INPUT_TYPE_EXIT
} InputType;


/**
 * Initializes the input device.
 */
void input_init(void);


/**
 * Polls the input device to retrieve the current game input. If the type
 * of input was a move, then sets the given direction to the input.
 *
 * @param direction Pointer to direction to set if the type of input is a move.
 *
 * @returns Type of input retrieved.
 */
InputType input_get(Direction* direction);


#endif
