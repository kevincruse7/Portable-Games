/*
 * Copyright 2021 Kevin Matthew Cruse
 * This file is part of Portable Games.
 *
 * Portable Games is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Portable Games is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Portable Games. If not, see <https://www.gnu.org/licenses/>.
 */


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
