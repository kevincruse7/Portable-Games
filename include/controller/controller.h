/**
 * Module defines a controller for running Snake.
 *
 * @author Kevin Cruse
 */

#pragma once

/**
 * Defines a positive integer tick rate in ticks per second for how often input should be polled.
 */
#define CONTROLLER_MAIN_TICK_RATE 60

/**
 * Defines a positive integer tick rate in ticks per
 * second for how often the view should be rendered.
 */
#define CONTROLLER_RENDER_TICK_RATE 10

/**
 * Runs the snake game.
 */
void run(void);