#ifndef INPUT_H
#define INPUT_H

#include "model/model.h"

enum InputType {
  MOVE, EXIT, NONE
};

void initInput(void);

enum InputType getMoveInput(enum MoveType *move_type);

#endif  // INPUT_H
