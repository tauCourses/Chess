#include "ModeWindow.h"

ModeWindow* createModeWindow() {
    ModeWindow *window = NULL;

    window = calloc(sizeof(ModeWindow), sizeof(char));
    if (window == NULL)
        return NULL;

    window->window = SDL_CreateWindow("SP Chess - Choose mode", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_OPENGL);

    if (window->window == NULL) {
        destroyModeWindow(window);
        return NULL;
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (window->renderer == NULL) {
        destroyModeWindow(window);
        return NULL;
    }

    createModeButtons(window);
    if (window->title == NULL || window->back == NULL || window->progress == NULL ||
            window->onePlayer == NULL || window->twoPlayers == NULL)
    {
        destroyModeWindow(window);
        return NULL;
    }

    changeChoiceModeWindow(window, 0);
    return window;
}

void createModeButtons(ModeWindow* window)
{
    if(window == NULL || window->renderer == NULL)
        return;

    //BUTTONS LOCATIONS
    SDL_Rect titleR = { .x = 350, .y = 50, .h = 100, .w = 300 };
    SDL_Rect oneR = { .x = 200, .y = 250, .h = 100, .w = 250 };
    SDL_Rect twoR = { .x = 550, .y = 250, .h = 100, .w = 250 };
    SDL_Rect progressR = { .x = 200, .y = 900, .h = 100, .w = 250 };
    SDL_Rect backR = { .x = 550, .y = 900, .h = 100, .w = 250 };

    //SETUP BUTTONS:
    window->title = createButton(window->renderer, titleR, "newGame.bmp", "", BUTTON_TYPE_DEGENERATED);
    window->onePlayer = createButton(window->renderer, oneR, "start.bmp", "exit.bmp", BUTTON_TYPE_CHOICE);
    window->twoPlayers = createButton(window->renderer, twoR, "start.bmp", "exit.bmp", BUTTON_TYPE_CHOICE);
    window->progress = createButton(window->renderer, progressR, "start.bmp", "exit.bmp", BUTTON_TYPE_TWO_OPTIONS);
    window->back = createButton(window->renderer, backR, "back.bmp", "", BUTTON_TYPE_ONE_OPTION);
}

void destroyModeWindow(ModeWindow *window)
{
    if (window == NULL)
        return;
    //buttons:
    destroyButton(window->title);
    destroyButton(window->onePlayer);
    destroyButton(window->twoPlayers);
    destroyButton(window->progress);
    destroyButton(window->back);

    //renderer destroy:
    if (window->renderer != NULL )
        SDL_DestroyRenderer(window->renderer);
    //window destroy:
    if (window->window != NULL)
        SDL_DestroyWindow(window->window);

    free(window);
}

void drawModeWindow(ModeWindow *window)
{
    if(window==NULL)
        return;


    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_RenderClear(window->renderer);

    drawButton(window->title);
    drawButton(window->onePlayer);
    drawButton(window->twoPlayers);
    drawButton(window->progress);
    drawButton(window->back);

    SDL_RenderPresent(window->renderer);
}

void hideModeWindow(ModeWindow* window)
{
    SDL_HideWindow(window->window);
}

void showModeWindow(ModeWindow* window)
{
    SDL_ShowWindow(window->window);
}

MODE_WINDOW_EVENTS handleEventModeWindow(ModeWindow *window, SDL_Event *event)
{
    if(window == NULL || event==NULL)
        return MODE_INVALID_ARGUMENT;

    switch (event->type)
    {
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE)
                return MODE_EXIT;
            break;
        case SDL_MOUSEBUTTONUP:
            if(clickOnButton(window->back, event->button.x, event->button.y))
                return MODE_BACK;
            if(clickOnButton(window->progress, event->button.x, event->button.y))
            {
                if(window->configurationChosen == 0)
                    return MODE_NEXT;
                else
                   return MODE_START;
            }
            if(clickOnButton(window->onePlayer, event->button.x, event->button.y))
                changeChoiceModeWindow(window, 0);
            if(clickOnButton(window->twoPlayers, event->button.x, event->button.y))
                changeChoiceModeWindow(window, 1);
            break;
        default:
            return MODE_NONE;

    }
    return MODE_NONE;
}

void changeChoiceModeWindow(ModeWindow* window, int i)
{
    if(i==0)
    {
        window->onePlayer->state.choosen = BUTTON_CHOSEN;
        window->twoPlayers->state.choosen = BUTTON_UNCHOSEN;
        window->configurationChosen = 0;
    }
    if(i==1)
    {
        window->onePlayer->state.choosen = BUTTON_UNCHOSEN;
        window->twoPlayers->state.choosen = BUTTON_CHOSEN;
        window->configurationChosen = 1;
    }
}