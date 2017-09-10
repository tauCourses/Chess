#include "MainWindow.h"

MainWindow* createMainWindow(SDL_Renderer* renderer)
{
    MainWindow* window = NULL;

    window = calloc(sizeof(MainWindow), sizeof(char));
    if (window == NULL )
        return NULL ;

    window->renderer = renderer;

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

    SDL_Rect startR = { .x = 400, .y = 100, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect loadR = { .x = 400, .y = 200, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect exitR = { .x = 400, .y = 500, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };

    window->newGame = createButton(window->renderer, startR, NEW_GAME_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
    window->load = createButton(window->renderer, loadR, LOAD_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
    window->exit = createButton(window->renderer, exitR, EXIT_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
}

void destroyMainWindow(MainWindow *window)
{
    if (window == NULL)
        return;
    //textures buttons:
    if(window->newGame != NULL)
        destroyButton(window->newGame);
    if(window->load != NULL)
        destroyButton(window->load);
    if(window->exit != NULL)
        destroyButton(window->exit);

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
                return MAIN_START;

            if(clickOnButton(window->load, event->button.x, event->button.y))
                return MAIN_LOAD;

            if(clickOnButton(window->exit, event->button.x, event->button.y))
                return MAIN_EXIT;

            break;

        default:
            return MAIN_NONE;

    }
    return MAIN_NONE;
}