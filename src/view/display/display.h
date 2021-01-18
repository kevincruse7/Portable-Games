/**
 * Module defines interactions with the system display for running Snake.
 *
 * @author Kevin Cruse
 */

#pragma once

#include "model/model.h"

/**
 * Initializes the display device.
 */
void display_init(void);

/**
 * Renders the given model on the display device.
 *
 * @param p_model Pointer to model to be rendered.
 *
 * @throws EIO Display device is not initialized
 * @throws EINVAL Pointer to model is @c NULL.
 */
void display_render(const struct Model *p_model);