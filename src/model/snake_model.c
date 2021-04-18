/*
 * Copyright 2021 Kevin Matthew Cruse
 * This file is part of Portable Games.
 *
 * Portable Games is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Portable Games is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Portable Games. If not, see <https://www.gnu.org/licenses/>.
 */


/**
 * Implementation of the Snake model module.
 *
 * @author Kevin Cruse
 */
#include "model/snake_model.h"


#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>


#include "controller/system_time/system_time.h"
#include "view/sound/notes.h"


const ModelFunctions SNAKE_MODEL_FUNCTIONS = {snake_create, snake_destroy, snake_action, snake_move, snake_next_frame};


/**
 * Frees multiple pointers at once.
 *
 * @param count Number of pointers to free.
 * @param ... Pointers to free.
 */
static void snake_free_multiple(int count, ...);


/**
 * Retrieves an array of (row, column) pairs of free tiles.
 *
 * @param model Model to retrieve free tiles from.
 * @param free_tiles Pointer to pointer in which to store array of (row, column) pairs.
 *
 * @returns Number of free tiles found.
 * @throws ENOMEM Device is out of memory.
 */
static int snake_get_free_tiles(const Model* model, int (** free_tiles)[2]);


/**
 * Wraps the given coordinate around the given size using the Euclidean modulo.
 *
 * @param coordinate Coordinate to wrap.
 * @param size Size to wrap around.
 *
 * @returns Wrapped coordinate.
 */
static int snake_wrap(int coordinate, int size);


Model* snake_create(va_list args) {
    // Extracts number of food tiles from variadic arguments
    int num_food_tiles = va_arg(args, int);

    // Create new Snake model
    Model* model = (Model*) malloc(sizeof(Model));
    if (errno == ENOMEM) return NULL;
    model->game_over = false;
    model->current_note = NOTE_NONE;

    // Create new Snake board
    bool (* board)[MODEL_COLS] = (bool (*)[]) calloc(MODEL_ROWS, sizeof(bool[MODEL_COLS]));
    if (errno == ENOMEM) {
        free(model);
        return NULL;
    }
    model->board = board;
    board[0][0] = true;

    // Create new set of game-specific data for Snake
    SnakeGameData* game_data = (SnakeGameData*) malloc(sizeof(SnakeGameData));
    if (errno == ENOMEM) {
        snake_free_multiple(2, model, board);
        return NULL;
    }
    model->game_data = (void*) game_data;
    game_data->current_direction = DIRECTION_RIGHT;

    // Start with a snake of size one in the top left corner
    SnakeTileNode* snake_tile_node = (SnakeTileNode*) malloc(sizeof(SnakeTileNode));
    if (errno == ENOMEM) {
        snake_free_multiple(3, model, board, game_data);
        return NULL;
    }
    game_data->snake_tile_list_head = snake_tile_node;
    game_data->snake_tile_list_tail = snake_tile_node;
    snake_tile_node->position[0] = 0;
    snake_tile_node->position[1] = 0;
    snake_tile_node->prev = NULL;

    // Create new food tile list
    bool (* food_tiles)[MODEL_COLS] = (bool (*)[]) calloc(MODEL_ROWS, sizeof(bool[MODEL_COLS]));
    if (errno == ENOMEM) {
        snake_free_multiple(4, model, board, game_data, snake_tile_node);
        return NULL;
    }
    game_data->food_tiles = food_tiles;

    // Get list of (row, column) pairs indicating free board tiles
    // and cap number of food tiles to the number of free tiles
    int (* free_tiles)[2];
    int num_free_tiles = snake_get_free_tiles(model, &free_tiles);
    if (errno == ENOMEM) {
        snake_free_multiple(5, model, board, game_data, snake_tile_node, food_tiles);
        return NULL;
    }
    if (num_food_tiles > num_free_tiles) {
        num_food_tiles = num_free_tiles;
    }

    // Put food tiles in random positions on the board
    for (int i = 0; i < num_food_tiles; i++) {
        int tile = rand() % num_free_tiles;
        int row = free_tiles[tile][0];
        int col = free_tiles[tile][1];

        board[row][col] = food_tiles[row][col] = true;

        // Once tile has been chosen, remove it from free tile list
        for (int j = tile; j < num_food_tiles - 1; j++) {
            free_tiles[j][0] = free_tiles[j + 1][0];
            free_tiles[j][1] = free_tiles[j + 1][1];
        }
    }
    free(free_tiles);

    return model;
}


void snake_destroy(Model** model) {
    // Clear Snake board
    free((*model)->board);

    SnakeGameData* game_data = (SnakeGameData*) (*model)->game_data;

    // Clear snake tile list
    SnakeTileNode* prev = game_data->snake_tile_list_tail;
    SnakeTileNode* next;
    while (prev != NULL) {
        next = prev;
        prev = prev->prev;
        free(next);
    }

    // Clear food tile board
    free(game_data->food_tiles);

    // Clear set of game-specific data
    free(game_data);

    // Clear Snake model
    free(*model);
    *model = NULL;
}


