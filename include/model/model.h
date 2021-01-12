/**
 * Module defines a model for Snake, providing a model structure
 * along with a function to move along the board.
 *
 * @author Kevin Cruse
 */

#pragma once

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

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
  UP, DOWN, LEFT, RIGHT
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

/**
 * Determines if the given model is malformed.
 *
 * @param p_model Pointer to model.
 * @return @c true if malformed, @c false if not.
 */
static bool is_malformed(struct Model *p_model);

struct Model *model_create(void) {

  struct Model *p_model = (struct Model *) calloc(1, sizeof(struct Model));
  p_model->board[0][0] = true;
  return p_model;
}

void model_destroy(struct Model **pp_model) {

  free(*pp_model);
  *pp_model = NULL;
}

void model_move(struct Model *p_model, enum MoveType move_type) {

  if (is_malformed(p_model)) {
    errno = EINVAL;
    return;
  }

  p_model->board[p_model->position[0]][p_model->position[1]] = false;

  switch (move_type) {
    case UP:
      if (p_model->position[0] <= 0) {
        p_model->position[0] = MODEL_BOARD_ROWS - 1;
      } else {
        p_model->position[0]--;
      }
      break;
    case DOWN:
      if (p_model->position[0] >= MODEL_BOARD_ROWS - 1) {
        p_model->position[0] = 0;
      } else {
        p_model->position[0]++;
      }
      break;
    case LEFT:
      if (p_model->position[1] <= 0) {
        p_model->position[1] = MODEL_BOARD_COLS - 1;
      } else {
        p_model->position[1]--;
      }
      break;
    case RIGHT:
      if (p_model->position[1] >= MODEL_BOARD_COLS - 1) {
        p_model->position[1] = 0;
      } else {
        p_model->position[1]++;
      }
      break;
    default:
      break;
  }

  p_model->board[p_model->position[0]][p_model->position[1]] = true;
}

static bool is_malformed(struct Model *p_model) {

  return p_model == NULL
         || p_model->position[0] >= MODEL_BOARD_ROWS
         || p_model->position[1] >= MODEL_BOARD_COLS;
}