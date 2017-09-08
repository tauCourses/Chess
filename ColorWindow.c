#include "ColorWindow.h"

ColorWindow* createColorWindow() {
    ColorWindow *window = NULL;

    window = calloc(sizeof(ColorWindow), sizeof(char));
    if (window == NULL)
        return NULL;

    window->window = SDL_CreateWindow("SP Chess - Choose mode", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_OPENGL);

    if (window->window == NULL) {
        destroyColorWindow(window);
        return NULL;
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (window->renderer == NULL) {
        destroyColorWindow(window);
        return NULL;
    }

    createColorButtons(window);
    if (window->title == NULL || window->back == NULL || window->black == NULL || window->white == NULL ||
        window->start == NULL)
    {
        destroyColorWindow(window);
        return NULL;
    }

    changeChoiceColorWindow(window, 0);

    return window;
}

void createColorButtons(ColorWindow* window)
{
    if(window == NULL || window->renderer == NULL)
        return;

    //BUTTONS LOCATIONS
    SDL_Rect titleR = { .x = 350, .y = 50, .h = 50, .w = 300 };
    SDL_Rect black = { .x = 200, .y = 200, .h = 50, .w = 250 };
    SDL_Rect white = { .x = 600, .y = 200, .h = 50, .w = 250 };

    SDL_Rect startR = { .x = 200, .y = 900, .h = 100, .w = 250 };
    SDL_Rect backR = { .x = 550, .y = 900, .h = 100, .w = 250 };

    //SETUP BUTTONS:
    window->title = createButton(window->renderer, titleR, "newGame.bmp", "", BUTTON_TYPE_DEGENERATED);

    window->black = createButton(window->renderer, black, "start.bmp", "exit.bmp", BUTTON_TYPE_CHOICE);
    window->white = createButton(window->renderer, white, "start.bmp", "exit.bmp", BUTTON_TYPE_CHOICE);

    window->start = createButton(window->renderer, startR, "start.bmp", "exit.bmp", BUTTON_TYPE_ONE_OPTION);
    window->back = createButton(window->renderer, backR, "back.bmp", "", BUTTON_TYPE_ONE_OPTION);
}

void destroyColorWindow(ColorWindow *window)
{
    if (window == NULL)
        return;
    //buttons:
    destroyButton(window->title);

    destroyButton(window->black);
    destroyButton(window->white);

    destroyButton(window->start);
    destroyButton(window->back);

    //renderer destroy:
    if (window->renderer != NULL )
        SDL_DestroyRenderer(window->renderer);
    //window destroy:
    if (window->window != NULL)
        SDL_DestroyWindow(window->window);

    free(window);
}

void drawColorWindow(ColorWindow *window)
{
    if(window==NULL)
        return;

    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_RenderClear(window->renderer);

    drawButton(window->title);

    drawButton(window->black);
    drawButton(window->white);

    drawButton(window->start);
    drawButton(window->back);

    SDL_RenderPresent(window->renderer);
}

void hideColorWindow(ColorWindow* window)
{
    SDL_HideWindow(window->window);
}

void showColorWindow(ColorWindow* window)
{
    SDL_ShowWindow(window->window);
}

COLOR_WINDOW_EVENTS handleEventColorWindow(ColorWindow *window, SDL_Event *event)
{
    if(window == NULL || event==NULL)
        return COLOR_INVALID_ARGUMENT;

    switch (event->type)
    {
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE)
                return COLOR_EXIT;
            break;
        case SDL_MOUSEBUTTONUP:
            if(clickOnButton(window->back, event->button.x, event->button.y))
                return COLOR_BACK;
            if(clickOnButton(window->start, event->button.x, event->button.y))
                return COLOR_START;
            if(clickOnButton(window->black, event->button.x, event->button.y))
                changeChoiceColorWindow(window, 0);
            if(clickOnButton(window->white, event->button.x, event->button.y))
                changeChoiceColorWindow(window, 1);

            break;
        default:
            return COLOR_NONE;

    }
    return COLOR_NONE;
}

void changeChoiceColorWindow(ColorWindow* window, int i)
{
    if(i<0 || i>1)
        return;

    window->black->state.choosen = BUTTON_UNCHOSEN;
    window->white->state.choosen = BUTTON_UNCHOSEN;
    switch(i)
    {
        case 0:
            window->black->state.choosen = BUTTON_CHOSEN;
            break;
        case 1:
            window->white->state.choosen = BUTTON_CHOSEN;
            break;
        default:
            printf("BUG!!!");
            window->black->state.choosen = BUTTON_CHOSEN;
    }
    window->configurationChosen = i;
}