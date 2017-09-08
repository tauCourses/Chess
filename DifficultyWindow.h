#ifndef CHESS_DIFFICULTYWINDOW_H
#define CHESS_DIFFICULTYWINDOW_H

#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Button.h"

typedef enum {
    DIFFICULTY_NEXT, DIFFICULTY_BACK, DIFFICULTY_EXIT,  DIFFICULTY_INVALID_ARGUMENT, DIFFICULTY_NONE
} DIFFICULTY_WINDOW_EVENTS;

typedef struct  {
    SDL_Window* window;
    SDL_Renderer* renderer;

    Button* title; //not really a button. click on not changing it
    Button* noob;
    Button* easy;
    Button* moderate;
    Button* hard;
    Button* expert;
    Button* back;
    Button* next;
    int configurationChosen;
} DifficultyWindow;

DifficultyWindow* createDifficultyWindow();
void createDifficultyButtons(DifficultyWindow* window);
void destroyDifficultyWindow(DifficultyWindow *window);
void drawDifficultyWindow(DifficultyWindow *window);
DIFFICULTY_WINDOW_EVENTS handleEventDifficultyWindow(DifficultyWindow *window, SDL_Event *event);

void hideDifficultyWindow(DifficultyWindow* window);
void showDifficultyWindow(DifficultyWindow* window);

void changeChoiceDifficultyWindow(DifficultyWindow* window, int i);

#endif //CHESS_DIFFICULTYWINDOW_H
