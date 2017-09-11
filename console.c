#include "console.h"

int mainConsole()
{
    printf("console\n");
    return 0;
}

bool printBoard(char** board){
    for (int i=7; i>-1; i--){
        printf("%d| ",i+1);
        for (int j=0; j<8; j++){
            printf("%c ",getPieceInCoordinates(board,i,j));
        }
        printf("|\n");
    }
    printf("  -----------------\n");
    printf("   A B C D E F G H \n");
}

void printStateBoard(void* state){
    printBoard(((State*)state)->board);
}