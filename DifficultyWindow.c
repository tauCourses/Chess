#include "DifficultyWindow.h"

DifficultyWindow* createDifficultyWindow(SDL_Renderer* renderer)
{
    DifficultyWindow *window = NULL;

    window = calloc(sizeof(DifficultyWindow), sizeof(char));
    if (window == NULL)
        return NULL;

    window->renderer = renderer;

    createDifficultyButtons(window);
    if (window->title == NULL || window->back == NULL || window->next == NULL || window->noob == NULL ||
        window->easy == NULL || window->moderate == NULL || window->hard == NULL)
    {
        destroyDifficultyWindow(window);
        return NULL;
    }

    changeChoiceDifficultyWindow(window, 0);

    return window;
}

void createDifficultyButtons(DifficultyWindow* window)
{
    if(window == NULL || window->renderer == NULL)
        return;

    //BUTTONS LOCATIONS
    SDL_Rect titleR = { .x = 365, .y = 50, .h = 70, .w = 270 };
    SDL_Rect noobR = { .x = 400, .y = 130, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect easyR = { .x = 400, .y = 200, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect moderateR = { .x = 400, .y = 270, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect hardR = { .x = 400, .y = 340, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect expertR = { .x = 400, .y = 410, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect nextR = { .x = 250, .y = 600, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect backR = { .x = 550, .y = 600, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };

    //SETUP BUTTONS:
    window->title = createButton(window->renderer, titleR, SELECT_DIFFICULTY_TITLE, "", BUTTON_TYPE_DEGENERATED);

    window->noob = createButton(window->renderer, noobR, NOOB_ACTIVE_BUTTON, NOOB_NOT_ACTIVE_BUTTON, BUTTON_TYPE_CHOICE);
    window->easy = createButton(window->renderer, easyR, EASY_ACTIVE_BUTTON, EASY_NOT_ACTIVE_BUTTON, BUTTON_TYPE_CHOICE);
    window->moderate = createButton(window->renderer, moderateR, MODERATE_ACTIVE_BUTTON, MODERATE_NOT_ACTIVE_BUTTON, BUTTON_TYPE_CHOICE);
    window->hard = createButton(window->renderer, hardR, HARD_ACTIVE_BUTTON, HARD_NOT_ACTIVE_BUTTON, BUTTON_TYPE_CHOICE);

    window->next = createButton(window->renderer, nextR, NEXT_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
    window->back = createButton(window->renderer, backR, BACK_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
}

void destroyDifficultyWindow(DifficultyWindow *window)
{
    if (window == NULL)
        return;
    //buttons:
    if(window->title != NULL)
        destroyButton(window->title);
    if(window->noob != NULL)
        destroyButton(window->noob);
    if(window->easy != NULL)
        destroyButton(window->easy);
    if(window->moderate != NULL)
        destroyButton(window->moderate);
    if(window->hard != NULL)
        destroyButton(window->hard);

    if(window->next != NULL)
        destroyButton(window->next);
    if(window->back != NULL)
        destroyButton(window->back);


    free(window);
}

bool drawDifficultyWindow(DifficultyWindow *window)
{
    if(window==NULL)
        return false;


    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_RenderClear(window->renderer);

    drawButton(window->title);

    drawButton(window->noob);
    drawButton(window->easy);
    drawButton(window->moderate);
    drawButton(window->hard);

    drawButton(window->next);
    drawButton(window->back);

    return true;
}

DIFFICULTY_WINDOW_EVENTS handleEventDifficultyWindow(DifficultyWindow *window, SDL_Event *event)
{
    if(window == NULL || event==NULL)
        return DIFFICULTY_ERROR;

    switch (event->type)
    {
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE)
                return DIFFICULTY_EXIT;
            break;
        case SDL_MOUSEBUTTONUP:
            if(clickOnButton(window->back, event->button.x, event->button.y))
                return DIFFICULTY_BACK;
            if(clickOnButton(window->next, event->button.x, event->button.y))
                return DIFFICULTY_NEXT;
            if(clickOnButton(window->noob, event->button.x, event->button.y))
                changeChoiceDifficultyWindow(window, 0);
            if(clickOnButton(window->easy, event->button.x, event->button.y))
                changeChoiceDifficultyWindow(window, 1);
            if(clickOnButton(window->moderate, event->button.x, event->button.y))
                changeChoiceDifficultyWindow(window, 2);
            if(clickOnButton(window->hard, event->button.x, event->button.y))
                changeChoiceDifficultyWindow(window, 3);
            break;
        default:
            return DIFFICULTY_NONE;

    }
    return DIFFICULTY_NONE;
}

void changeChoiceDifficultyWindow(DifficultyWindow* window, int i)
{
    if(i<0 || i>3)
        return;

    window->noob->state.choosen = BUTTON_UNCHOSEN;
    window->easy->state.choosen = BUTTON_UNCHOSEN;
    window->moderate->state.choosen = BUTTON_UNCHOSEN;
    window->hard->state.choosen = BUTTON_UNCHOSEN;
    switch(i)
    {
        case 0:
            window->noob->state.choosen = BUTTON_CHOSEN;
            break;
        case 1:
            window->easy->state.choosen = BUTTON_CHOSEN;
            break;
        case 2:
            window->moderate->state.choosen = BUTTON_CHOSEN;
            break;
        case 3:
            window->hard->state.choosen = BUTTON_CHOSEN;
            break;
        default:
            printf("BUG!!!1");
            window->easy->state.choosen = BUTTON_CHOSEN;
    }
    window->configurationChosen = i;
}