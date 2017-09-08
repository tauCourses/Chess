#include "DifficultyWindow.h"

DifficultyWindow* createDifficultyWindow() {
    DifficultyWindow *window = NULL;

    window = calloc(sizeof(DifficultyWindow), sizeof(char));
    if (window == NULL)
        return NULL;

    window->window = SDL_CreateWindow("SP Chess - Choose mode", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_OPENGL);

    if (window->window == NULL) {
        destroyDifficultyWindow(window);
        return NULL;
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (window->renderer == NULL) {
        destroyDifficultyWindow(window);
        return NULL;
    }

    createDifficultyButtons(window);
    if (window->title == NULL || window->back == NULL || window->next == NULL || window->noob == NULL ||
        window->easy == NULL || window->moderate == NULL || window->hard == NULL || window->expert == NULL)
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
    SDL_Rect titleR = { .x = 350, .y = 50, .h = 50, .w = 300 };
    SDL_Rect noobR = { .x = 450, .y = 100, .h = 50, .w = 250 };
    SDL_Rect easyR = { .x = 450, .y = 170, .h = 50, .w = 250 };
    SDL_Rect moderateR = { .x = 450, .y = 240, .h = 50, .w = 250 };
    SDL_Rect hardR = { .x = 450, .y = 310, .h = 50, .w = 250 };
    SDL_Rect expertR = { .x = 450, .y = 380, .h = 50, .w = 250 };
    SDL_Rect nextR = { .x = 200, .y = 900, .h = 100, .w = 250 };
    SDL_Rect backR = { .x = 550, .y = 900, .h = 100, .w = 250 };

    //SETUP BUTTONS:
    window->title = createButton(window->renderer, titleR, "newGame.bmp", "", BUTTON_TYPE_DEGENERATED);

    window->noob = createButton(window->renderer, noobR, "start.bmp", "exit.bmp", BUTTON_TYPE_CHOICE);
    window->easy = createButton(window->renderer, easyR, "start.bmp", "exit.bmp", BUTTON_TYPE_CHOICE);
    window->moderate = createButton(window->renderer, moderateR, "start.bmp", "exit.bmp", BUTTON_TYPE_CHOICE);
    window->hard = createButton(window->renderer, hardR, "start.bmp", "exit.bmp", BUTTON_TYPE_CHOICE);
    window->expert = createButton(window->renderer, expertR, "start.bmp", "exit.bmp", BUTTON_TYPE_CHOICE);

    window->next = createButton(window->renderer, nextR, "start.bmp", "exit.bmp", BUTTON_TYPE_ONE_OPTION);
    window->back = createButton(window->renderer, backR, "back.bmp", "", BUTTON_TYPE_ONE_OPTION);
}

void destroyDifficultyWindow(DifficultyWindow *window)
{
    if (window == NULL)
        return;
    //buttons:
    destroyButton(window->title);

    destroyButton(window->noob);
    destroyButton(window->easy);
    destroyButton(window->moderate);
    destroyButton(window->hard);
    destroyButton(window->expert);

    destroyButton(window->next);
    destroyButton(window->back);

    //renderer destroy:
    if (window->renderer != NULL )
        SDL_DestroyRenderer(window->renderer);
    //window destroy:
    if (window->window != NULL)
        SDL_DestroyWindow(window->window);

    free(window);
}

void drawDifficultyWindow(DifficultyWindow *window)
{
    if(window==NULL)
        return;


    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_RenderClear(window->renderer);

    drawButton(window->title);

    drawButton(window->noob);
    drawButton(window->easy);
    drawButton(window->moderate);
    drawButton(window->hard);
    drawButton(window->expert);

    drawButton(window->next);
    drawButton(window->back);

    SDL_RenderPresent(window->renderer);
}

void hideDifficultyWindow(DifficultyWindow* window)
{
    SDL_HideWindow(window->window);
}

void showDifficultyWindow(DifficultyWindow* window)
{
    SDL_ShowWindow(window->window);
}

DIFFICULTY_WINDOW_EVENTS handleEventDifficultyWindow(DifficultyWindow *window, SDL_Event *event)
{
    if(window == NULL || event==NULL)
        return DIFFICULTY_INVALID_ARGUMENT;

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
            if(clickOnButton(window->expert, event->button.x, event->button.y))
                changeChoiceDifficultyWindow(window, 4);
            break;
        default:
            return DIFFICULTY_NONE;

    }
    return DIFFICULTY_NONE;
}

void changeChoiceDifficultyWindow(DifficultyWindow* window, int i)
{
    if(i<0 || i>4)
        return;

    window->noob->state.choosen = BUTTON_UNCHOSEN;
    window->easy->state.choosen = BUTTON_UNCHOSEN;
    window->moderate->state.choosen = BUTTON_UNCHOSEN;
    window->hard->state.choosen = BUTTON_UNCHOSEN;
    window->expert->state.choosen = BUTTON_UNCHOSEN;
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
        case 4:
            window->expert->state.choosen = BUTTON_CHOSEN;
            break;
        default:
            printf("BUG!!!");
            window->easy->state.choosen = BUTTON_CHOSEN;
    }
    window->configurationChosen = i;
}