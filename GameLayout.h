#ifndef CHESS_GAMELAYOUT_H
#define CHESS_GAMELAYOUT_H

#include <SDL.h>
#include <stdbool.h>
#include "BoardLayout.h"
#include "GameManager.h"

/**
 * GameLayout summary:
 * the GameLayout module handle all functions that belongs to Game Layout
 */

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
#define SUGGEST_MOVE_THREATENED_COLOR 0,0,255,20
#define SUGGEST_MOVE_BEAT_COLOR 0,255,0,20
#define SUGGEST_MOVE_REGULAR_COLOR 0,255,255,20
#define SUGGEST_MOVE_CASLTLE_COLOR 70, 20, 90, 20


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
    Location* suggestMoves;
} GameLayout;

/**
 *  create new Game Layout
 *  @param renderer - the renderer for the window
 *  startingPoint - the starting point for creating the window
 *  @return
 *  the new Game Layout.
 */
GameLayout* createGameLayout(SDL_Point startingPoint, SDL_Renderer* renderer);

/**
 *  create new pieces
 *  @param renderer - the renderer for the pieces
 *  pawn - symbol of pawn
 *  rook - symbol of rook
 *  bishop - symbol of bishop
 *  knight - symbol of knight
 *  queen - symbol of queen
 *  king - symbol of king
 *  @return
 *  the new pieces created
 */
Pieces* createPieces(SDL_Renderer* renderer, char* pawn, char* rook, char* bishop, char* knight, char* queen, char* king);

/**
 *  create new draged piece
 *  @param game - the game layout to drag in
 *  loc - location in which the piece
 *  c - the char of piece
 *  @return true is success, false otherwise.
 */
bool setDragedPiece(GameLayout* game, Location loc, char c);

/**
 *  destroy game layout
 *  @param game - game layout to destroy
 *  @return void
 */
void destroyGameLayout(GameLayout* game);

/**
 *  destroy pieces
 *  @param pieces - pieces to destroy
 *  @return void
 */
void destroyPieces(Pieces* pieces);

/**
 *  destroy dragged piece
 *  @param game - game layout to destroy dragged piece in
 *  @return void
 */
void destroyDragPiece(GameLayout* game);

/**
 *  draw game layout
 *  @param game - game layout to draw
 *  state - the current game state to draw from
 *  @return true if success, false otherwise.
 */
bool drawGameLayout(GameLayout* game, GameState* state);

/**
 *  draw suggestes moves
 *  @param game - game layout to draw
 *  state - the current game state to draw from
 *  @return true if success, false otherwise.
 */
bool drawSuggestMoves(GameLayout* game, GameState* state);

/**
 *  turns char to the currect texture
 *  @param game - game layout to draw
 *  c - the char to draw
 *  @return the texture that fits the char.
 */
SDL_Texture* charToTexture(GameLayout* game, char c);

/**
 *  draw square in game layout
 *  @param game - game layout to draw
 *  x - x of point to draw
 *  y - y of point to draw
 *  c - char of piece to draw
 *  @return true if success, false otherwise.
 */
bool drawSquare(GameLayout* game, int x, int y, char c);

/**
 *  check if point is on game layout
 *  @param game - game layout to check
 *  x - x of point to check
 *  y - y of point to check
 *  @return true if point is on game layout, false otherwise.
 */
bool isPointOnGameLayout(GameLayout *game, int x, int y);

/**
 *  get sqaure from game layout with point
 *  @param game - game layout to get sqaure from
 *  x - x of point to get sqaure from
 *  y - y of point to get sqaure from
 *  @return location of square.
 */
Location getSquare(GameLayout* game, int x, int y);

#endif //CHESS_GAMELAYOUT_H
