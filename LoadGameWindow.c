#include "LoadGameWindow.h"

LoadWindow* createLoadWindow(SDL_Renderer* renderer)
{
    LoadWindow *window = NULL;

    window = calloc(sizeof(LoadWindow), sizeof(char));
    if (window == NULL)
        return NULL;

    window->renderer = renderer;

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

    SDL_Rect backR = { .x = 250, .y = 650, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect loadR = { .x = 550, .y = 650, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect slotR = { .x = 400, .y = 50, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    window->back = createButton(window->renderer, backR, BACK_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
    window->load = createButton(window->renderer, loadR, LOAD_ACTIVE_BUTTON, LOAD_NOT_ACTIVE_BUTTON, BUTTON_TYPE_VALIDATE);
    if(window->load != NULL)
        window->load->state.valid = BUTTON_INVALID;
    for (int i = 0; i < window->numOfSlots; i++)
    {
        switch(i)
        {
            case 0:
                window->slots[i] = createButton(window->renderer, slotR, GAME_SLOT_1_ACTIVE_BUTTON, GAME_SLOT_1_NOT_ACTIVE_BUTTON, BUTTON_TYPE_CHOICE);
                break;
            case 1:
                window->slots[i] = createButton(window->renderer, slotR, GAME_SLOT_2_ACTIVE_BUTTON, GAME_SLOT_2_NOT_ACTIVE_BUTTON, BUTTON_TYPE_CHOICE);
                break;
            case 2:
                window->slots[i] = createButton(window->renderer, slotR, GAME_SLOT_3_ACTIVE_BUTTON, GAME_SLOT_3_NOT_ACTIVE_BUTTON, BUTTON_TYPE_CHOICE);
                break;
            case 3:
                window->slots[i] = createButton(window->renderer, slotR, GAME_SLOT_4_ACTIVE_BUTTON, GAME_SLOT_4_NOT_ACTIVE_BUTTON, BUTTON_TYPE_CHOICE);
                break;
            case 4:
                window->slots[i] = createButton(window->renderer, slotR, GAME_SLOT_5_ACTIVE_BUTTON, GAME_SLOT_5_NOT_ACTIVE_BUTTON, BUTTON_TYPE_CHOICE);
                break;
            default:
                printf("not supported more than 5 slots"); //TODO - > BUG!
        }
        slotR.y += 90;
    }
}

void destroyLoadWindow(LoadWindow *window)
{
    if (window == NULL)
        return;
    //buttons:
    if(window->back!= NULL)
        destroyButton(window->back);
    if(window->load!= NULL)
        destroyButton(window->load);
    for (int i = 0; i < window->numOfSlots; i++)
        if(window->slots[i] != NULL)
            destroyButton(window->slots[i]);

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
                    return LOAD_START;
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