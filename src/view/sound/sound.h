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
 * Module defines interactions with the system sound device for running arbitrary pixel games.
 *
 * @author Kevin Cruse
 */
#ifndef SOUND_H
#define SOUND_H


#include "model/model.h"


/**
 * Initializes the system sound device.
 */
void sound_init(void);


/**
 * Plays model sound on the sound device.
 *
 * @param model Model to extract sound from.
 * @param frame_rate Frame rate to determine note length with.
 */
void sound_play(const Model* model, int frame_rate);


#endif
