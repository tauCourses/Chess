#include "GUIManager.h"
#include "ModeWindow.h"
#include "MainWindow.h"
#include "DifficultyWindow.h"

int mainGUI()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    GUIManager* gui = managerCreate();
    if (gui == NULL ) {
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    while (1) {
        SDL_WaitEvent(&event);
        if(managerHandleEvent(gui,&event) == MANAGER_QUIT)
            break;

        managerDraw(gui);
    }
    managerDestroy(gui);
    SDL_Quit();
    return 0;
}

GUIManager* managerCreate()
{
    GUIManager* gui = calloc(sizeof(GUIManager), sizeof(char));
    if (gui == NULL )
        return NULL;

    gui->window = SDL_CreateWindow("SP Chess", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, 1000, 730, SDL_WINDOW_OPENGL);
    if (gui->window == NULL)
        goto error;

    gui->renderer = SDL_CreateRenderer(gui->window, -1, SDL_RENDERER_ACCELERATED);
    if (gui->renderer == NULL)
        goto error;

    createSidesBoards(gui);
    if(gui->leftBoard == NULL || gui->rightBoard == NULL)
        goto error;

    if(createWindows(gui) == false)
        goto error;

    gui->activeWindow = MAIN_WINDOW_ACTIVE;
    gui->lastWindow = MAIN_WINDOW_ACTIVE;
    managerDraw(gui);
    return gui;

    error:
    managerDestroy(gui);
    return NULL ;
}

bool createWindows(GUIManager* gui)
{
    gui->mainWindow = createMainWindow(gui->renderer);
    if (gui->mainWindow == NULL )
        return false;

    gui->loadWindow = createLoadWindow(gui->renderer);
    if (gui->loadWindow == NULL )
        return false;

    gui->modeWindow = createModeWindow(gui->renderer);
    if (gui->modeWindow == NULL )
        return false;

    gui->difficultyWindow = createDifficultyWindow(gui->renderer);
    if (gui->difficultyWindow == NULL )
        return false;

    gui->colorWindow = createColorWindow(gui->renderer);
    if (gui->colorWindow == NULL )
        return false;

    return true;
}
void createSidesBoards(GUIManager* gui)
{
    gui->leftBoard = createBoardLayout((SDL_Point){.x=0,.y=0}, 3, 10);
    gui->rightBoard = createBoardLayout((SDL_Point){.x=760,.y=0}, 3, 10);
}

void managerDestroy(GUIManager* gui)
{
    if (gui == NULL)
        return;

    if(gui->mainWindow != NULL)
        destroyMainWindow(gui->mainWindow);
    if(gui->loadWindow != NULL)
        destroyLoadWindow(gui->loadWindow);
    if(gui->modeWindow != NULL)
        destroyModeWindow(gui->modeWindow);
    if(gui->difficultyWindow != NULL)
        destroyDifficultyWindow(gui->difficultyWindow);
    if(gui->colorWindow != NULL)
        destroyColorWindow(gui->colorWindow);
    if(gui->gameWindow != NULL)
        destroyGameWindow(gui->gameWindow);

    if (gui->leftBoard != NULL )
        destroyBoardLayout(gui->leftBoard);
    if (gui->rightBoard != NULL )
        destroyBoardLayout(gui->rightBoard);

    //renderer destroy:
    if (gui->renderer != NULL )
        SDL_DestroyRenderer(gui->renderer);

    if (gui->window != NULL)
        SDL_DestroyWindow(gui->window);


    free(gui);
}

void managerDraw(GUIManager* gui)
{
    if (gui == NULL)
    {
        printf("null draw");
        return;
    }

    switch(gui->activeWindow)
    {
        case MAIN_WINDOW_ACTIVE:
            drawMainWindow(gui->mainWindow);
            drawBoardLayout(gui->renderer, gui->leftBoard);
            drawBoardLayout(gui->renderer, gui->rightBoard);
            break;
        case LOAD_WINDOW_ACTIVE:
            drawLoadWindow(gui->loadWindow);
            drawBoardLayout(gui->renderer, gui->leftBoard);
            drawBoardLayout(gui->renderer, gui->rightBoard);
            break;
        case MODE_WINDOW_ACTIVE:
            drawModeWindow(gui->modeWindow);
            drawBoardLayout(gui->renderer, gui->leftBoard);
            drawBoardLayout(gui->renderer, gui->rightBoard);
            break;
        case DIFFICULTY_WINDOW_ACTIVE:
            drawDifficultyWindow(gui->difficultyWindow);
            drawBoardLayout(gui->renderer, gui->leftBoard);
            drawBoardLayout(gui->renderer, gui->rightBoard);
            break;
        case COLOR_WINDOW_ACTIVE:
            drawColorWindow(gui->colorWindow);
            drawBoardLayout(gui->renderer, gui->leftBoard);
            drawBoardLayout(gui->renderer, gui->rightBoard);
            break;
        case GAME_WINDOW_ACTIVE:
            drawGameWindow(gui->gameWindow);
            break;
        default:
            printf("unknown window to draw %d\n", gui->activeWindow); //TODO -> WHAT WE SHOULD DO IN BUGS?
    }
    SDL_RenderPresent(gui->renderer);

}

