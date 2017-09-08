#include "MainWindow.h"

MainWindow* createMainWindow()
{
    MainWindow* window = NULL;

    window = calloc(sizeof(MainWindow), sizeof(char));
    if (window == NULL )
        return NULL ;

    window->window = SDL_CreateWindow("SP Chess - main", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_OPENGL);

    if (window->window == NULL )
    {
        destroyMainWindow(window);
        printf("Could not create a window1: %s\n", SDL_GetError());
        return NULL ;
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (window->renderer == NULL)
    {
        destroyMainWindow(window);
        printf("Could not create a window2: %s\n", SDL_GetError());
        return NULL;
    }

    createMainButtons(window);
    if(window->newGame == NULL || window->load == NULL || window->exit == NULL)
    {
        destroyMainWindow(window);
        printf("Could not create buttons: %s\n", SDL_GetError());
        return NULL;
    }
    return window;
}

void createMainButtons(MainWindow* window)
{
    if(window == NULL || window->renderer == NULL)
        return;

    SDL_Rect startR = { .x = 450, .y = 100, .h = 100, .w = 250 };
    SDL_Rect loadR = { .x = 450, .y = 250, .h = 100, .w = 250 };
    SDL_Rect exitR = { .x = 450, .y = 500, .h = 100, .w = 250 };
    window->newGame = createButton(window->renderer, startR, "start.bmp", "", BUTTON_TYPE_ONE_OPTION);
    window->load = createButton(window->renderer, loadR, "load.bmp", "", BUTTON_TYPE_ONE_OPTION);
    window->exit = createButton(window->renderer, exitR, "exit.bmp", "", BUTTON_TYPE_ONE_OPTION);
}

void destroyMainWindow(MainWindow *window)
{
    if (window == NULL)
        return;
    //textures buttons:
    destroyButton(window->newGame);
    destroyButton(window->load);
    destroyButton(window->exit);
    //renderer destroy:
    if (window->renderer != NULL )
        SDL_DestroyRenderer(window->renderer);
    //window destroy:
    if (window->window != NULL)
        SDL_DestroyWindow(window->window);

    free(window);
}

void drawMainWindow(MainWindow *window)
{
    if(window==NULL)
        return;


    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_RenderClear(window->renderer);

    drawButton(window->newGame);
    drawButton(window->load);
    drawButton(window->exit);

    SDL_RenderPresent(window->renderer);
}

void hideMainWindow(MainWindow* window)
{
    SDL_HideWindow(window->window);
}

void showMainWindow(MainWindow *window)
{
    SDL_ShowWindow(window->window);
}

MAIN_WINDOW_EVENTS handleEventMainWindow(MainWindow *window, SDL_Event *event)
{
    if(window == NULL || event==NULL)
        return MAIN_INVALID_ARGUMENT;

    switch (event->type)
    {
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE)
                return MAIN_EXIT;
            break;

        case SDL_MOUSEBUTTONUP:
            if(clickOnButton(window->newGame, event->button.x, event->button.y))
            {
                printf("start\n");
                return MAIN_START;
            }
            if(clickOnButton(window->load, event->button.x, event->button.y))
            {
                printf("load\n");
                return MAIN_LOAD;
            }
            if(clickOnButton(window->exit, event->button.x, event->button.y))
            {
                printf("exit\n");
                return MAIN_EXIT;
            }
            break;

        default:
            return MAIN_NONE;

    }
    return MAIN_NONE;
}