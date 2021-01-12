/**
 * Module defines functions to retrieve game input from user.
 *
 * @author Kevin Cruse
 */

#pragma once

#include "model/model.h"

/**
 * Defines the possible types of game input to receive from user.
 */
enum InputType {
  ACTION, MOVE, EXIT, NONE
};

/**
 * Initializes the input device.
 */
void input_init(void);

/**
 * Polls the input device to retrieve the current game input. If the input
 * type is a move, then sets the given move type to the retrieved move.
 *
 * @param p_move_type Pointer to move type to set if retrieved input is a move.
 *
 * @returns Type of input retrieved.
 *
 * @throws EIO Input device is not initialized.
 * @throws EINVAL Pointer to move type is @c NULL.
 */
enum InputType input_get(enum MoveType *p_move_type);