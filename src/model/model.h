/**
 * Module defines a model for Snake, providing a model structure
 * along with a function to move along the board.
 *
 * @author Kevin Cruse
 */

#pragma once

#include <stdbool.h>

/**
 * Defines how many rows a game board has.
 */
#define MODEL_BOARD_ROWS 8

/**
 * Defines how many columns a game board has.
 */
#define MODEL_BOARD_COLS 8

/**
 * Represents a model, providing a game board and a position.
 */
struct Model {

  /**
   * Represents a game board, indicating which tiles should
   * be lit up. (0, 0) represents the top left.
   */
  bool board[MODEL_BOARD_ROWS][MODEL_BOARD_COLS];

  /**
   * Represents a Cartesian point (y, x), indicating where
   * the character lies. (0, 0) represents the top left.
   */
  unsigned position[2];
};

/**
 * Defines the legal move types along a game board.
 */
enum MoveType {
  MOVE_TYPE_NONE, MOVE_TYPE_UP, MOVE_TYPE_DOWN, MOVE_TYPE_LEFT, MOVE_TYPE_RIGHT
};

/**
 * Creates a model for snake.
 *
 * @returns Pointer to model upon success.
 * @returns @c NULL upon memory allocation error.
 */
struct Model *model_create(void);

/**
 * Destroys the given snake model and sets the pointer to @c NULL.
 *
 * @param pp_model Pointer to pointer to model.
 */
void model_destroy(struct Model **pp_model);

/**
 * Moves the character one tile in the indicated direction,
 * updating the model's position and board matrix.
 *
 * @param p_model Pointer to model.
 * @param move_type Type of move to perform.
 *
 * @throws EINVAL Model pointer is @c NULL, model is malformed, or move type is invalid.
 */
void model_move(struct Model *p_model, enum MoveType move_type);