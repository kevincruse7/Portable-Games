/**
 * Module defines interactions with the system display and sound devices for running Snake.
 *
 * @author Kevin Cruse
 */

#pragma once

#include "model/model.h"

void view_init(void);

void view_render(struct Model *p_model);

void view_play_movement_sound(void);