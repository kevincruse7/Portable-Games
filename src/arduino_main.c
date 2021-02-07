#include <Arduino.h>

#include "controller/controller.h"

#include "model/snake_model.h"

void setup() {

  run(&SNAKE_MODEL_FUNCTIONS);
}

void loop() {}