#include "GUIManager.h"
#include "ModeWindow.h"
#include "MainWindow.h"
#include "DifficultyWindow.h"
#include "GameManager.h"

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
        MANAGER_EVENT response = managerHandleEvent(gui,&event);
        if(response == MANAGER_QUIT || response == MANAGER_ERROR)
            break;

        if(managerDraw(gui) == false)
            break;
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

bool managerDraw(GUIManager* gui)
{
    if (gui == NULL)
        return false;

    switch(gui->activeWindow)
    {
        case MAIN_WINDOW_ACTIVE:
            if(drawMainWindow(gui->mainWindow) == false)
                return false;
            break;
        case LOAD_WINDOW_ACTIVE:
            if(drawLoadWindow(gui->loadWindow) == false)
                return false;
            break;
        case MODE_WINDOW_ACTIVE:
            if(drawModeWindow(gui->modeWindow) == false)
                return false;
            break;
        case DIFFICULTY_WINDOW_ACTIVE:
            if(drawDifficultyWindow(gui->difficultyWindow) == false)
                return false;
            break;
        case COLOR_WINDOW_ACTIVE:
            if(drawColorWindow(gui->colorWindow) == false)
                return false;

            break;
        case GAME_WINDOW_ACTIVE:
            if(drawGameWindow(gui->gameWindow) == false)
                return false;
            SDL_RenderPresent(gui->renderer);
            return true;
        default:
            return false;
    }
    drawBoardLayout(gui->renderer, gui->leftBoard);
    drawBoardLayout(gui->renderer, gui->rightBoard);
    SDL_RenderPresent(gui->renderer);
    return true;

}

void switchWindow(GUIManager* gui, ACTIVE_WINDOW next)
{
    gui->lastWindow = gui->activeWindow;
    gui->activeWindow = next;
}

MANAGER_EVENT managerHandleEvent(GUIManager* gui, SDL_Event* event) {
    if (gui == NULL || event == NULL )
        return MANAGER_ERROR;

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
            return MANAGER_ERROR;
    }
}

MANAGER_EVENT handleManagerDueToMainEvent(GUIManager* gui, MAIN_WINDOW_EVENTS event)
{
    if (gui == NULL )
        return MANAGER_ERROR;

    switch (event)
    {
        case MAIN_EXIT:
            return MANAGER_QUIT;
        case MAIN_START:
            switchWindow(gui, MODE_WINDOW_ACTIVE);
            return MANAGER_NONE;
        case MAIN_LOAD:
            switchWindow(gui, LOAD_WINDOW_ACTIVE);
            return MANAGER_NONE;
        case MAIN_ERROR:
            printf("Error in main window\n");
            return MANAGER_ERROR;
        case MAIN_NONE:
            return MANAGER_NONE;
        default:
            printf("Invalid main window response\n");
            return MANAGER_ERROR;
    }
}

MANAGER_EVENT handleManagerDueToLoadEvent(GUIManager* gui, LOAD_WINDOW_EVENTS event)
{
    if (gui == NULL )
        return MANAGER_ERROR;

    switch (event)
    {
        case LOAD_EXIT:
            return MANAGER_QUIT;
            break;
        case LOAD_BACK:
            switchWindow(gui, gui->lastWindow);
            return MANAGER_NONE;
        case LOAD_START:
            if(gui->gameWindow != NULL)
                destroyGameWindow(gui->gameWindow);
            GameManager* game = loadGameFromSlots(gui->loadWindow->slotChosed+1);
            if(game == NULL)
            {
                printf("unable to create game\n");
                return MANAGER_ERROR;
            }
            gui->gameWindow = createGameWindow(gui->renderer,game);
            if(gui->gameWindow == NULL)
            {
                printf("unable to create game window\n");
                return MANAGER_ERROR;
            }
            gui->lastWindow = gui->activeWindow;
            gui->activeWindow = GAME_WINDOW_ACTIVE;
            return MANAGER_NONE;
        case LOAD_ERROR:
            printf("Error in load window\n");
            return MANAGER_ERROR;
        case LOAD_NONE:
            return MANAGER_NONE;
        default:
            printf("Invalid load window response\n");
            return MANAGER_ERROR;
    }
}

