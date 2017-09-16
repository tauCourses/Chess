#include "GameWindow.h"
#include "GameManager.h"
#include "GameState.h"
#include "Button.h"

GameWindow* createGameWindow(SDL_Renderer* renderer, GameManager* game)
{
    GameWindow *window = NULL;
    if(game == NULL)
        return NULL;
    if (renderer == NULL)
        return NULL;

    window = calloc(sizeof(GameWindow), sizeof(char));
    if (window == NULL)
        return NULL;

    window->renderer = renderer;
    window->game = game;

    createGameButtons(window);
    if (window->restart == NULL || window->save == NULL || window->load == NULL || window->undo == NULL ||
        window->main == NULL || window->exit == NULL)
    {
        destroyGameWindow(window);
        return NULL;
    }

    SDL_Point startBoardPoint = {.x=300,.y=40};
    window->board = createGameLayout(startBoardPoint, window->renderer);
    if(window->board == NULL)
    {
        destroyGameWindow(window);
        return NULL;
    }
    window->isSaved = true;
    return window;
}

void createGameButtons(GameWindow* window)
{
    if(window == NULL || window->renderer == NULL)
        return;

    //buttons locations and sizes
    SDL_Rect restartR = { .x = 50, .y = 80, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect saveR = { .x = 50, .y = 150, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect loadR = { .x = 50, .y = 220, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect undoR = { .x = 50, .y = 290, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };

    SDL_Rect mainR = { .x = 50, .y = 450, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };
    SDL_Rect exitR = { .x = 50, .y = 520, .h = BUTTON_DEFAULT_HEIGHT, .w = BUTTON_DEFAULT_WIDTH };


    //setup buttons:
    window->restart = createButton(window->renderer, restartR, RESTART_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
    window->save = createButton(window->renderer, saveR, SAVE_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
    window->load = createButton(window->renderer, loadR, LOAD_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
    window->undo = createButton(window->renderer, undoR, UNDO_ACTIVE_BUTTON, UNDO_NOT_ACTIVE_BUTTON, BUTTON_TYPE_VALIDATE);
    if(!candoundo(window->game))
        window->undo->state.valid = BUTTON_INVALID;

    window->main = createButton(window->renderer, mainR, MAIN_MANU_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
    window->exit = createButton(window->renderer, exitR, EXIT_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
}

void destroyGameWindow(GameWindow *window)
{
    printf("destory game window\n");
    if (window == NULL)
        return;
    //buttons:
    if(window->restart != NULL)
        destroyButton(window->restart);
    if(window->save != NULL)
        destroyButton(window->save);
    if(window->load != NULL)
        destroyButton(window->load);
    if(window->undo != NULL)
        destroyButton(window->undo);

    if(window->main != NULL)
        destroyButton(window->main);
    if(window->exit != NULL)
        destroyButton(window->exit);

    if(window->board != NULL)
        destroyGameLayout(window->board);

    if(window->game != NULL)
        destroyGame(window->game);

    free(window);
}

void drawGameWindow(GameWindow *window)
{
    if(window==NULL)
        return;

    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_RenderClear(window->renderer);

    drawButton(window->restart);
    drawButton(window->save);
    drawButton(window->load);
    drawButton(window->undo);

    drawButton(window->main);
    drawButton(window->exit);

    drawGameLayout(window->board, window->game->state->board);
}


GAME_WINDOW_EVENTS handleMouseUpGameWindow(GameWindow *window, SDL_Event *event)
{
    if(isPointOnGameLayout(window->board,event->button.x, event->button.y))
    {
        if(window->board->draged != NULL)
        {
            Location square = getSquare(window->board, event->button.x, event->button.y);
            GAME_MOVE_MESSAGE message = movePiece(window->game, &window->board->draged->location, &square);
            destroyDragPiece(window->board);
            //check if pawn need to became something wlse //TODO
            if(message == MOVE_VALID)
            {
                window->isSaved = false;
                if(candoundo(window->game))
                    window->undo->state.valid = BUTTON_VALID;
                else
                    window->undo->state.valid = BUTTON_INVALID;

                GAME_STATE state =  getGameState(window->game);
                if(state == GAME_CHECKMATE)
                    gameEndMessageBox(oppositeColor(window->game->state->currentPlayer));
                else if(state == GAME_TIE)
                    gameEndMessageBox(NONE_PLAYER_COLOR);
                if(state != VALID_GAME_STATE)
                    return GAME_NONE;

                if(window->game->mode == ONE_PLAYER_GAME_MODE)
                    applyAIMove(window->game);
                state =  getGameState(window->game);
                if(state == GAME_CHECKMATE)
                    gameEndMessageBox(oppositeColor(window->game->state->currentPlayer));
            }

            return GAME_NONE;
        }
    }
    else if(window->board->draged != NULL)
    {
        destroyDragPiece(window->board);
        return GAME_NONE;
    }

    if(clickOnButton(window->restart, event->button.x, event->button.y))
    {
        GameManager *newGame;
        if(window->game->mode == TWO_PLAYERS_GAME_MODE)
            newGame = createTwoPlayersGame();
        else
            newGame = createOnePlayerGame(window->game->difficulty,window->game->userColor);

        if(newGame == NULL)
            return GAME_NONE; //TODO -> WHAT TO DO?
        if(newGame->mode == ONE_PLAYER_GAME_MODE &&newGame->userColor == BLACK_PLAYER)
            applyAIMove(newGame);
        destroyGame(window->game);
        window->game = newGame;

        return GAME_NONE;
    }
    else if(clickOnButton(window->save, event->button.x, event->button.y))
    {
        addGameToGameSlots(window->game);
        window->isSaved = true;
        return GAME_NONE;
    }
    else if(clickOnButton(window->load, event->button.x, event->button.y))
        return GAME_LOAD;
    else if(clickOnButton(window->undo, event->button.x, event->button.y))
    {
        if(candoundo(window->game))
        {
            undoMove(window->game);
            undoMove(window->game);
        }
        if(candoundo(window->game))
            window->undo->state.valid = BUTTON_VALID;
        else
            window->undo->state.valid = BUTTON_INVALID;
        return GAME_NONE;
    }
    else if(clickOnButton(window->main, event->button.x, event->button.y) &&
            (window->isSaved || exitConfirmationMessageBox() == 1))
        return GAME_MAIN;
    else if(clickOnButton(window->exit, event->button.x, event->button.y) &&
            (window->isSaved || exitConfirmationMessageBox() == 1))
        return GAME_EXIT;

    return GAME_NONE;
}

GAME_WINDOW_EVENTS handleEventGameWindow(GameWindow *window, SDL_Event *event)
{
    if(window == NULL || event==NULL)
        return GAME_INVALID_ARGUMENT;

    switch (event->type)
    {
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE)
                return GAME_EXIT;
            break;
        case SDL_MOUSEBUTTONUP:
            return handleMouseUpGameWindow(window,event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(isPointOnGameLayout(window->board,event->button.x, event->button.y))
            {
                Location square = getSquare(window->board, event->button.x, event->button.y);
                if(window->game->state->board[square.x][square.y] != EMPTY_PLACE_SYMBOL)
                    setDragedPiece(window->board, square.x, square.y, window->game->state->board[square.x][square.y]);

            }
            return GAME_NONE;
            break;
        default:
            return GAME_NONE;

    }
    return GAME_NONE;
}

int exitConfirmationMessageBox()
{
    const SDL_MessageBoxButtonData buttons[] = {
            { /* .flags, .buttonid, .text */        0, 0, "no" },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                    { 255,   255,   255 }, /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    {   0, 0,   0 }, /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    { 255, 0,   0 }, /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    {   0,   0, 255 }, /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    { 255,   0, 255 } /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            }
    };
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            NULL, /* .window */
            "Exit warning", /* .title */
            "Are you sure you want to exit without saving?", /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        return -1;

    }
    printf("buttonid - %d\n", buttonid);
    return buttonid;
}

int gameEndMessageBox(PLAYER_COLOR winner)
{
    const SDL_MessageBoxButtonData buttons[] = {
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "OK" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
            { /* .colors (.r, .g, .b) */
                    { 255,   255,   255 }, /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    {   0, 0,   0 }, /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    { 255, 0,   0 }, /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    {   0,   0, 255 }, /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    { 255,   0, 255 } /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            }
    };
    char* victoryMessage;
    if(winner == WHITE_PLAYER)
        victoryMessage = "White wins!";
    else if(winner == BLACK_PLAYER)
        victoryMessage = "Black wins!";
    else
        victoryMessage = "Tie";

    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            NULL, /* .window */
            "Game End", /* .title */
            victoryMessage, /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        return -1;

    }
    printf("buttonid - %d\n", buttonid);
    return buttonid;
}