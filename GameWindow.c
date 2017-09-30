#include "GameWindow.h"
#include "GameManager.h"
#include "GameState.h"
#include "Button.h"
#include "Location.h"
#include "GameLayout.h"

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
    if(window->undo != NULL && candoundo(window->game) != UNDO_POSSIBLE)
        window->undo->state.valid = BUTTON_INVALID;

    window->main = createButton(window->renderer, mainR, MAIN_MANU_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
    window->exit = createButton(window->renderer, exitR, EXIT_ACTIVE_BUTTON, "", BUTTON_TYPE_ONE_OPTION);
}

void destroyGameWindow(GameWindow *window)
{
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

bool drawGameWindow(GameWindow *window)
{
    if(window==NULL)
        return false;

    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
    SDL_RenderClear(window->renderer);

    drawButton(window->restart);
    drawButton(window->save);
    drawButton(window->load);
    drawButton(window->undo);

    drawButton(window->main);
    drawButton(window->exit);

    return drawGameLayout(window->board, window->game->state);
}

void updateUndoButton(GameWindow *window)
{
    if(candoundo(window->game) == UNDO_POSSIBLE)
        window->undo->state.valid = BUTTON_VALID;
    else
        window->undo->state.valid = BUTTON_INVALID;
}

GAME_WINDOW_EVENTS handleLeftMouseUpGameLayout(GameWindow *window, SDL_Event *event)
{
    if(window->board->draged != NULL)
    {
        Location square = getSquare(window->board, event->button.x, event->button.y);
        GAME_MOVE_MESSAGE message = movePiece(window->game, &window->board->draged->location, &square);
        if(message == MOVE_ERROR)
            return GAME_WINDOW_ERROR;
        destroyDragPiece(window->board);

        if(message == MOVE_VALID || message == MOVE_PAWN_REACH_END)
        {
            if(message == MOVE_PAWN_REACH_END)
            {
                char newPiece = gamePawnPromotionMessageBox(oppositeColor(window->game->state->currentPlayer));
                window->game->state->board[square.x][square.y] = newPiece;
            }
            window->isSaved = false;
            updateUndoButton(window);

            GAME_STATE state =  getGameState(window->game);
            if(state == GAME_CHECKMATE)
                gameEndMessageBox(oppositeColor(window->game->state->currentPlayer));
            else if(state == GAME_TIE)
                gameEndMessageBox(NONE_PLAYER_COLOR);
            else if(state == GAME_ERROR)
                return GAME_WINDOW_ERROR;
            if(state != VALID_GAME_STATE)
                return GAME_NONE;

            if(window->game->mode == ONE_PLAYER_GAME_MODE)
            {
                GameMove* move = applyAIMove(window->game);
                if(move == NULL)
                {
                    printf("ERROR: in perform AI move\n");
                    return GAME_WINDOW_ERROR;
                }
            }
            state =  getGameState(window->game);
            if(state == GAME_CHECKMATE)
                gameEndMessageBox(oppositeColor(window->game->state->currentPlayer));
            else if(state == GAME_TIE)
                gameEndMessageBox(NONE_PLAYER_COLOR);
            else if(state == GAME_ERROR)
                return GAME_WINDOW_ERROR;
            updateUndoButton(window);
        }
    }
    return GAME_NONE;
}

GAME_WINDOW_EVENTS handleLeftMouseUpRestart(GameWindow *window)
{
    GameManager *newGame;
    if(window->game->mode == TWO_PLAYERS_GAME_MODE)
        newGame = createTwoPlayersGame();
    else
        newGame = createOnePlayerGame(window->game->difficulty,window->game->userColor);

    if(newGame == NULL)
    {
        printf("ERROR: Failed to create a new restarted game!\n");
        return GAME_WINDOW_ERROR;
    }
    if(newGame->mode == ONE_PLAYER_GAME_MODE &&newGame->userColor == BLACK_PLAYER)
    {
        GameMove* move = applyAIMove(newGame);
        if(move == NULL)
        {
            printf("ERROR: Failed to perform an AI move\n");
            return GAME_WINDOW_ERROR;
        }
    }
    destroyGame(window->game);
    window->game = newGame;

    return GAME_NONE;
}

GAME_WINDOW_EVENTS handleLeftMouseUpUndo(GameWindow *window)
{
    if(candoundo(window->game) == UNDO_POSSIBLE)
    {
        undoMove(window->game);
        undoMove(window->game);
    }
    updateUndoButton(window);
    return GAME_NONE;
}

GAME_WINDOW_EVENTS handleLeftMouseUpGameWindow(GameWindow *window, SDL_Event *event)
{
    if(isPointOnGameLayout(window->board,event->button.x, event->button.y))
        return handleLeftMouseUpGameLayout(window, event);
    else if(window->board->draged != NULL)
    {
        destroyDragPiece(window->board);
        return GAME_NONE;
    }

    if(clickOnButton(window->restart, event->button.x, event->button.y))
        return handleLeftMouseUpRestart(window);
    else if(clickOnButton(window->save, event->button.x, event->button.y))
    {
        addGameToGameSlots(window->game);
        window->isSaved = true;
        return GAME_NONE;
    }
    else if(clickOnButton(window->load, event->button.x, event->button.y))
        return GAME_LOAD;
    else if(clickOnButton(window->undo, event->button.x, event->button.y))
        return handleLeftMouseUpUndo(window);
    else if(clickOnButton(window->main, event->button.x, event->button.y) &&
            (window->isSaved || exitConfirmationMessageBox() == 1))
        return GAME_MAIN;
    else if(clickOnButton(window->exit, event->button.x, event->button.y) &&
            (window->isSaved || exitConfirmationMessageBox() == 1))
        return GAME_EXIT;

    return GAME_NONE;
}

GAME_WINDOW_EVENTS  handleLeftMouseDownGameWindow(GameWindow *window, SDL_Event *event)
{
    if(isPointOnGameLayout(window->board,event->button.x, event->button.y))
    {
        Location square = getSquare(window->board, event->button.x, event->button.y);
        if(window->game->state->board[square.x][square.y] != EMPTY_PLACE_SYMBOL)
        {
            char piece = window->game->state->board[square.x][square.y];
            if(setDragedPiece(window->board, square, piece) == false)
            {
                printf("ERROR: Failed to drag the piece\n");
                return GAME_WINDOW_ERROR;
            }
        }
    }
    return GAME_NONE;
}

GAME_WINDOW_EVENTS  handleRightMouseUpGameWindow(GameWindow *window, SDL_Event *event)
{
    if(window->board->suggestMoves != NULL)
    {
        destroyLocation(window->board->suggestMoves);
        window->board->suggestMoves = NULL;
    }
    return GAME_NONE;
}
GAME_WINDOW_EVENTS  handleRightMouseDownGameWindow(GameWindow *window, SDL_Event *event)
{
    if(window->board->draged != NULL)
        return GAME_NONE;
    if(!isPointOnGameLayout(window->board,event->button.x, event->button.y))
        return GAME_NONE;
    if(window->game->mode != ONE_PLAYER_GAME_MODE || window->game->difficulty > 2)
        return GAME_NONE;
    if(window->board->suggestMoves != NULL)
        return GAME_NONE;
    Location square = getSquare(window->board, event->button.x, event->button.y);
    window->board->suggestMoves = duplicateLocation(&square);
    if(window->board->suggestMoves == NULL)
    {
        printf("ERROR: Unable to create location for suggest piece\n");
        return GAME_WINDOW_ERROR;
    }
    return GAME_NONE;
}

GAME_WINDOW_EVENTS handleEventGameWindow(GameWindow *window, SDL_Event *event)
{
    if(window == NULL || event==NULL)
        return GAME_WINDOW_ERROR;

    switch (event->type)
    {
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE)
                return GAME_EXIT;
            break;
        case SDL_MOUSEBUTTONUP:
            if(event->button.button == SDL_BUTTON_LEFT)
                return handleLeftMouseUpGameWindow(window, event);
            else if(event->button.button == SDL_BUTTON_RIGHT)
                return handleRightMouseUpGameWindow(window, event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event->button.button == SDL_BUTTON_LEFT)
                return handleLeftMouseDownGameWindow(window, event);
            else if(event->button.button == SDL_BUTTON_RIGHT)
                return handleRightMouseDownGameWindow(window, event);
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
    return buttonid;
}

char gamePawnPromotionMessageBox(PLAYER_COLOR player)
{
    const SDL_MessageBoxButtonData buttons[] = {
            { /* .flags, .buttonid, .text */        0, 'm', "Pawn" },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 'n', "Knight" },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 'b', "Bishop" },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 'r', "Rook" },
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 'q', "Queen" },
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
            "Pawn promotion", /* .title */
            "Please select the piece that would replace the pawn", /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        return -1;

    }
    char result = (char)(player == WHITE_PLAYER ? buttonid : toUpper(buttonid));
    return result;
}
