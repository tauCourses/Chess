#include "LoadGameWindow.h"

LoadWindow* createLoadWindow() {
    LoadWindow *window = NULL;

    window = calloc(sizeof(LoadWindow), sizeof(char));
    if (window == NULL)
        return NULL;

    window->window = SDL_CreateWindow("SP Chess - load", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_OPENGL);

    if (window->window == NULL) {
        destroyLoadWindow(window);
        return NULL;
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (window->renderer == NULL) {
        destroyLoadWindow(window);
        return NULL;
    }

    window->numOfSlots = 3; // TODO - should get from chess infra!!! don't leave me like that!
    createLoadButtons(window);
    if (window->back == NULL || window->load == NULL)
    {
        destroyLoadWindow(window);
        return NULL;
    }
    for (int i = 0; i < window->numOfSlots; i++)
    {
        if (window->slots[i] == NULL)
        {
            destroyLoadWindow(window);
            return NULL;
        }
    }

    window->slotChosed = -1;
    return window;
}

void createLoadButtons(LoadWindow* window)
{
    if(window == NULL || window->renderer == NULL)
        return;

    SDL_Rect backR = { .x = 300, .y = 900, .h = 100, .w = 250 };
    SDL_Rect loadR = { .x = 600, .y = 900, .h = 100, .w = 250 };
    SDL_Rect slotR = { .x = 450, .y = 50, .h = 100, .w = 250 };
    window->back = createButton(window->renderer, backR, "back.bmp", "", BUTTON_TYPE_ONE_OPTION);
    window->load = createButton(window->renderer, loadR, "load.bmp", "load.bmp", BUTTON_TYPE_VALIDATE);
    if(window->load != NULL)
        window->load->state.valid = BUTTON_INVALID;
    for (int i = 0; i < window->numOfSlots; i++)
    {
        window->slots[i] = createButton(window->renderer, slotR, "exit.bmp", "start.bmp", BUTTON_TYPE_CHOICE);
        slotR.y += 120;
    }
}

void destroyLoadWindow(LoadWindow *window)
{
    if (window == NULL)
        return;
    //buttons:
    destroyButton(window->back);
    destroyButton(window->load);
    for (int i = 0; i < window->numOfSlots; i++)
        destroyButton(window->slots[i]);
    //renderer destroy:
    if (window->renderer != NULL )
        SDL_DestroyRenderer(window->renderer);
    //window destroy:
    if (window->window != NULL)
        SDL_DestroyWindow(window->window);

    free(window);
}

void drawLoadWindow(LoadWindow *window)
{
    if(window==NULL)
        return;


    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_RenderClear(window->renderer);

    drawButton(window->back);
    drawButton(window->load);
    for (int i = 0; i < window->numOfSlots; i++)
        drawButton(window->slots[i]);

    SDL_RenderPresent(window->renderer);
}

void hideLoadWindow(LoadWindow* window)
{
    SDL_HideWindow(window->window);
}

void showLoadWindow(LoadWindow* window)
{
    SDL_ShowWindow(window->window);
}

LOAD_WINDOW_EVENTS handleEventLoadWindow(LoadWindow *window, SDL_Event *event)
{
    if(window == NULL || event==NULL)
        return LOAD_INVALID_ARGUMENT;

    switch (event->type)
    {
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE)
                return LOAD_EXIT;
            break;
        case SDL_MOUSEBUTTONUP:
            if(clickOnButton(window->back, event->button.x, event->button.y))
                return LOAD_BACK;

            if(clickOnButton(window->load, event->button.x, event->button.y))
            {
                if(window->slotChosed != -1)
                    return LOAD_CONITNUE;
                return LOAD_NONE;
            }
            for (int i = 0; i < window->numOfSlots; i++)
            {
                if (clickOnButton(window->slots[i], event->button.x, event->button.y))
                {
                    if (i != window->slotChosed)
                        changeChoiceLoadWindow(window, i);
                    return LOAD_NONE;
                }
            }
            break;
        default:
            return LOAD_NONE;

    }
    return LOAD_NONE;
}

void changeChoiceLoadWindow(LoadWindow* window, int i)
{
    if(window->slotChosed == -1) //first choice, make load button valid.
        window->load->state.valid = BUTTON_VALID;
    else
        window->slots[window->slotChosed]->state.choosen = BUTTON_UNCHOSEN;
    window->slots[i]->state.choosen = BUTTON_CHOSEN;
    window->slotChosed = i;
}