

#ifndef CHESS_LOADGAMEWINDOW_H
#define CHESS_LOADGAMEWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"
#include "Storage.h"

/**
 * Load Game Window summary:
 * the Load Game Window module handle the window of the load feature
 */

typedef enum {
    LOAD_BACK, LOAD_EXIT, LOAD_START, LOAD_ERROR, LOAD_NONE
} LOAD_WINDOW_EVENTS;

typedef struct  {
    SDL_Renderer* renderer;

    Button* slots[MAX_NUMBER_OF_LOAD_GAMES];
    Button* back;
    Button* load;
    int slotChosed;
} LoadWindow;


/**
 *  create new load window
 *  @param renderer - the renderer for the window
 *  @return
 *  the new load window.
 */
LoadWindow* createLoadWindow(SDL_Renderer* renderer);

/**
 *  create new load buttons
 *  @param window - window to create new load buttons in
 *  @return void
 */
void createLoadButtons(LoadWindow* window);

/**
 *  destroy load window
 *  @param window - window to destroy
 *  @return void
 */
void destroyLoadWindow(LoadWindow *window);

/**
 *  draw load window
 *  @param window - window to draw
 *  @return true if success, false otherwise
 */
bool drawLoadWindow(LoadWindow *window);

/**
 *  handle event in load window
 *  @param window - window to handle event in
 *  event - SDL event to handle
 *  @return next state of window
 */
LOAD_WINDOW_EVENTS handleEventLoadWindow(LoadWindow *window, SDL_Event *event);

/**
 *  chagne choice of game slot in load window
 *  @param window - window to change choice in
 *  i - number of new game slot number
 *  @return void
 */
void changeChoiceLoadWindow(LoadWindow* window, int i);


#endif //CHESS_LOADGAMEWINDOW_H
