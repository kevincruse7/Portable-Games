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
 * Module defines interactions with the system display for running arbitrary pixel games.
 *
 * @author Kevin Cruse
 */
#ifndef DISPLAY_H
#define DISPLAY_H


#include "model/model.h"


/**
 * Initializes the display device.
 */
void display_init(void);


/**
 * Renders the given model on the display device.
 *
 * @param model Model to be rendered.
 */
void display_render(const Model* model);


#endif
