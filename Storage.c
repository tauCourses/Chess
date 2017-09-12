#include "Storage.h"
#include "Infrastructure.h"


bool saveGame(Game* game, char* filename)
{
    FILE * file = fopen(filename, "w");
    if(file == NULL)
        return false;
    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(file, "<game>\n");
    fprintf(file, "<current_turn>%d</current_turn>\n",game->state->currentPlayer == CHESS_GAME_PLAYER_COLOR_BLACK ? 0 : 1);
    fprintf(file, "<game_mode>%d</game_mode>\n",game->mode==CHESS_GAME_ONE_PLAYER?1:2);
    if(game->mode == 1)
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
    FILE * file = fopen(filename, "r");
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
    currentTurn = currentTurn == 0 ? CHESS_GAME_PLAYER_COLOR_BLACK : CHESS_GAME_PLAYER_COLOR_WHITE;
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
    {
        return NULL;
        fclose(file);
    }
    fclose(file);
    Game* game = createNewGame(gameMode, difficulty, userColor);
    if(game == NULL)
        return NULL;
    destroyBoard(game->state->board);
    game->state->board = board;
    game->state->currentPlayer = currentTurn;
    return game;

}

void waitForChar(FILE* file, char c)
{
    while((char)fgetc(file) != c);
}
char** loadBoard(FILE* file)
{
    char line[256];
    char** board = createNewBoard();
    if(board == NULL)
        return NULL;
    for(int i=CHESS_BOARD_SIZE-1;i>=0;i--)
    {
        waitForChar(file, '>');

        for(int j=0;j<CHESS_BOARD_SIZE;j++)
            board[i][j] = (char)fgetc(file);

        waitForChar(file, '\n');
    }
    return board;
}

void addGameToGameSlots(Game* game)
{
    char filename[25];
    sprintf(filename,SlotBasicName,1);
    moveSlots();
    saveGame(game,filename);
}
void moveSlots()
{
    char oldFileName[25], newFileName[25];
    int numberOfSlots = numberOfGameSlots();
    for(int i=numberOfSlots; i>0; i--)
    {
        if(i<MAX_NUMBER_OF_LOAD_GAMES)
        {
            sprintf(oldFileName,SlotBasicName,i);
            sprintf(newFileName,SlotBasicName,i+1);
            rename(oldFileName,newFileName);
        }
    }
}
int numberOfGameSlots()
{
    char filename[25];

    for(int i=MAX_NUMBER_OF_LOAD_GAMES; i>0; i--)
    {
        sprintf(filename,SlotBasicName,i);
        if(isFileExist(filename))
            return i;
    }
    return 0;
}

Game* loadGameFromSlots(int num)
{
    char filename[25];
    sprintf(filename, SlotBasicName, num);
    return loadGame(filename);
}