void snake_action(Model* model) {
    (void) model;
}


void snake_move(Model* model, Direction direction) {
    // Seed random number generator with time of first direction change
    static bool first_move = true;
    if (first_move) {
        srand(system_time_get());
    }

    ((SnakeGameData*) model->game_data)->current_direction = direction;
}


void snake_next_frame(Model* model) {
    static int frame = 0;

    // Move and play note every other frame
    if (frame % 2 == 0) {
        // Update board with removal of old tail position
        SnakeGameData* game_data = (SnakeGameData*) model->game_data;
        SnakeTileNode* snake_tile_list_head = game_data->snake_tile_list_head;
        SnakeTileNode* snake_tile_list_tail = game_data->snake_tile_list_tail;
        int* position = snake_tile_list_tail->position;
        if (position[0] >= 0 && position[1] >= 0) {
            model->board[position[0]][position[1]] = false;
        }

        // If snake is longer than one tile, move tail node to head
        if (snake_tile_list_head != snake_tile_list_tail) {
            // Update tail's position to match that of head
            position[0] = snake_tile_list_head->position[0];
            position[1] = snake_tile_list_head->position[1];

            // Connect old head to new head
            snake_tile_list_head->prev = snake_tile_list_tail;

            // Update references to head and tail nodes
            snake_tile_list_head = game_data->snake_tile_list_head = snake_tile_list_tail;
            snake_tile_list_tail = game_data->snake_tile_list_tail = snake_tile_list_tail->prev;

            // Update endpoint
            snake_tile_list_head->prev = NULL;
        }

        // Move new head tile in the direction currently being faced
        switch (game_data->current_direction) {
            case DIRECTION_UP:
                position[0] = snake_wrap(position[0] - 1, MODEL_ROWS);
                break;
            case DIRECTION_DOWN:
                position[0] = snake_wrap(position[0] + 1, MODEL_ROWS);
                break;
            case DIRECTION_LEFT:
                position[1] = snake_wrap(position[1] - 1, MODEL_ROWS);
                break;
            case DIRECTION_RIGHT:
                position[1] = snake_wrap(position[1] + 1, MODEL_ROWS);
                break;
            default:
                break;
        }

        if (model->board[position[0]][position[1]]) {
            // If snake has run into an occupied tile that is a food tile, then replace food tile
            // and grow snake. Otherwise, occupied tile is a snake tile, and game is lost
            if (game_data->food_tiles[position[0]][position[1]]) {
                // If tile is a food tile, play an E
                model->current_note = NOTE_E5;

                // Remove old food tile
                game_data->food_tiles[position[0]][position[1]] = false;

                // Get list of available spots to put new food tile
                int (* free_tiles)[2];
                int num_free_tiles = snake_get_free_tiles(model, &free_tiles);
                if (errno == ENOMEM) return;

                // If there are no available spots, the game is won
                if (num_free_tiles == 0) {
                    model->game_over = true;
                    return;
                }

                // Otherwise, choose an available tile to be a new food tile
                int tile = rand() % num_free_tiles;
                int row = free_tiles[tile][0];
                int col = free_tiles[tile][1];
                free(free_tiles);

                // Update game boards
                model->board[row][col] = true;
                game_data->food_tiles[row][col] = true;

                // Grow snake in size
                SnakeTileNode* new_snake_tile = (SnakeTileNode*) malloc(sizeof(SnakeTileNode));
                new_snake_tile->position[0] = -1;
                new_snake_tile->position[1] = -1;
                new_snake_tile->prev = snake_tile_list_tail;
                game_data->snake_tile_list_tail = new_snake_tile;
            } else {
                model->game_over = true;
                return;
            }
        } else {
            // If snake has not run into a tile, play an A
            model->current_note = NOTE_A4;
        }

        // Update board with new head tile
        model->board[position[0]][position[1]] = true;
    } else {
        model->current_note = NOTE_NONE;
    }

    frame = (frame + 1) % 2;
}


static void snake_free_multiple(int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        free(va_arg(args, void*));
    }
    va_end(args);
}


static int snake_get_free_tiles(const Model* model, int (** free_tiles)[2]) {
    *free_tiles = (int (*)[]) malloc(MODEL_ROWS * MODEL_COLS * sizeof(int[2]));
    if (errno == ENOMEM) return 0;

    int num_free_tiles = 0;
    for (int row = 0; row < MODEL_ROWS; row++) {
        for (int col = 0; col < MODEL_COLS; col++) {
            if (!model->board[row][col]) {
                (*free_tiles)[num_free_tiles][0] = row;
                (*free_tiles)[num_free_tiles][1] = col;

                num_free_tiles++;
            }
        }
    }

    return num_free_tiles;
}


static int snake_wrap(int coordinate, int size) {
    if (coordinate >= 0) {
        return coordinate % size;
    } else {
        return coordinate % size + size;
    }
}
