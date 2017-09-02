#ifndef SPSIMPLEMAINWINDOW_H_
#define SPSIMPLEMAINWINDOW_H_
#include "SPWindow.h"
#include "Widget.h"

typedef struct sp_simplewindow_t  SPSimpleWindow;
struct sp_simplewindow_t {
    SDL_Window* window;
    SDL_Renderer* windowRenderer;
    //All widgets in our window
    Widget** widgets;
    int numOfWidgets;
};

SPWindow* createSimpleWindow();
void destroySimpleWindow(SPWindow* src);
void drawSimpleWindow(SPWindow* src);
void handleEvenetSimpleWindow(SPWindow* src, SDL_Event* event);
#endif
