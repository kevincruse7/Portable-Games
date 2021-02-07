/**
 * Module defines a generic model for games, providing structures for model data and functions.
 *
 * @author Kevin Cruse
 */

#pragma once

#include <stdbool.h>

/**
 * Defines how many rows a game board has, with possible integer values spanning [1, 255].
 */
#define MODEL_BOARD_ROWS 8

/**
 * Defines how many columns a game board has, with possible integer values spanning [1, 255].
 */
#define MODEL_BOARD_COLS 8

/**
 * Defines the legal directions along a game board.
 */
enum Direction {
  DIRECTION_NONE, DIRECTION_UP, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT
};

/**
 * Represents a model, providing a game board, a game over indicator,
 * and a generic pointer to any game-specific data.
 */
struct Model {

  /**
   * Represents a game board, indicating which tiles should
   * be lit up. (0, 0) represents the top left.
   */
  bool board[MODEL_BOARD_ROWS][MODEL_BOARD_COLS];

  /**
   * Indicates whether the game is over.
   */
  bool is_game_over;

  /**
   * The current note to be played by the sound device, represented in Hertz.
   */
  unsigned short current_note;

  /**
   * Generic pointer to game-specific data.
   */
  void* p_game_data;
};

/**
 * Holds pointers to model functions that are defined on a per-game basis.
 */
struct ModelFunctions {

  /**
   * Creates a model.
   *
   * @returns Pointer to model upon success.
   * @returns @c NULL upon memory allocation error.
   */
  struct Model* (*create)(void);

  /**
   * Destroys the given model and sets the pointer to @c NULL.
   *
   * @param pp_model Pointer to pointer to model.
   */
  void (*destroy)(struct Model** pp_model);

  /**
   * Performs an action, the effect of which is game-specific.
   *
   * @param p_model Pointer to model.
   */
  void (*action)(struct Model* p_model);

  /**
   * Moves the character in the indicated direction.
   *
   * @param p_model Pointer to model.
   * @param direction Direction in which to move.
   */
  void (*move)(struct Model* p_model, enum Direction direction);

  /**
   * Advances the model to the next frame.
   *
   * @param p_model Pointer to model.
   */
  void (*next_frame)(struct Model* p_model);
};