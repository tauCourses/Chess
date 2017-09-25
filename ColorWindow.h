#ifndef CHESS_COLORWINDOW_H
#define CHESS_COLORWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"
#include "GameManager.h"

/**
 * ColorWindow summary:
 * the select color window module
 */

#define SELECT_COLOR_TITLE "images/titles/selectYourColor.bmp"

typedef enum {
    COLOR_START, COLOR_BACK, COLOR_EXIT,  COLOR_ERROR, COLOR_NONE
} COLOR_WINDOW_EVENTS;

typedef struct  {
    SDL_Renderer* renderer;

    Button* title; //not really a button. click on not changing it
    Button* colorSwitch;

    Button* back;
    Button* start;
} ColorWindow;


/**
 *  create color window
 *  @param renderer - the renderer for the window
 *  @return
 *  the new color window.
 */
ColorWindow* createColorWindow(SDL_Renderer* renderer);

/**
 *  create buttons for color window
 *  @param window - the window to create buttons for
 *  @return void
 */
void createColorButtons(ColorWindow* window);
/**
 *  destroy color window
 *  @param window - the window to destroy
 *  @return void
 */
void destroyColorWindow(ColorWindow *window);

/**
 *  draw color window
 *  @param window - the window to draw
 *  @return true if success, false otherwise.
 */
bool drawColorWindow(ColorWindow *window);

/**
 *  handle event in color window
 *  @param window - the window to handle event in
 *  event - the SDL event
 *  @return which event occurred
 */
COLOR_WINDOW_EVENTS handleEventColorWindow(ColorWindow *window, SDL_Event *event);

/**
 *  return color chosen from color window
 *  @param window - the window that color is chosen from
 *  @return the color that was chosen
 */
PLAYER_COLOR getColorFromColorWindow(ColorWindow *window);

#endif //CHESS_COLORWINDOW_H
