#include "GameLayout.h"
#include "BoardLayout.h"
#include "Location.h"
#include "GameState.h"

GameLayout* createGameLayout(SDL_Point startingPoint, SDL_Renderer* renderer)
{

    GameLayout* game;
    if(renderer == NULL)
        return NULL;

    game =  (GameLayout*) malloc(sizeof(GameLayout));
    if(game == NULL)
        return NULL;

    game->boardLayout = createBoardLayout(startingPoint,CHESS_BOARD_SIZE,CHESS_BOARD_SIZE);
    if(game->boardLayout == NULL)
    {
        destroyGameLayout(game);
        return NULL;
    }
    game->renderer = renderer;
    game->black = createPieces(game->renderer,BLACK_PAWN_IMAGE, BLACK_ROOK_IMAGE, BLACK_BISHOP_IMAGE,
                               BLACK_KNIGHT_IMAGE, BLACK_QUEEN_IMAGE, BLACK_KING_IMAGE);
    if(game->black == NULL) {
        destroyGameLayout(game);
        return NULL;
    }

    game->white = createPieces(game->renderer,WHITE_PAWN_IMAGE, WHITE_ROOK_IMAGE, WHITE_BISHOP_IMAGE,
                               WHITE_KNIGHT_IMAGE, WHITE_QUEEN_IMAGE, WHITE_KING_IMAGE);
    if(game->white == NULL) {
        destroyGameLayout(game);
        return NULL;
    }
    game->draged = NULL;
    game->suggestMoves = NULL;
    return game;
}

SDL_Texture* setTexture(SDL_Renderer* renderer, char* image)
{
    SDL_Surface* loadingSurface = SDL_LoadBMP(image);
    if (loadingSurface == NULL ) {
        printf("unable to load %s\n", image);
        return NULL;
    }
    SDL_SetColorKey(loadingSurface, SDL_TRUE,
                    SDL_MapRGB(loadingSurface->format, PIECES_BACK_GROUND_COLOR));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
    return texture;
}

Pieces* createPieces(SDL_Renderer* renderer, char* pawn, char* rook, char* bishop, char* knight, char* queen, char* king)
{
    Pieces* pieces = (Pieces*) malloc(sizeof(Pieces));
    if(pieces == NULL)
        return NULL;

    pieces->pawn = setTexture(renderer, pawn);
    pieces->rook = setTexture(renderer, rook);
    pieces->bishop = setTexture(renderer, bishop);
    pieces->knight = setTexture(renderer, knight);
    pieces->queen = setTexture(renderer, queen);
    pieces->king = setTexture(renderer, king);

    if(pieces->pawn == NULL || pieces->rook == NULL || pieces->bishop == NULL ||
            pieces->knight == NULL || pieces->queen == NULL || pieces->king == NULL)
    {
        destroyPieces(pieces);
        return NULL;
    }
    return pieces;
}

void setDragedPiece(GameLayout* game, int x, int y, char c)
{
    DragedPiece* piece = (DragedPiece*) malloc(sizeof(DragedPiece));
    piece->location.x = x;
    piece->location.y = y;
    piece->texture = charToTexture(game, c);
    game->draged = piece;
}
void destroyDragPiece(GameLayout* game)
{
    if(game->draged != NULL) //do not free texture! it's still in use.
        free(game->draged);
    game->draged = NULL;
}

void destroyPieces(Pieces* pieces)
{
    if (pieces == NULL )
        return;

    if(pieces->pawn != NULL)
        SDL_DestroyTexture(pieces->pawn);

    if(pieces->rook != NULL)
        SDL_DestroyTexture(pieces->rook);

    if(pieces->bishop != NULL)
        SDL_DestroyTexture(pieces->bishop);

    if(pieces->knight != NULL)
        SDL_DestroyTexture(pieces->knight);

    if(pieces->queen != NULL)
        SDL_DestroyTexture(pieces->queen);

    if(pieces->king != NULL)
        SDL_DestroyTexture(pieces->king);

    free(pieces);
}


void destroyGameLayout(GameLayout* game)
{
    if (game == NULL)
        return;
    if (game->white != NULL)
        destroyPieces(game->white);

    if (game->black != NULL)
        destroyPieces(game->black);

    if(game->boardLayout != NULL)
        destroyBoardLayout(game->boardLayout);

    free(game);
}

void drawGameLayout(GameLayout* game, GameState* state)
{
    drawBoardLayout(game->renderer, game->boardLayout);
    if(game->suggestMoves != NULL)
        drawSuggestMoves(game, state);
    for(int i=0;i<CHESS_BOARD_SIZE;i++)
    {
        for(int j=0;j<CHESS_BOARD_SIZE;j++)
        {
            if(state->board[7-i][j] != EMPTY_PLACE_SYMBOL)
                drawSquare(game, j, i, state->board[7-i][j]);
        }
    }
    if(game->draged != NULL && game->draged->texture != NULL)
    {
        int x,y;
        SDL_GetMouseState(&x,&y);
        SDL_Rect ract = { x - SQUARE_SIZE/2, y - SQUARE_SIZE/2, .h=SQUARE_SIZE, .w=SQUARE_SIZE};
        SDL_RenderCopy(game->renderer, game->draged->texture, NULL, &ract);
    }
}

