#include "console.h"
#include "GameState.h"

int mainConsole()
{
    printf("console\n");
    return 0;
}

bool printBoard(GameState* state){
    for (int i=CHESS_BOARD_SIZE-1; i>=0; i--){
        printf("%d| ",i+1);
        for (int j=0; j<CHESS_BOARD_SIZE; j++){
            printf("%c ",state->board[i][j]);
        }
        printf("|\n");
    }
    printf("  -----------------\n");
    printf("   A B C D E F G H \n");
}

void printStateBoard(GameState* state)
{
    printBoard(state);
}