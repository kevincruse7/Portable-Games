/**
 * Module defines interactions with the system sound device for running Snake.
 *
 * @author Kevin Cruse
 */

#pragma once

/**
 * Initializes the system sound device.
 */
void sound_init(void);

/**
 * Plays movement sound on the sound device.
 *
 * @throws EIO Sound device is not initialized.
 */
void sound_movement_play(void);