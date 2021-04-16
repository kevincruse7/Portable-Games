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