MANAGER_EVENT handleManagerDueToModeEvent(GUIManager* gui, MODE_WINDOW_EVENTS event)
{
    if (gui == NULL )
        return MANAGER_ERROR;

    switch (event)
    {
        case MODE_EXIT:
            return MANAGER_QUIT;

        case MODE_BACK:
            switchWindow(gui, MAIN_WINDOW_ACTIVE);
            return MANAGER_NONE;

        case MODE_START:
            if(gui->gameWindow != NULL)
                destroyGameWindow(gui->gameWindow);
            GameManager* game = createTwoPlayersGame();
            if(game == NULL)
            {
                printf("unable to create game\n");
                return MANAGER_ERROR;
            }
            gui->gameWindow = createGameWindow(gui->renderer, game);
            if(gui->gameWindow == NULL)
            {
                printf("unable to create game window\n");
                return MANAGER_ERROR;
            }
            gui->lastWindow = gui->activeWindow;
            gui->activeWindow = GAME_WINDOW_ACTIVE;

            return MANAGER_NONE;

        case MODE_NEXT:
            switchWindow(gui, DIFFICULTY_WINDOW_ACTIVE);
            return MANAGER_NONE;

        case MODE_ERROR:
            printf("Error in mode window\n");
            return MANAGER_ERROR;

        case MODE_NONE:
            return MANAGER_NONE;
        default:
            printf("Invalid mode window response\n");
            return MANAGER_ERROR;
    }

}

MANAGER_EVENT handleManagerDueToDifficultyEvent(GUIManager* gui, DIFFICULTY_WINDOW_EVENTS event)
{
    if (gui == NULL )
        return MANAGER_ERROR;

    switch (event)
    {
        case DIFFICULTY_EXIT:
            return MANAGER_QUIT;

        case DIFFICULTY_BACK:
            switchWindow(gui, MODE_WINDOW_ACTIVE);
            return MANAGER_NONE;

        case DIFFICULTY_NEXT:
            switchWindow(gui, COLOR_WINDOW_ACTIVE);
            return MANAGER_NONE;

        case DIFFICULTY_NONE:
            return MANAGER_NONE;

        case DIFFICULTY_ERROR:
            printf("Error in difficulty window\n");
            return MANAGER_ERROR;

        default:
            printf("Invalid difficulty window response\n");
            return MANAGER_ERROR;
    }

}

MANAGER_EVENT handleManagerDueToColorEvent(GUIManager* gui, COLOR_WINDOW_EVENTS event)
{
    if (gui == NULL )
        return MANAGER_ERROR;

    switch (event)
    {
        case COLOR_EXIT:
            return MANAGER_QUIT;

        case COLOR_BACK:
            switchWindow(gui, DIFFICULTY_WINDOW_ACTIVE);
            return MANAGER_NONE;

        case COLOR_START:
            if(gui->gameWindow != NULL)
                destroyGameWindow(gui->gameWindow);

            GameManager* game = createOnePlayerGame(gui->difficultyWindow->configurationChosen+1,
                                            getColorFromColorWindow(gui->colorWindow));
            if(game == NULL)
            {
                printf("unable to create game\n");
                return MANAGER_ERROR;
            }
            if(game->userColor == BLACK_PLAYER)
            {
                if(applyAIMove(game) == NULL)
                {
                    printf("unable to run AI move\n");
                    destroyGame(game);
                    return MANAGER_ERROR;
                }
                destroyMove(popFromHistory(game->history));
            }
            gui->gameWindow = createGameWindow(gui->renderer, game);
            if(gui->gameWindow == NULL)
            {
                printf("unable to create game window\n");
                return MANAGER_ERROR;
            }
            gui->lastWindow = gui->activeWindow;
            gui->activeWindow = GAME_WINDOW_ACTIVE;

            return MANAGER_NONE;

        case COLOR_NONE:
            return MANAGER_NONE;

        case COLOR_ERROR:
            printf("Error in color window\n");
            return MANAGER_ERROR;

        default:
            printf("Invalid color window response\n");
            return MANAGER_ERROR;
    }

}

MANAGER_EVENT handleManagerDueToGameEvent(GUIManager* gui, GAME_WINDOW_EVENTS event)
{
    if (gui == NULL )
        return MANAGER_NONE;

    switch (event)
    {
        case GAME_EXIT:
            return MANAGER_QUIT;

        case GAME_MAIN:
            switchWindow(gui, MAIN_WINDOW_ACTIVE);
            return MANAGER_NONE;

        case GAME_LOAD:
            switchWindow(gui, LOAD_WINDOW_ACTIVE);
            return MANAGER_NONE;

        case GAME_NONE:
            return MANAGER_NONE;

        case GAME_WINDOW_ERROR:
            printf("Error in game window\n");
            return MANAGER_ERROR;

        default:
            printf("Invalid game window response\n");
            return MANAGER_ERROR;
    }
}
