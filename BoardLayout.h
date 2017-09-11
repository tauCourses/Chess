#ifndef CHESS_BOARDLAYOUT_H
#define CHESS_BOARDLAYOUT_H

#include <SDL.h>
#include <stdbool.h>

#define SQUARE_SIZE 80
#define SQUARE_GAP 1
#define BLACK_COLOR 0, 153, 51, 255
#define WHITE_COLOR 255, 179, 102, 255

typedef enum { //validation options
    BOARD_SQUARE_BLACK, BOARD_SQUARE_WHITE
} Board_Square_Type;


typedef struct{
    SDL_Point startingPoint;
    int numInX, numInY; //number of squeres in each direction
} BoardLayout;

BoardLayout* createBoardLayout(SDL_Point startingPoint, int numInX, int numInY);
void destroyBoardLayout(BoardLayout* board);

void drawBoardLayout(SDL_Renderer* renderer, BoardLayout* board);

bool isPointOnBoardLayout(BoardLayout *button, int x, int y);


#endif //CHESS_BOARDLAYOUT_H
