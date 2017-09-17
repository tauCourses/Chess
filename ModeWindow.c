#include "ModeWindow.h"
#include "Button.h"

ModeWindow* createModeWindow(SDL_Renderer* renderer)
{
    ModeWindow *window = NULL;

    window = calloc(sizeof(ModeWindow), sizeof(char));
    if (window == NULL)
        return NULL;

    window->renderer = renderer;

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
    SDL_Rect titleR = { .x = 365, .y = 50, .h = 70, .w = 270 };
    SDL_Rect oneR = { .x = 250, .y = 250, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect twoR = { .x = 550, .y = 250, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect progressR = { .x = 250, .y = 600, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect backR = { .x = 550, .y = 600, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };

    //SETUP BUTTONS:
    window->title = createButton(window->renderer, titleR, SELECT_MODE_TITLE, "", BUTTON_TYPE_DEGENERATED);
    window->onePlayer = createButton(window->renderer, oneR, ONE_PLAYER_ACTIVE_BUTTON, ONE_PLAYER_NOT_ACTIVE_BUTTON, BUTTON_TYPE_CHOICE);
    window->twoPlayers = createButton(window->renderer, twoR, TWO_PLAYERS_ACTIVE_BUTTON, TWO_PLAYERS_NOT_ACTIVE_BUTTON, BUTTON_TYPE_CHOICE);
    window->progress = createButton(window->renderer, progressR, NEXT_ACTIVE_BUTTON, START_ACTIVE_BUTTON, BUTTON_TYPE_TWO_OPTIONS);
    window->back = createButton(window->renderer, backR, BACK_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
}

void destroyModeWindow(ModeWindow *window)
{
    if (window == NULL)
        return;
    //buttons:
    if(window->title != NULL)
        destroyButton(window->title);
    if(window->onePlayer != NULL)
        destroyButton(window->onePlayer);
    if(window->twoPlayers != NULL)
        destroyButton(window->twoPlayers);
    if(window->progress != NULL)
        destroyButton(window->progress);
    if(window->back != NULL)
        destroyButton(window->back);

    free(window);
}

bool drawModeWindow(ModeWindow *window) {
    if (window == NULL)
        return false;

    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_RenderClear(window->renderer);

    drawButton(window->title);
    drawButton(window->onePlayer);
    drawButton(window->twoPlayers);
    drawButton(window->progress);
    drawButton(window->back);
    return true;
}

MODE_WINDOW_EVENTS handleEventModeWindow(ModeWindow *window, SDL_Event *event)
{
    if(window == NULL || event==NULL)
        return MODE_ERROR;

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
                    return MODE_NEXT  ;
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
        window->progress->state.option = BUTTON_FIRST_OPTION ;
        window->configurationChosen = 0;
    }
    if(i==1)
    {
        window->onePlayer->state.choosen = BUTTON_UNCHOSEN;
        window->twoPlayers->state.choosen = BUTTON_CHOSEN;
        window->progress->state.option = BUTTON_SECOND_OPTION;
        window->configurationChosen = 1;
    }
}