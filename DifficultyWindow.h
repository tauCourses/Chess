#ifndef CHESS_DIFFICULTYWINDOW_H
#define CHESS_DIFFICULTYWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"

/**
 * DifficultyWindow summary:
 * the select difficulty window module
 */

#define SELECT_DIFFICULTY_TITLE "images/titles/Difficulty.bmp"

typedef enum {
    DIFFICULTY_NEXT, DIFFICULTY_BACK, DIFFICULTY_EXIT,  DIFFICULTY_ERROR, DIFFICULTY_NONE
} DIFFICULTY_WINDOW_EVENTS;

typedef struct  {
    SDL_Renderer* renderer;

    Button* title; //not really a button. click on not changing it
    Button* noob;
    Button* easy;
    Button* moderate;
    Button* hard;
    Button* back;
    Button* next;
    int configurationChosen;
} DifficultyWindow;


/**
 *  create difficulty window
 *  @param renderer - the renderer for the window
 *  @return
 *  the new difficulty window.
 */
DifficultyWindow* createDifficultyWindow(SDL_Renderer* renderer);

/**
 *  create difficulty buttons
 *  @param window - the window to create buttons for
 *  @return void
 */
void createDifficultyButtons(DifficultyWindow* window);

/**
 *  destroy difficulty buttons
 *  @param window - the window to destroy
 *  @return void
 */
void destroyDifficultyWindow(DifficultyWindow *window);

/**
 *  draw difficulty window
 *  @param window - the window to draw
 *  @return true if success, false otherwise.
 */
bool drawDifficultyWindow(DifficultyWindow *window);

/**
 *  handle event in difficulty window
 *  @param window - the window to handle event in
 *  event - the SDL event
 *  @return which event occurred
 */
DIFFICULTY_WINDOW_EVENTS handleEventDifficultyWindow(DifficultyWindow *window, SDL_Event *event);

/**
 *  change choice in difficulty window
 *  @param window - the window to change choose in
 *  i - new difficulty number
 *  @return void
 */
void changeChoiceDifficultyWindow(DifficultyWindow* window, int i);

#endif //CHESS_DIFFICULTYWINDOW_H
