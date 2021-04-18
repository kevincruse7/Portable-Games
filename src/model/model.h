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
 * Module defines a generic model for games, providing structures for model data and functions.
 *
 * @author Kevin Cruse
 */
#ifndef MODEL_H
#define MODEL_H


#include <stdarg.h>
#include <stdbool.h>


#include "view/sound/notes.h"


/**
 * Defines how many rows a game board has.
 */
#define MODEL_ROWS 8
/**
 * Defines how many columns a game board has.
 */
#define MODEL_COLS 8


/**
 * Defines the legal directions of a game board.
 */
typedef enum Direction {
    DIRECTION_NONE, DIRECTION_UP, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT
} Direction;


/**
 * Represents a model, providing a game board, a 'game over' indicator, and any additional game-specific data.
 */
typedef struct Model {
    /**
     * Represents a game board, indicating which tiles should be lit up. (0, 0) represents the top left.
     */
    bool (* board)[MODEL_COLS];
    /**
     * Indicates whether the game is over.
     */
    bool game_over;
    /**
     * The current note to be played by the sound device.
     */
    Note current_note;
    /**
     * Generic pointer to game-specific data.
     */
    void* game_data;
} Model;


/**
 * Collection of model functions that are defined on a per-game basis.
 */
typedef struct ModelFunctions {
    /**
     * Creates a new model.
     *
     * @param args Additional game-specific arguments.
     * @returns Pointer to new model.
     * @throws ENOMEM Device is out of memory.
     */
    Model* (* create)(va_list args);
    /**
     * Destroys the given model.
     *
     * @param model Double pointer to model to destroy.
     */
    void (* destroy)(Model** model);
    /**
     * Performs an action on the given model, the effect of which is game-specific.
     *
     * @param model Pointer to model to update.
     */
    void (* action)(Model* model);
    /**
     * Moves the character of the given model in the indicated direction.
     *
     * @param model Pointer to model to update.
     * @param direction Direction in which to move.
     */
    void (* move)(Model* model, Direction direction);
    /**
     * Advances the given model to the next frame.
     *
     * @param model Pointer to model to update.
     * @throws ENOMEM Device is out of memory.
     */
    void (* next_frame)(Model* model);
} ModelFunctions;


#endif