void switchWindow(GUIManager* gui, ACTIVE_WINDOW next)
{
    gui->lastWindow = gui->activeWindow;
    gui->activeWindow = next;
}

MANAGER_EVENT managerHandleEvent(GUIManager* gui, SDL_Event* event) {
    if (gui == NULL || event == NULL )
        return MANAGER_NONE;

    switch(gui->activeWindow)
    {
        case MAIN_WINDOW_ACTIVE:
            return handleManagerDueToMainEvent(gui, handleEventMainWindow(gui->mainWindow, event));
        case LOAD_WINDOW_ACTIVE:
            return handleManagerDueToLoadEvent(gui, handleEventLoadWindow(gui->loadWindow, event));
        case MODE_WINDOW_ACTIVE:
            return handleManagerDueToModeEvent(gui, handleEventModeWindow(gui->modeWindow, event));
        case DIFFICULTY_WINDOW_ACTIVE:
            return handleManagerDueToDifficultyEvent(gui, handleEventDifficultyWindow(gui->difficultyWindow, event));
        case COLOR_WINDOW_ACTIVE:
            return handleManagerDueToColorEvent(gui, handleEventColorWindow(gui->colorWindow, event));
        case GAME_WINDOW_ACTIVE:
            return handleManagerDueToGameEvent(gui, handleEventGameWindow(gui->gameWindow, event));
        default:
            printf("unkonwn event\n"); //TODO -> WHAT WE SHOULD DO IN BUGS?
    }

    return MANAGER_NONE; //TODO -> WHAT WE SHOULD DO IN BUGS?
}

