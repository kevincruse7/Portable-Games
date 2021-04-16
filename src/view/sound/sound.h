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
