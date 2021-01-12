/**
 * Module defines interactions with the system display and sound devices for running Snake.
 *
 * @author Kevin Cruse
 */

#pragma once

#include "model/model.h"

/**
 * Initializes the view.
 */
void view_init(void);

/**
 * Renders the given model in the view.
 *
 * @param p_model Pointer to model to be rendered.
 *
 * @throws EIO View is not initialized.
 * @throws EINVAL Pointer to model is @c NULL.
 */
void view_render(struct Model *p_model);

/**
 * Plays the movement sound in the view.
 *
 * @throws EIO View is not initialized.
 */
void view_play_movement_sound(void);