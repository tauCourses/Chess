#ifndef CHESS_GUIMANAGER_H
#define CHESS_GUIMANAGER_H

#include <SDL.h>
#include <stdlib.h>
#include "MainWindow.h"
#include "LoadGameWindow.h"
#include "ModeWindow.h"
#include "DifficultyWindow.h"
#include "ColorWindow.h"
#include "GameWindow.h"

/**
 * GUIManager summary:
 * the GUIManager module is the main module of the GUI and handle all game management
 */

typedef enum{
    MAIN_WINDOW_ACTIVE,
    LOAD_WINDOW_ACTIVE,
    MODE_WINDOW_ACTIVE,
    DIFFICULTY_WINDOW_ACTIVE,
    COLOR_WINDOW_ACTIVE,
    GAME_WINDOW_ACTIVE
}ACTIVE_WINDOW;

typedef enum{
    MANAGER_QUIT,
    MANAGER_ERROR,
    MANAGER_NONE,
}MANAGER_EVENT;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;

    MainWindow* mainWindow;
    LoadWindow* loadWindow;
    ModeWindow* modeWindow;
    DifficultyWindow* difficultyWindow;
    ColorWindow* colorWindow;
    GameWindow* gameWindow;
    ACTIVE_WINDOW activeWindow;
    ACTIVE_WINDOW lastWindow;
    BoardLayout* leftBoard;
    BoardLayout* rightBoard;
} GUIManager;

/**
 *  create new Game window
 *  @param renderer - the renderer for the window
 *  game - the game for which the game window is created
 *  @return
 *  the new Game window.
 */
int mainGUI();

/**
 *  create new Game manager
 *  @param none
 *  @return the new Game manager.
 */
GUIManager* managerCreate();

/**
 *  create sides board in menus
 *  @param src - game manager to create in
 *  @return void
 */
void createSidesBoards(GUIManager* src);

/**
 *  create new windows for Game manager
 *  @param src - game manager to create in
 *  @return true if success, false otherwise.
 */
bool createWindows(GUIManager* gui);

/**
 *  destroy Game manager
 *  @param src - game manager to destroy
 *  @return void
 */
void managerDestroy(GUIManager* src);

/**
 *  draw Game manager
 *  @param src - game manager to draw
 *  @return true if success, false otherwise
 */
bool managerDraw(GUIManager* src);

/**
 *  hides the current window
 *  @param src - game manager to hide window in
 *  @return void
 */
void hideCurrentWindow(GUIManager* src);

/**
 *  switch the current window with another
 *  @param src - game manager to switch in
 *  next - the window to be switched to
 *  @return void
 */
void switchWindow(GUIManager* src, ACTIVE_WINDOW next);

/**
 *  hides the current window
 *  @param src - game manager to hide window in
 *  @return void
 */
MANAGER_EVENT managerHandleEvent(GUIManager* src, SDL_Event* event) ;

/**
 *  handle main event
 *  @param src - game manager to handle event
 *  event - the event
 *  @return manager event
 */
MANAGER_EVENT handleManagerDueToMainEvent(GUIManager* src, MAIN_WINDOW_EVENTS event);

/**
 *  handle load event
 *  @param src - game manager to handle event
 *  event - the event
 *  @return manager event
 */
MANAGER_EVENT handleManagerDueToLoadEvent(GUIManager* src, LOAD_WINDOW_EVENTS event);

/**
 *  handle mode event
 *  @param src - game manager to handle event
 *  event - the event
 *  @return manager event
 */
MANAGER_EVENT handleManagerDueToModeEvent(GUIManager* src, MODE_WINDOW_EVENTS event);

/**
 *  handle difficulty event
 *  @param src - game manager to handle event
 *  event - the event
 *  @return manager event
 */
MANAGER_EVENT handleManagerDueToDifficultyEvent(GUIManager* src, DIFFICULTY_WINDOW_EVENTS event);

/**
 *  handle color event
 *  @param src - game manager to handle event
 *  event - the event
 *  @return manager event
 */
MANAGER_EVENT handleManagerDueToColorEvent(GUIManager* src, COLOR_WINDOW_EVENTS event);

/**
 *  handle game event
 *  @param src - game manager to handle event
 *  event - the event
 *  @return manager event
 */
MANAGER_EVENT handleManagerDueToGameEvent(GUIManager* src, GAME_WINDOW_EVENTS event);

#endif //CHESS_GUIMANAGER_H
