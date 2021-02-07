/**
 * Module defines interactions with the system sound device for running Snake.
 *
 * @author Kevin Cruse
 */

#pragma once

#include "model/model.h"

/**
 * Initializes the system sound device.
 */
void sound_init(void);

/**
 * Plays model sound on the sound device.
 *
 * @param p_model Pointer to model.
 *
 * @throws EIO Sound device is not initialized.
 * @throws EINVAL Pointer to model is @c NULL.
 */
void sound_play(const struct Model *p_model);