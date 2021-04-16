/**
 * Module defines a game model for Snake, with corresponding model data and functions.
 *
 * @author Kevin Cruse
 */
#ifndef SNAKE_MODEL_H
#define SNAKE_MODEL_H


#include <stdarg.h>
#include "model/model.h"


/**
 * Collection of model functions for Snake.
 */
extern const ModelFunctions SNAKE_MODEL_FUNCTIONS;


/**
 * Represents a snake tile in a doubly linked list of board tiles.
 */
typedef struct SnakeTileNode {
    /**
     * Position of tile by its row and column on the board.
     */
    int position[2];
    /**
     * Pointer to previous tile in list.
     */
    struct SnakeTileNode* prev;
} SnakeTileNode;


/**
 * Additional model data needed for keeping track of snake and food tiles.
 */
typedef struct SnakeGameData {
    /**
     * Linked list of tiles in which the snake occupies, in order from head to tail.
     */
    SnakeTileNode* snake_tile_list_head;
    /**
     * Pointer to tail of snake tile list.
     */
    SnakeTileNode* snake_tile_list_tail;
    /**
     * Copy of board only containing food tiles.
     */
    bool (* food_tiles)[MODEL_COLS];
    /**
     * Direction in which the snake is currently travelling.
     */
    Direction current_direction;
} SnakeGameData;


/**
 * Creates a new Snake model.
 *
 * @param args Number of food tiles to place on board.
 * @returns Pointer to new model.
 * @throws ENOMEM Device is out of memory.
 */
Model* snake_create(va_list args);


/**
 * Destroys the given Snake model.
 *
 * @param model Double pointer to model to destroy.
 */
void snake_destroy(Model** model);


/**
 * Performs an action on the given model, which has no effect in Snake.
 *
 * @param model Pointer to model to update.
 */
void snake_action(Model* model);


/**
 * Points the snake of the given model toward the indicated direction.
 *
 * @param model Pointer to model to update.
 * @param direction Direction in which to point.
 */
void snake_move(Model* model, Direction direction);


/**
 * Advances the given Snake model to the next frame.
 *
 * @param model Pointer to model to update.
 * @throws ENOMEM Device is out of memory.
 */
void snake_next_frame(Model* model);


#endif
