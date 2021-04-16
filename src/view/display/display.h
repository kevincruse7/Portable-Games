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
