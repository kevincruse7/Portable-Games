#ifndef MODEL_H
#define MODEL_H

#define MODEL_BOARD_NUM_ROWS 8
#define MODEL_BOARD_NUM_COLS 8

struct ModelData {
  unsigned char _board[MODEL_BOARD_NUM_ROWS][MODEL_BOARD_NUM_COLS];
  unsigned _position[2];
};
typedef struct ModelData *Model;

enum MoveType {
  UP, DOWN, LEFT, RIGHT
};

Model createModel(void);

void destroyModel(Model *model_ptr);

void getModelBoard(Model model, unsigned char board[MODEL_BOARD_NUM_ROWS][MODEL_BOARD_NUM_COLS]);

void modelMove(Model model, enum MoveType move_type);

#endif  // MODEL_H