Location toLayoutLocation(Location* loc)
{
    return (Location) {.x = loc->y, .y = 7-loc->x};
}

void drawSuggestMoves(GameLayout* game, GameState* state)
{
    Location** dests = getAllAvailableMovesFromLocation(state,game->suggestMoves);
    if(dests == NULL)
        return;
    int i=0;
    while(dests[i] != NULL)
    {
        Location realSquare = toLayoutLocation(dests[i]);
        SDL_Rect ract = {   .x= game->boardLayout->startingPoint.x + realSquare.x  * (SQUARE_SIZE + SQUARE_GAP),
                .y=game->boardLayout->startingPoint.y + realSquare.y * (SQUARE_SIZE + SQUARE_GAP),
                .h=SQUARE_SIZE,
                .w=SQUARE_SIZE};
        GameState* tempState = duplicateGameState(state);
        if(tempState == NULL)
            continue;
        GameMove* move = applyMove(tempState, game->suggestMoves, dests[i]);
        if(move == NULL)
        {
            destroyGameState(tempState);
            continue;
        }
        if(isREALLYThreatened(tempState, dests[i]))
            SDL_SetRenderDrawColor(game->renderer, SUGGEST_MOVE_THREATENED_COLOR);
        else if(getPieceColor(state->board[dests[i]->x][dests[i]->y]) == oppositeColor(state->currentPlayer))
            SDL_SetRenderDrawColor(game->renderer, SUGGEST_MOVE_BEAT_COLOR);
        else
            SDL_SetRenderDrawColor(game->renderer, SUGGEST_MOVE_REGULAR_COLOR);
        destroyGameState(tempState);
        if(tolower(state->board[game->suggestMoves->x][game->suggestMoves->y]) == 'k' &&
                abs(game->suggestMoves->y - dests[i]->y) > 1) {
            SDL_SetRenderDrawColor(game->renderer, SUGGEST_MOVE_CASLTLE_COLOR);
            Location *rookLocation = createLocation(game->suggestMoves->x, (dests[i]->y > game->suggestMoves->y) ? CHESS_BOARD_SIZE-1 : 0);
            if(rookLocation == NULL)
                continue;
            Location rookSquare = toLayoutLocation(rookLocation);
            destroyLocation(rookLocation);
            SDL_Rect rookRact = {   .x= game->boardLayout->startingPoint.x + rookSquare.x  * (SQUARE_SIZE + SQUARE_GAP),
                    .y=game->boardLayout->startingPoint.y + rookSquare.y * (SQUARE_SIZE + SQUARE_GAP),
                    .h=SQUARE_SIZE,
                    .w=SQUARE_SIZE};
            SDL_RenderFillRect(game->renderer,&rookRact);
        }
        SDL_RenderFillRect(game->renderer,&ract);
        i++;
    }
    destroyLocationsList(dests);

}

SDL_Texture* charToTexture(GameLayout* game, char c)
{
    Pieces* pieces = c > 'a' ? game->white : game->black;

    switch(tolower(c))
    {
        case 'r':
            return pieces->rook;
            break;
        case 'n':
            return pieces->knight;
            break;
        case 'b':
            return pieces->bishop;
            break;
        case 'k':
            return pieces->king;
            break;
        case 'q':
            return pieces->queen;
            break;
        case 'm':
            return pieces->pawn;
            break;
        default:
            printf("BUG %c\n", c);
            return NULL;
    }
    return NULL;
}

void drawSquare(GameLayout* game, int x, int y, char c)
{
    SDL_Rect ract = {   .x= game->boardLayout->startingPoint.x + x * (SQUARE_SIZE + SQUARE_GAP),
            .y=game->boardLayout->startingPoint.y + y * (SQUARE_SIZE + SQUARE_GAP),
            .h=SQUARE_SIZE,
            .w=SQUARE_SIZE};
    SDL_Texture* image;

    SDL_Texture* texture = charToTexture(game,c);
    if(texture == NULL)
        return; //TODO -> BUG WHAT SHELL WE DO?
    if(game->draged != NULL && game->draged->location.x == 7-y && game->draged->location.y == x)
        return;
    SDL_RenderCopy(game->renderer, texture, NULL, &ract);
}

bool isPointOnGameLayout(GameLayout *game, int x, int y)
{
     return ((x >= game->boardLayout->startingPoint.x) &&
       (y >= game->boardLayout->startingPoint.y) &&
       (x <= game->boardLayout->startingPoint.x + (SQUARE_SIZE+SQUARE_GAP) * game->boardLayout->numInX)  &&
       (y <= game->boardLayout->startingPoint.y + (SQUARE_SIZE+SQUARE_GAP) * game->boardLayout->numInY));
}

Location getSquare(GameLayout* game, int x, int y)
{
    Location p = {.x= (y - game->boardLayout->startingPoint.y)/(SQUARE_SIZE+SQUARE_GAP),
                    .y = (x - game->boardLayout->startingPoint.x)/(SQUARE_SIZE+SQUARE_GAP)};

    p.x = 7 - p.x; //change to board position
    return p;
}