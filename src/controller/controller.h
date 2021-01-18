/**
 * Module defines a controller for running Snake.
 *
 * @author Kevin Cruse
 */

#pragma once

/**
 * Defines a positive integer tick rate in ticks per second.
 */
#define CONTROLLER_TICK_RATE 64

/**
 * Defines a positive integer frame rate in frames per
 * second for how often the view should be updated.
 */
#define CONTROLLER_FRAME_RATE 8

/**
 * Runs the snake game.
 */
void run(void);