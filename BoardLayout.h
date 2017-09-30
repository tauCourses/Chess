#ifndef CHESS_BOARDLAYOUT_H
#define CHESS_BOARDLAYOUT_H

#include <SDL.h>
#include <stdbool.h>

/**
 * BoardLayout summary:
 * Responsible for the chess board basic layout
 */

#define SQUARE_SIZE 80
#define SQUARE_GAP 1
//#define BLACK_RGBA_COLOR 212, 242, 157, 255
#define BLACK_RGBA_COLOR 220, 220, 220, 255
//#define WHITE_RGBA_COLOR 155, 40, 34, 255
#define WHITE_RGBA_COLOR 25, 25, 120, 255

typedef enum { //validation options
    BOARD_SQUARE_BLACK, BOARD_SQUARE_WHITE
} Board_Square_Type;


typedef struct{
    SDL_Point startingPoint;
    int numInX, numInY; //number of squeres in each direction
} BoardLayout;

/**
 *  create new board layout
 *  @param startingPoint - start point for drawing board layout
 *  numInX - the number for X axis
 *  numInY - the number for Y axis
 *  @return
 *  the new board layout.
 */
BoardLayout* createBoardLayout(SDL_Point startingPoint, int numInX, int numInY);

/**
 *  destroy board layout
 *  @param board - board to destroy
 *  @return void
 */
void destroyBoardLayout(BoardLayout* board);

/**
 *  draws board layout
 *  @param renderer - the renderer to draw
 *  board - the board layout
 *  @return
 *  void
 */
void drawBoardLayout(SDL_Renderer* renderer, BoardLayout* board);

/**
 *  check if given point is on board layout
 *  @param button - the board layout
 *  x - x of point
 *  y - y of point
 *  @return true if point is on button, false otherwise.
 */
bool isPointOnBoardLayout(BoardLayout *button, int x, int y);


#endif //CHESS_BOARDLAYOUT_H
