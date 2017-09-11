#include "Storage.h"
#include "Infrastructure.h"


bool saveGame(Game* game, char* filename)
{
    FILE * file = fopen(filename, "w");
    if(file == NULL)
        return false;
    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(file, "<game>\n");
    fprintf(file, "<current_turn>%d</current_turn>\n",0);
    fprintf(file, "<game_mode>%d</game_mode>\n",1);
    if(game->mode == CHESS_GAME_ONE_PLAYER)
    {
        fprintf(file, "<difficulty>%d</difficulty>\n",2);
        fprintf(file, "<user_color>%d</user_color>\n",1);
    }
    saveBoard(file, game->state->board);
    fprintf(file, "</game>\n");
    fclose(file);
    return true;

}

void saveBoard(FILE* file, char** board)
{
    fprintf(file, "<board>\n");
    for(int i=CHESS_BOARD_SIZE-1;i>=0;i--)
    {
        fprintf(file, "<row_%d>",i+1);
        for(int j=0; j<CHESS_BOARD_SIZE;j++)
            fprintf(file,"%c",board[i][j]);
        fprintf(file, "</row_%d>\n",i+1);
    }
    fprintf(file, "</board>\n");
}

bool isFileExist(char* filename)
{
    FILE * file = fopen(filename, "w");
    if(file != NULL)
    {
        fclose(file);
        return true;
    }
    return false;
}
Game* loadGame(char* filename)
{
    char line[256];
    FILE * file = fopen(filename, "r");
    if(file == NULL)
        return NULL;
    fgets ( line, sizeof(line), file );
    fgets ( line, sizeof(line), file );
    fgets ( line, sizeof(line), file );
    int currentTurn, gameMode,difficulty,userColor;
    sscanf(line, "<current_turn>%d</current_turn>", &currentTurn);
    fgets ( line, sizeof(line), file );
    sscanf(line, "<game_mode>%d</game_mode>", &gameMode);
    if(gameMode==2)
    {
        fgets(line, sizeof(line), file );
        while(strncmp(line, "<board>", 7))
            fgets(line, sizeof(line), file );
    }
    else
    {
        fgets(line, sizeof(line), file );
        sscanf(line, "<difficulty>%d</difficulty>", &difficulty);
        fgets(line, sizeof(line), file );
        sscanf(line, "<user_color>%d</user_color>", &userColor);
        fgets(line, sizeof(line), file ); //read the board line
    }
    char** board = loadBoard(file);
    if(board == NULL)
        return NULL;
    fclose(file);
}

char** loadBoard(FILE* file)
{
    char line[256];
    char** board = (char **)malloc(sizeof(char *) * CHESS_BOARD_SIZE);
    if(board == NULL)
        return NULL;
    for(int i=CHESS_BOARD_SIZE-1;i>=0;i--)
    {
        fgets(line, sizeof(line), file );
        sscanf(line, "<%s>%c%c%c%c%c%c%c%c<%s>", &board[i][0], &board[i][1], &board[i][2], &board[i][3], &board[i][4]
                , &board[i][5], &board[i][6], &board[i][7]);
    }
    return board;
}