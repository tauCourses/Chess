#include "BoardLayout.h"

BoardLayout* createBoardLayout(SDL_Point startingPoint, int numInX, int numInY)
{
    BoardLayout* boardLayout = (BoardLayout*) malloc(sizeof(BoardLayout));
    if(boardLayout == NULL)
        return NULL;

    boardLayout->startingPoint =  startingPoint; //set the location of the button
    boardLayout->numInX = numInX; //set as valid/invalid button by default
    boardLayout->numInY = numInY; //set as valid/invalid button by default

    return boardLayout;
}

void destroyBoardLayout(BoardLayout* board)
{
    if (board == NULL )
        return;

    free(board);
}

void drawBoardLayout(SDL_Renderer* renderer, BoardLayout* board)
{
    int i,j;
	if (board == NULL )
        return;

    Board_Square_Type currentType = BOARD_SQUARE_WHITE;
    for(i=0; i<board->numInX; i++)
    {
        for(j=0;j<board->numInY;j++)
        {
            if(currentType == BOARD_SQUARE_WHITE)
            {
                SDL_SetRenderDrawColor(renderer, WHITE_RGBA_COLOR);
                SDL_Rect ract = {   .x= board->startingPoint.x + i * (SQUARE_SIZE + SQUARE_GAP),
                                    .y=board->startingPoint.y + j * (SQUARE_SIZE + SQUARE_GAP),
                                    .h=SQUARE_SIZE,
                                    .w=SQUARE_SIZE};
                SDL_RenderFillRect(renderer,&ract);
                currentType = BOARD_SQUARE_BLACK;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, BLACK_RGBA_COLOR);
                SDL_Rect ract = {   .x= board->startingPoint.x + i * (SQUARE_SIZE + SQUARE_GAP),
                        .y=board->startingPoint.y + j * (SQUARE_SIZE + SQUARE_GAP),
                        .h=SQUARE_SIZE,
                        .w=SQUARE_SIZE};
                SDL_RenderFillRect(renderer,&ract);
                currentType = BOARD_SQUARE_WHITE;
            }
        }
        currentType = (currentType==BOARD_SQUARE_WHITE) ? BOARD_SQUARE_BLACK : BOARD_SQUARE_WHITE;
    }
}




