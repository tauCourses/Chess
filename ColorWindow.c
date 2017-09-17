#include "ColorWindow.h"
#include "Button.h"

ColorWindow* createColorWindow(SDL_Renderer* renderer)
{
    ColorWindow *window = NULL;

    window = calloc(sizeof(ColorWindow), sizeof(char));
    if (window == NULL)
        return NULL;

    window->renderer = renderer;

    createColorButtons(window);
    if (window->title == NULL || window->back == NULL || window->colorSwitch == NULL || window->start == NULL)
    {
        destroyColorWindow(window);
        return NULL;
    }

    return window;
}

void createColorButtons(ColorWindow* window)
{
    if(window == NULL || window->renderer == NULL)
        return;

    //BUTTONS LOCATIONS
    SDL_Rect titleR = { .x = 365, .y = 50, .h = 70, .w = 270 };
    SDL_Rect colorSwitchR = { .x = 400, .y = 200, .h = 200, .w = 200 };
    SDL_Rect startR = { .x = 250, .y = 500, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect backR = { .x = 550, .y = 500, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };

    //SETUP BUTTONS:
    window->title = createButton(window->renderer, titleR, SELECT_COLOR_TITLE, "", BUTTON_TYPE_DEGENERATED);

    window->colorSwitch = createButton(window->renderer, colorSwitchR,
                                       SELECT_COLOR_BLACK_BUTTON, SELECT_COLOR_WHITE_BUTTON, BUTTON_TYPE_TWO_OPTIONS);

    window->start = createButton(window->renderer, startR, START_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
    window->back = createButton(window->renderer, backR, BACK_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
}

void destroyColorWindow(ColorWindow *window)
{
    if (window == NULL)
        return;
    //buttons:
    if(window->title != NULL)
        destroyButton(window->title);

    if(window->colorSwitch != NULL)
        destroyButton(window->colorSwitch);

    if(window->start != NULL)
        destroyButton(window->start);
    if(window->back != NULL)
        destroyButton(window->back);

    free(window);
}

bool drawColorWindow(ColorWindow *window)
{
    if (window == NULL)
        return false;

    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_RenderClear(window->renderer);

    drawButton(window->title);

    drawButton(window->colorSwitch);

    drawButton(window->start);
    drawButton(window->back);

    return true;
}

COLOR_WINDOW_EVENTS handleEventColorWindow(ColorWindow *window, SDL_Event *event)
{
    if(window == NULL || event==NULL)
        return COLOR_ERROR;

    switch (event->type)
    {
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE)
                return COLOR_EXIT;
            break;
        case SDL_MOUSEBUTTONUP:
            if(clickOnButton(window->back, event->button.x, event->button.y))
                return COLOR_BACK;
            else if(clickOnButton(window->start, event->button.x, event->button.y))
                return COLOR_START;
            else if(clickOnButton(window->colorSwitch, event->button.x, event->button.y))
                window->colorSwitch->state.option = (window->colorSwitch->state.option == BUTTON_FIRST_OPTION) ?
                                                    BUTTON_SECOND_OPTION : BUTTON_FIRST_OPTION;

            break;
        default:
            return COLOR_NONE;

    }
    return COLOR_NONE;
}

PLAYER_COLOR getColorFromColorWindow(ColorWindow *window)
{
    if(window->colorSwitch->state.option == BUTTON_FIRST_OPTION)
        return BLACK_PLAYER;
    return WHITE_PLAYER;
}