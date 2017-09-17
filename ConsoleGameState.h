#ifndef CHESS_CONSOLEGAMESTATE_H
#define CHESS_CONSOLEGAMESTATE_H

#include <stdio.h>
#include "GameManager.h"
#include "Parser.h"
#include "AI.h"

typedef enum GAME_STATE_COMMAND_TYPE{
	GAME_STATE_COMMAND_QUIT, GAME_STATE_COMMAND_MOVE ,GAME_STATE_COMMAND_GET_POSSIBLE_MOVES,
	GAME_STATE_COMMAND_SAVE, GAME_STATE_COMMAND_UNDO, GAME_STATE_COMMAND_CASTLE ,GAME_STATE_COMMAND_RESET, GAME_STATE_COMMAND_INVALID
} GAME_STATE_COMMAND_TYPE;

typedef struct GameStateCommand{
	GAME_STATE_COMMAND_TYPE type;
    char* path;
    Location* org;
    Location* des;
} GameStateCommand;

typedef enum GAME_INPUT_STATE{
	GAME_INPUT_SETTINGS_STATE, GAME_INPUT_GAME_STATE, GAME_INPUT_GAME_QUIT
} GAME_INPUT_STATE;



//define messages and errors to print
#define MSG_QUIT "Exiting...\n"
#define MSG_NEXT_MOVE_WHITE "white player - enter your move:\n"
#define MSG_NEXT_MOVE_BLACK "black player - enter your move:\n"
#define MSG_INVALID_POSTION "Invalid position on the board\n"
#define MSG_NOT_YOUR_PIECE "The specified position does not contain your piece\n"
#define MSG_ILLEGAL_MOVE "Illegal move\n"
#define MSG_CHECK_AGAINST_WHITE "Check: white King is threatened!\n"
#define MSG_CHECK_AGAINST_BLACK "Check: black King is threatened!\n"
#define MSG_CHECK_BY_COM "Check!\n"
#define MSG_WHITE_WIN "Checkmate! white player wins the game\n"
#define MSG_BLACK_WIN "Checkmate! black player wins the game\n"
#define MSG_TIE "The game is tied\n"
#define MSG_FILE_CANNOT_CREATED_MODIFIED "File cannot be created or modified\n"
#define MSG_UNDO_2_PLAYERS "Undo command not available in 2 players mode\n"
#define MSG_UNDO_EMPTY_HISTORY "Empty history, move cannot be undone\n"
#define MSG_UNDO_WHITE "Undo move for player white : %s -> %s\n"
#define MSG_UNDO_BLACK "Undo move for player black : %s -> %s\n"
#define MSG_CASTLE_WRONG_POSITION_ROOK "Wrong position for a rook\n"
#define MSG_CASTLE_ILLEGAL "Illegal castling move\n"
#define MSG_RESTART "Restarting...\n"

#define MSG_COM_MOVE_PAWN "Computer: move pawn at %s -> %s\n"
#define MSG_COM_MOVE_BISHOP "Computer: move bishop at <%d,%d> -> <%d,%d>\n"
#define MSG_COM_MOVE_knight "Computer: move knight at <%d,%d> -> <%d,%d>\n"
#define MSG_COM_MOVE_rook "Computer: move rook at <%d,%d> -> <%d,%d>\n"
#define MSG_COM_MOVE_queen "Computer: move queen at <%d,%d> -> <%d,%d>\n"
#define MSG_COM_MOVE_king "Computer: move king at <%d,%d> -> <%d,%d>\n"

#define MSG_COM_PAWN_PROMTION_PAWN "Computer: move pawn %s to %s and promote to pawn\n"
#define MSG_COM_PAWN_PROMTION_BISHOP "Computer: move pawn %s to %s and promote to bishop\n"
#define MSG_COM_PAWN_PROMTION_KNIGHT "Computer: move pawn %s to %s and promote to knight\n"
#define MSG_COM_PAWN_PROMTION_ROOK "Computer: move pawn %s to %s and promote to rook\n"
#define MSG_COM_PAWN_PROMTION_QUEEN "Computer: move pawn %s to %s and promote to queen\n"
#define MSG_COM_CASTLE "Computer: castle King at %s and Rook at %s\n"

#define MSG_PAWN_PROMOTION "Pawn promotion- please replace the pawn by queen, rook, knight, bishop or pawn:\n"
#define MSG_PAWN_PROMOTION_INVALID_TYPE "Invalid Type\n"

#define MSG_INVALID_IN_GAME "Invalid command\n"

#define ERR_FILE_CANNOT_OPEN_DONT_EXISTS "Error: File does not exist or cannot be opened\n"
#define ERR_MALLOC "ERROR: in allocating memory\n"
#define ERR_FGETS "ERROR: in receiving user input\n"


GameStateCommand getGameStateCommandFromUser();

GAME_INPUT_STATE executeGameStateCommand(GameManager* game, GameStateCommand* GCommand);

GameStateCommand PraseGameStateLine(const char* str);

GAME_STATE_COMMAND_TYPE gameStateCommandFromStr(char* token);

void parseSaveCommand(GameStateCommand* result, const char* token,const char delimeter[]);

void parseMoveCommand(GameStateCommand* result, const char* token,const char delimeter[]);

void parsePossibleMovesCommand(GameStateCommand* result, const char* token,const char delimeter[]);

void parseCastle(GameStateCommand* result, const char* token,const char delimeter[]);




GAME_INPUT_STATE executeCommandMove(GameManager* game, GameStateCommand* GCommand);

GAME_INPUT_STATE afterValidMove(GameManager* game);

void executeCommandGetPossibleMoves(GameManager* game, GameStateCommand* GCommand);

bool isLegalGetPossibleMoves(GameManager* game, GameStateCommand* GCommand);

void executeCommandSave(GameManager* game, GameStateCommand GCommand);

void executeCommandUndo(GameManager* game, GameStateCommand GCommand);

void executeCommandCastle(GameManager* game,GameStateCommand* GCommand);

Location* castleGetKingDes(GameManager* game,GameStateCommand* GCommand);

void executeCommandReset(GameManager* game, GameStateCommand GCommand);

void executePawnPromotion(GameManager* game, Location* des);

char parsePawnPromotion(PLAYER_COLOR playerColor, char* input);

char getPiecePawnPromotion(PLAYER_COLOR playerColor);


GAME_INPUT_STATE makeComputerMove(GameManager* game);

void printComMove(GameMove* move, char piece);

void printComPawnPromotion(GameMove* move,char desPiece);



#endif //CHESS_CONSOLEGAMESTATE_H
