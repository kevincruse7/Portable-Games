/**
 * Implementation of the model module for Snake.
 *
 * @author Kevin Cruse
 */

#include "model/model.h"

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

// Determines if the given model is malformed
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
    case MOVE_TYPE_UP:
      if (p_model->position[0] <= 0) {
        p_model->position[0] = MODEL_BOARD_ROWS - 1;
      } else {
        p_model->position[0]--;
      }
      break;
    case MOVE_TYPE_DOWN:
      if (p_model->position[0] >= MODEL_BOARD_ROWS - 1) {
        p_model->position[0] = 0;
      } else {
        p_model->position[0]++;
      }
      break;
    case MOVE_TYPE_LEFT:
      if (p_model->position[1] <= 0) {
        p_model->position[1] = MODEL_BOARD_COLS - 1;
      } else {
        p_model->position[1]--;
      }
      break;
    case MOVE_TYPE_RIGHT:
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