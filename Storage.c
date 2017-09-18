#include "Storage.h"
#include "GameManager.h"
#include "GameState.h"

#include <errno.h>//for testing, can be deleted after load and save game in console works

bool saveGame(GameManager* game, char* filename)
{
    printf("saveGame: this is filename |%s|\n",filename);


    errno = 0;//for testing

    FILE * file = fopen(filename, "w");

    if (file==NULL) //for testing
        printf("Error %d \n", errno);//for testing

    if(file == NULL)
        return false;
    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(file, "<game>\n");
    fprintf(file, "<current_turn>%d</current_turn>\n",game->state->currentPlayer == BLACK_PLAYER ? 0 : 1);
    fprintf(file, "<game_mode>%d</game_mode>\n",game->mode==ONE_PLAYER_GAME_MODE?1:2);

    if(game->mode == ONE_PLAYER_GAME_MODE)
    {
        fprintf(file, "<difficulty>2</difficulty>\n");
        fprintf(file, "<user_color>1</user_color>\n");
    }
    else
    {
        fprintf(file, "<difficulty>%d</difficulty>\n", game->difficulty);
        fprintf(file, "<user_color>%d</user_color>\n", game->userColor == BLACK_PLAYER ? 0 : 1);
    }
    saveBoard(file, game->state);
    fprintf(file, "<general>%d%d%d%d%d%d</general>\n",game->state->whiteCastle->hasLeftRookMoved,
            game->state->whiteCastle->hasRightRookMoved,
            game->state->whiteCastle->hasKingMoved,
            game->state->blackCastle->hasLeftRookMoved,
            game->state->blackCastle->hasLeftRookMoved,
            game->state->blackCastle->hasLeftRookMoved);
    fprintf(file, "</game>\n");
    fclose(file);
    return true;

}

void saveBoard(FILE* file, GameState* state)
{
    fprintf(file, "<board>\n");
    for(int i=CHESS_BOARD_SIZE-1;i>=0;i--)
    {
        fprintf(file, "<row_%d>",i+1);
        for(int j=0; j<CHESS_BOARD_SIZE;j++)
            fprintf(file,"%c",state->board[i][j]);
        fprintf(file, "</row_%d>\n",i+1);
    }
    fprintf(file, "</board>\n");
}

bool isFileExist(char* filename)
{
    printf("isFileExists: this is filename |%s|\n",filename);
    FILE * file = fopen(filename, "r");
    if(file != NULL)
    {
        fclose(file);
        return true;
    }
    return false;
}

GameManager* loadGame(char* filename)
{
    GameManager* game = createEmptyGame();
    if(game == NULL)
        return NULL;

    FILE * file = fopen(filename, "r");

    if(file == NULL)
    {
        destroyGame(game);
        return NULL;
    }
    updateGameParams(game,file);
    updateBoardFromFile(game->state, file);
    updateCastlesStateFromFile(game->state, file);

    fclose(file);

    return game;
}

void updateCastlesStateFromFile(GameState* state, FILE* file) //please do not read it
{
    if(waitForChar(file, 'l') != EOF)
    {
        waitForChar(file, '>');
        state->whiteCastle->hasLeftRookMoved = (fgetc(file) == '1')? true : false;
        state->whiteCastle->hasRightRookMoved = (fgetc(file) == '1')? true : false;
        state->whiteCastle->hasKingMoved = (fgetc(file) == '1')? true : false;
        state->blackCastle->hasLeftRookMoved = (fgetc(file) == '1')? true : false;
        state->blackCastle->hasRightRookMoved = (fgetc(file) == '1')? true : false;
        state->blackCastle->hasKingMoved = (fgetc(file) == '1')? true : false;
    }
    else
    {
        state->blackCastle = createCastleState(true,true,true); //TODO -> MALLOC! WHAT IF FAIL?
        state->whiteCastle = createCastleState(true,true,true); //TODO -> MALLOC! WHAT IF FAIL?
    }
}
void updateGameParams(GameManager* game, FILE* file)
{
    char line[256];
    fgets ( line, sizeof(line), file );
    fgets ( line, sizeof(line), file );
    fgets ( line, sizeof(line), file );
    int currentTurn, gameMode,difficulty,userColor;
    sscanf(line, "<current_turn>%d</current_turn>", &currentTurn);
    game->state->currentPlayer = currentTurn == 0 ? BLACK_PLAYER : WHITE_PLAYER;
    fgets ( line, sizeof(line), file );
    sscanf(line, "<game_mode>%d</game_mode>", &gameMode);
    game->mode = (gameMode == 2) ? TWO_PLAYERS_GAME_MODE : ONE_PLAYER_GAME_MODE;
    if(game->mode==TWO_PLAYERS_GAME_MODE)
    {
        fgets(line, sizeof(line), file );
        while(strncmp(line, "<board>", 7))
            fgets(line, sizeof(line), file );
    }
    else
    {
        fgets(line, sizeof(line), file );
        sscanf(line, "<difficulty>%d</difficulty>", &difficulty);
        game->difficulty = difficulty;
        fgets(line, sizeof(line), file );
        sscanf(line, "<user_color>%d</user_color>", &userColor);
        game->userColor = userColor == 0 ? BLACK_PLAYER : WHITE_PLAYER;
        fgets(line, sizeof(line), file ); //read the board line
    }
}

char waitForChar(FILE* file, char c)
{
    char temp;
    while ((temp = (char)fgetc(file)) != c && temp != EOF);

    return temp;
}

void updateBoardFromFile(GameState* state, FILE* file)
{
    for (int i = CHESS_BOARD_SIZE - 1; i >= 0; i--) {
        waitForChar(file, '>');

        for (int j = 0; j < CHESS_BOARD_SIZE; j++)
            state->board[i][j] = (char) fgetc(file);

        waitForChar(file, '\n');
    }
}

void addGameToGameSlots(GameManager* game)
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

GameManager* loadGameFromSlots(int num)
{
    char filename[25];
    sprintf(filename, SlotBasicName, num);
    return loadGame(filename);
}