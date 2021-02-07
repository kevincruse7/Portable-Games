/**
 * Module defines a game model for Snake, with corresponding model data and functions.
 *
 * @author Kevin Cruse
 */

#pragma once

#include "model/model.h"

/**
 * Defines the number of food tiles that can spawn on the board, with possible
 * integer values spanning [1, @c MODEL_BOARD_ROWS * @c MODEL_BOARD_COLS].
 */
#define SNAKE_MODEL_FOOD_TILES 2

/**
 * Represents a snake tile in a doubly linked list of board tiles.
 */
struct SnakeTileNode {

  /**
   * Position of tile by its row and column on the board.
   */
  unsigned char position[2];

  /**
   * Pointer to next tile in list.
   */
  struct SnakeTileNode* p_next;

  /**
   * Pointer to previous tile in list.
   */
   struct SnakeTileNode* p_prev;
};

/**
 * Additional model data needed for keeping track of snake and food tiles.
 */
struct SnakeModelData {

  /**
   * Linked list of tiles in which the snake occupies, in order from head to tail.
   */
  struct SnakeTileNode* p_snake_tile_list_head;

  /**
   * Pointer to tail of snake tile list.
   */
  struct SnakeTileNode* p_snake_tile_list_tail;

  /**
   * Matrix of food tile positions.
   */
  unsigned char food_tiles[SNAKE_MODEL_FOOD_TILES][2];

  /**
   * Direction in which the snake is currently travelling.
   */
  enum Direction current_direction;
};

/**
 * Creates a model for Snake.
 *
 * @returns Pointer to Snake model upon success.
 * @returns @c NULL upon memory allocation error.
 */
struct Model* snake_model_create(void);

/**
 * Destroys the given Snake model and sets the pointer to @c NULL.
 *
 * @param pp_snake_model Pointer to pointer to Snake model.
 */
void snake_model_destroy(struct Model** pp_snake_model);

/**
 * Performs an action, which has no effect in Snake.
 */
void snake_model_action(struct Model* unused);

/**
 * Points the snake toward the indicated direction.
 *
 * @param p_snake_model Pointer to Snake model.
 * @param direction Direction in which to point.
 */
void snake_model_move(struct Model* p_snake_model, enum Direction direction);

/**
 * Advances the Snake model to the next frame.
 *
 * @param p_snake_model Pointer to Snake model.
 */
void snake_model_next_frame(struct Model* p_snake_model);

/**
 * Structure containing pointers to all the model functions for Snake.
 */
const struct ModelFunctions SNAKE_MODEL_FUNCTIONS = {
  snake_model_create,
  snake_model_destroy,
  snake_model_action,
  snake_model_move,
  snake_model_next_frame
};