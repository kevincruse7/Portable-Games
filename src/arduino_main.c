/**
 * Module defines @c setup and @c loop functions for use on an Arduino.
 *
 * @author Kevin Cruse
 */


#include <Arduino.h>


#include "controller/controller.h"
#include "model/snake_model.h"


void setup(void) {
    run(SNAKE_MODEL_FUNCTIONS, 64, 16, 2);
}


void loop(void) {}
