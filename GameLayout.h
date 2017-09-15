#ifndef CHESS_GAMELAYOUT_H
#define CHESS_GAMELAYOUT_H

#include <SDL.h>
#include <stdbool.h>
#include "BoardLayout.h"
#include "GameManager.h"

#define BLACK_PAWN_IMAGE "images/pieces/blackPawn.bmp"
#define BLACK_ROOK_IMAGE "images/pieces/blackRook.bmp"
#define BLACK_KNIGHT_IMAGE "images/pieces/blackKnight.bmp"
#define BLACK_BISHOP_IMAGE "images/pieces/blackBishop.bmp"
#define BLACK_KING_IMAGE "images/pieces/blackKing.bmp"
#define BLACK_QUEEN_IMAGE "images/pieces/blackQueen.bmp"

#define WHITE_PAWN_IMAGE "images/pieces/whitePawn.bmp"
#define WHITE_ROOK_IMAGE "images/pieces/whiteRook.bmp"
#define WHITE_KNIGHT_IMAGE "images/pieces/whiteKnight.bmp"
#define WHITE_BISHOP_IMAGE "images/pieces/whiteBishop.bmp"
#define WHITE_KING_IMAGE "images/pieces/whiteKing.bmp"
#define WHITE_QUEEN_IMAGE "images/pieces/whiteQueen.bmp"

#define PIECES_BACK_GROUND_COLOR 34, 177, 76

typedef struct{
    SDL_Texture* pawn;
    SDL_Texture* rook;
    SDL_Texture* knight;
    SDL_Texture* bishop;
    SDL_Texture* king;
    SDL_Texture* queen;
} Pieces;

typedef struct{
    SDL_Texture* texture;
    Location location;
}DragedPiece;

typedef struct{
    BoardLayout* boardLayout;
    SDL_Renderer* renderer;
    Pieces* white;
    Pieces* black;
    DragedPiece* draged;
} GameLayout;

GameLayout* createGameLayout(SDL_Point startingPoint, SDL_Renderer* renderer);
Pieces* createPieces(SDL_Renderer* renderer, char* pawn, char* rook, char* bishop, char* knight, char* queen, char* king);
void setDragedPiece(GameLayout* game, int x, int y, char c);

void destroyGameLayout(GameLayout* game);
void destroyPieces(Pieces* pieces);
void destroyDragPiece(GameLayout* game);

void drawGameLayout(GameLayout* game, Board board);

SDL_Texture* charToTexture(GameLayout* game, char c);
void drawSquare(GameLayout* game, int x, int y, char c);

bool isPointOnGameLayout(GameLayout *game, int x, int y);
Location getSquare(GameLayout* game, int x, int y);

#endif //CHESS_GAMELAYOUT_H
