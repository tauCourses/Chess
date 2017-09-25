#ifndef CHESS_GAMEWINDOW_H
#define CHESS_GAMEWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"
#include "GameLayout.h"
#include "Storage.h"
#include "AI.h"

/**
 * GameWindow summary:
 * the GameWindow module handle all functions that belongs to the game window
 */

typedef enum {
    GAME_LOAD, GAME_MAIN, GAME_EXIT,  GAME_WINDOW_ERROR, GAME_NONE, GAME_CONTINUE
} GAME_WINDOW_EVENTS;

typedef struct  {
    SDL_Renderer* renderer;

    Button* restart;
    Button* save;
    Button* load;
    Button* undo;

    Button* main;
    Button* exit;

    GameLayout* board;
    GameManager* game;

    bool isSaved;
} GameWindow;

/**
 *  create new Game window
 *  @param renderer - the renderer for the window
 *  game - the game for which the game window is created
 *  @return
 *  the new Game window.
 */
GameWindow* createGameWindow(SDL_Renderer* renderer, GameManager* game);

/**
 *  create new Game buttons
 *  @param window - the game window to create in
 *  @return void
 */
void createGameButtons(GameWindow* window);

/**
 *  destroy Game window
 *  @param window - the game window to create in
 *  @return void
 */
void destroyGameWindow(GameWindow *window);

/**
 *  draw Game window
 *  @param window - the game window to draw
 *  @return true if success, false otherwise
 */
bool drawGameWindow(GameWindow *window);

/**
 *  handle left mouse up event in Game window
 *  @param window - the game window to create in
 *  event - the SDL event of mouse
 *  @return message what next state of window
 */
GAME_WINDOW_EVENTS handleLeftMouseUpGameWindow(GameWindow *window, SDL_Event *event);

/**
 *  handle left mouse down event in Game window
 *  @param window - the game window to create in
 *  event - the SDL event of mouse
 *  @return message what next state of window
 */
GAME_WINDOW_EVENTS  handleLeftMouseDownGameWindow(GameWindow *window, SDL_Event *event);

/**
 *  handle right mouse up event in Game window
 *  @param window - the game window to create in
 *  event - the SDL event of mouse
 *  @return message what next state of window
 */
GAME_WINDOW_EVENTS  handleRightMouseUpGameWindow(GameWindow *window, SDL_Event *event);

/**
 *  handle right mouse down event in Game window
 *  @param window - the game window to create in
 *  event - the SDL event of mouse
 *  @return message what next state of window
 */
GAME_WINDOW_EVENTS  handleRightMouseDownGameWindow(GameWindow *window, SDL_Event *event);


/**
 *  handle event in Game window
 *  @param window - the game window to create in
 *  event - the SDL event
 *  @return message what next state of window
 */
GAME_WINDOW_EVENTS handleEventGameWindow(GameWindow *window, SDL_Event *event);


/**
 *  jumps the confirm exit window
 *  @param none
 *  @return button id of which was chosen
 */
int exitConfirmationMessageBox();

/**
 *  jumps the end game window
 *  @param winnner - the color of the winner
 *  @return button id of which was chosen
 */
int gameEndMessageBox(PLAYER_COLOR winner);

/**
 *  jumps the pawn promotion window
 *  @param player - the color of the current player
 *  @return char of chosen piece
 */
char gamePawnPromotionMessageBox(PLAYER_COLOR player);

#endif //CHESS_GAMEWINDOW_H
