/**
 * Implementation of the Snake model module.
 *
 * @author Kevin Cruse
 */

#include "model/snake_model.h"

#include <stdbool.h>
#include <stdlib.h>

struct Model* snake_model_create(void) {

  // Create general model structure
  struct Model* p_snake_model = (struct Model*) calloc(1, sizeof(struct Model));
  p_snake_model->board[0][0] = true;

  // Create Snake model data structure
  struct SnakeModelData* p_snake_model_data = (struct SnakeModelData*) calloc(1,
      sizeof(struct SnakeModelData));
  p_snake_model_data->p_snake_tile_list_head = (struct SnakeTileNode*) calloc(1,
      sizeof(struct SnakeTileNode));
  p_snake_model_data->p_snake_tile_list_tail = NULL;

  // Fill board with food tiles in random positions
  for (unsigned i = 0; i < SNAKE_MODEL_FOOD_TILES; i++) {
    unsigned row;
    unsigned col;

    do {
      row = rand() % MODEL_BOARD_ROWS;
      col = rand() % MODEL_BOARD_COLS;
    }
    while (p_snake_model->board[row][col]);

    p_snake_model_data->food_tiles[i][0] = row;
    p_snake_model_data->food_tiles[i][1] = col;

    p_snake_model->board[row][col] = true;
  }

  // Snake starts in the top left corner, pointing rightward
  p_snake_model_data->current_direction = DIRECTION_RIGHT;

  // Add reference to snake data into general model structure and return
  p_snake_model->p_game_data = p_snake_model_data;
  return p_snake_model;
}

void snake_model_destroy(struct Model** pp_snake_model) {

  struct SnakeTileNode* p_snake_tile_list_prev;
  struct SnakeTileNode* p_snake_tile_list_next = ((struct SnakeModelData*)
      (*pp_snake_model)->p_game_data)->p_snake_tile_list_head;

  // Free nodes in snake tile list
  while (p_snake_tile_list_next != NULL) {
    p_snake_tile_list_prev = p_snake_tile_list_next;
    p_snake_tile_list_next = p_snake_tile_list_next->p_next;
    free(p_snake_tile_list_prev);
  }

  // Free base model structures
  free((*pp_snake_model)->p_game_data);
  free(*pp_snake_model);
  *pp_snake_model = NULL;
}

void snake_model_action(struct Model* unused) {

  (void) unused;
}

void snake_model_move(struct Model* p_snake_model, enum Direction direction) {

  struct SnakeModelData* p_snake_model_data = (struct SnakeModelData*) p_snake_model->p_game_data;
  struct SnakeTileNode* p_snake_tile_list_head = p_snake_model_data->p_snake_tile_list_head;
  struct SnakeTileNode* p_snake_tile_list_tail = p_snake_model_data->p_snake_tile_list_tail;

  // If snake is longer than one tile, move tail node to head
  if (p_snake_tile_list_head != p_snake_tile_list_tail) {
    p_snake_tile_list_head->p_prev = p_snake_tile_list_tail;
    p_snake_tile_list_tail->p_next = p_snake_tile_list_head;
    p_snake_tile_list_tail->p_prev->p_next = NULL;

    p_snake_model_data->p_snake_tile_list_head = p_snake_tile_list_tail;
    p_snake_model_data->p_snake_tile_list_tail = p_snake_tile_list_tail->p_prev;

    p_snake_tile_list_head = p_snake_model_data->p_snake_tile_list_head;
    p_snake_tile_list_tail = p_snake_model_data->p_snake_tile_list_tail;
  }

  switch (direction) {
    case DIRECTION_UP:
    case DIRECTION_DOWN:
    case DIRECTION_LEFT:
    case DIRECTION_RIGHT:
    default:
      break;
  }
}