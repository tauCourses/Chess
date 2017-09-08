#ifndef CHESS_GUIMANAGER_H
#define CHESS_GUIMANAGER_H

#include <SDL.h>
#include <stdlib.h>
#include "MainWindow.h"
#include "LoadGameWindow.h"
#include "ModeWindow.h"
#include "DifficultyWindow.h"
#include "ColorWindow.h"

typedef enum{
    MAIN_WINDOW_ACTIVE,
    LOAD_WINDOW_ACTIVE,
    MODE_WINDOW_ACTIVE,
    DIFFICULTY_WINDOW_ACTIVE,
    COLOR_WINDOW_ACTIVE
}ACTIVE_WINDOW;

typedef enum{
    MANAGER_QUIT,
    MANAGER_NONE,
}MANAGER_EVENT;

typedef struct {
    MainWindow* mainWindow;
    LoadWindow* loadWindow;
    ModeWindow* modeWindow;
    DifficultyWindow* difficultyWindow;
    ColorWindow* colorWindow;
    ACTIVE_WINDOW activeWin;
} GUIManager;

GUIManager* managerCreate();

void managerDestroy(GUIManager* src);
void managerDraw(GUIManager* src);

MANAGER_EVENT managerHandleEvent(GUIManager* src, SDL_Event* event) ;

MANAGER_EVENT handleManagerDueToMainEvent(GUIManager* src, MAIN_WINDOW_EVENTS event);
MANAGER_EVENT handleManagerDueToLoadEvent(GUIManager* src, LOAD_WINDOW_EVENTS event);
MANAGER_EVENT handleManagerDueToModeEvent(GUIManager* src, MODE_WINDOW_EVENTS event);
MANAGER_EVENT handleManagerDueToDifficultyEvent(GUIManager* src, DIFFICULTY_WINDOW_EVENTS event);
MANAGER_EVENT handleManagerDueToColorEvent(GUIManager* src, COLOR_WINDOW_EVENTS event);

#endif //CHESS_GUIMANAGER_H