MANAGER_EVENT handleManagerDueToMainEvent(GUIManager* gui, MAIN_WINDOW_EVENTS event)
{
    if (gui == NULL )
        return MANAGER_NONE;

    switch (event)
    {
        case MAIN_EXIT:
            return MANAGER_QUIT;
            break;
        case MAIN_START:
            switchWindow(gui, MODE_WINDOW_ACTIVE);
            return MANAGER_NONE;
            break;
        case MAIN_LOAD:
            switchWindow(gui, LOAD_WINDOW_ACTIVE);
            return MANAGER_NONE;
            break;
        case MAIN_INVALID_ARGUMENT:
            printf("INVALID, BUG1?!\n"); //TODO -> WHAT WE SHOULD DO IN BUGS?
            return MANAGER_NONE;
            break;
        case MAIN_NONE:
            return MANAGER_NONE;
            break;
        default:
            return MANAGER_NONE; //TODO -> WHAT WE SHOULD DO IN BUGS?
    }

    return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToLoadEvent(GUIManager* gui, LOAD_WINDOW_EVENTS event)
{
    if (gui == NULL )
        return MANAGER_NONE;

    switch (event)
    {
        case LOAD_EXIT:
            return MANAGER_QUIT;
            break;
        case LOAD_BACK:
            switchWindow(gui, gui->lastWindow);
            return MANAGER_NONE;
            break;

        case LOAD_START:
            if(gui->gameWindow != NULL)
                destroyGameWindow(gui->gameWindow);
            GameManager* game = loadGameFromSlots(gui->loadWindow->slotChosed+1);
            if(game == NULL)
                return MANAGER_NONE;
            gui->gameWindow = createGameWindow(gui->renderer,game);
            gui->lastWindow = gui->activeWindow;
            gui->activeWindow = GAME_WINDOW_ACTIVE;

            return MANAGER_NONE;
            break;
        case LOAD_INVALID_ARGUMENT:
            printf("INVALID, BUG2?!\n"); //TODO -> WHAT WE SHOULD DO IN BUGS?
            return MANAGER_NONE;
            break;
        case LOAD_NONE:
            // printf("TODO BOOM\n");
            return MANAGER_NONE;
            break;
        default:
            printf("INVALID, BUG3?!\n"); //TODO -> WHAT WE SHOULD DO IN BUGS?
            return MANAGER_NONE;
    }

    return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToModeEvent(GUIManager* gui, MODE_WINDOW_EVENTS event)
{
    if (gui == NULL )
        return MANAGER_NONE;

    switch (event)
    {
        case MODE_EXIT:
            return MANAGER_QUIT;
            break;
        case MODE_BACK:
            switchWindow(gui, MAIN_WINDOW_ACTIVE);
            return MANAGER_NONE;
            break;
        case MODE_START:
            if(gui->gameWindow != NULL)
                destroyGameWindow(gui->gameWindow);
            GameManager* game = createTwoPlayersGame();
            if(game == NULL) {
                printf("null\n");
                return MANAGER_NONE;
            }
            gui->gameWindow = createGameWindow(gui->renderer, game); //TODO -> CHANGE IT TO two player chess
            if(gui->gameWindow == NULL)
            {
                printf("null game\n");
                return MANAGER_NONE;
            }
            gui->lastWindow = gui->activeWindow;
            gui->activeWindow = GAME_WINDOW_ACTIVE;

            return MANAGER_NONE;
            break;
        case MODE_NEXT:
            switchWindow(gui, DIFFICULTY_WINDOW_ACTIVE);
            return MANAGER_NONE;
            break;
        case MODE_INVALID_ARGUMENT:
            printf("INVALID, BUG4?!\n"); //TODO -> WHAT WE SHOULD DO IN BUGS?
            return MANAGER_NONE;
            break;
        case MODE_NONE:
            return MANAGER_NONE;
            break;
        default:
            printf("INVALID, BUG5?!\n"); //TODO -> WHAT WE SHOULD DO IN BUGS?
            return MANAGER_NONE;
    }

    return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToDifficultyEvent(GUIManager* gui, DIFFICULTY_WINDOW_EVENTS event)
{
    if (gui == NULL )
        return MANAGER_NONE;

    switch (event)
    {
        case DIFFICULTY_EXIT:
            return MANAGER_QUIT;
            break;
        case DIFFICULTY_BACK:
            switchWindow(gui, MODE_WINDOW_ACTIVE);
            return MANAGER_NONE;
            break;
        case DIFFICULTY_NEXT:
            switchWindow(gui, COLOR_WINDOW_ACTIVE);
            return MANAGER_NONE;
            break;
        case DIFFICULTY_NONE:
            return MANAGER_NONE;
            break;
        case DIFFICULTY_INVALID_ARGUMENT:
            printf("INVALID, BUG4?!\n"); //TODO -> WHAT WE SHOULD DO IN BUGS?
            return MANAGER_NONE;
            break;

        default:
            printf("INVALID, BUG5?!\n"); //TODO -> WHAT WE SHOULD DO IN BUGS?
            return MANAGER_NONE;
    }
    return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToColorEvent(GUIManager* gui, COLOR_WINDOW_EVENTS event)
{
    if (gui == NULL )
        return MANAGER_NONE;

    switch (event)
    {
        case COLOR_EXIT:
            return MANAGER_QUIT;
            break;
        case COLOR_BACK:
            switchWindow(gui, DIFFICULTY_WINDOW_ACTIVE);
            return MANAGER_NONE;
            break;
        case COLOR_START:
            if(gui->gameWindow != NULL)
                destroyGameWindow(gui->gameWindow);

            GameManager* game = createOnePlayerGame(gui->difficultyWindow->configurationChosen,
                                            getColorFromColorWindow(gui->colorWindow));
            gui->gameWindow = createGameWindow(gui->renderer, game); //TODO -> CHANGE IT TO two player chess
            gui->lastWindow = gui->activeWindow;
            gui->activeWindow = GAME_WINDOW_ACTIVE;

            return MANAGER_NONE;
            break;
        case COLOR_NONE:
            return MANAGER_NONE;
            break;
        case COLOR_INVALID_ARGUMENT:
            printf("INVALID, BUG4?!\n"); //TODO -> WHAT WE SHOULD DO IN BUGS?
            return MANAGER_NONE;
            break;

        default:
            printf("INVALID, BUG5?!\n"); //TODO -> WHAT WE SHOULD DO IN BUGS?
            return MANAGER_NONE;
    }
    return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToGameEvent(GUIManager* gui, GAME_WINDOW_EVENTS event)
{
    if (gui == NULL )
        return MANAGER_NONE;

    switch (event)
    {
        case GAME_EXIT:
            return MANAGER_QUIT;
            break;
        case GAME_MAIN:
            switchWindow(gui, MAIN_WINDOW_ACTIVE);
            return MANAGER_NONE;
            break;
        case GAME_LOAD:
            switchWindow(gui, LOAD_WINDOW_ACTIVE);
            return MANAGER_NONE;
            break;
        case GAME_NONE:
            return MANAGER_NONE;
            break;
        case GAME_INVALID_ARGUMENT:
            printf("INVALID, BUG4?!\n"); //TODO -> WHAT WE SHOULD DO IN BUGS?
            return MANAGER_NONE;
            break;

        default:
            printf("INVALID, BUG5?!\n"); //TODO -> WHAT WE SHOULD DO IN BUGS?
            return MANAGER_NONE;
    }
    return MANAGER_NONE;
}