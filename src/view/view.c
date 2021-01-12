/**
 * Implementation of the view module for Snake.
 *
 * @author Kevin Cruse
 */

#include "view/view.h"

#include "model/model.h"

#include "view/display.h"
#include "view/sound.h"

void view_init(void) {

  display_init();
  sound_init();
}

void view_render(struct Model *p_model) {

  display_render(p_model);
}

void view_play_movement_sound(void) {

  sound_movement_play();
}