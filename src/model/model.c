#include "model/model.h"

#include <stdlib.h>

Model createModel(void) {

  Model model = (Model) calloc(1, sizeof(struct ModelData));
  model->_board[0][0] = 1;
  return model;
}

void destroyModel(Model *model_ptr) {

  free(*model_ptr);
  *model_ptr = NULL;
}

void getModelBoard(Model model, unsigned char board[MODEL_BOARD_NUM_ROWS][MODEL_BOARD_NUM_COLS]) {

  for (int row = 0; row < MODEL_BOARD_NUM_ROWS; row++) {
    for (int col = 0; col < MODEL_BOARD_NUM_COLS; col++) {
      board[row][col] = model->_board[row][col];
    }
  }
}

void modelMove(Model model, enum MoveType move_type) {

  model->_board[model->_position[0]][model->_position[1]] = 0;

  switch (move_type) {
    case UP:
      if (model->_position[0] <= 0) {
        model->_position[0] = MODEL_BOARD_NUM_ROWS - 1;
      } else {
        model->_position[0]--;
      }
      break;
    case DOWN:
      if (model->_position[0] >= MODEL_BOARD_NUM_ROWS - 1) {
        model->_position[0] = 0;
      } else {
        model->_position[0]++;
      }
      break;
    case LEFT:
      if (model->_position[1] <= 0) {
        model->_position[1] = MODEL_BOARD_NUM_COLS - 1;
      } else {
        model->_position[1]--;
      }
      break;
    case RIGHT:
      if (model->_position[1] >= MODEL_BOARD_NUM_COLS - 1) {
        model->_position[1] = 0;
      } else {
        model->_position[1]++;
      }
      break;
    default:
      break;
  }

  model->_board[model->_position[0]][model->_position[1]] = 1;
}