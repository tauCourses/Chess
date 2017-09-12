
#ifndef CHESS_CONSOLE_H
#define CHESS_CONSOLE_H
#include "game.h"

//define messages and errors to print TODO -> SHOULD NOT BE HERE! FOR SURE!
#define MSG_SETTING_BEGIN "Specify game setting or type 'start' to begin a game with the current setting:\n"
#define MSG_GAME_MODE_1 "Game mode is set to 1 player\n"
#define MSG_GAME_MODE_2 "Game mode is set to 2 players\n"
#define MSG_GAME_MODE_WRONG "Wrong game mode\n"
#define MSG_EXPERT_NOT_SUPPORTED "Expert level not supported, please choose a value between 1 to 4:\n"
#define MSG_WRONG_DIFFICULTY "Wrong difficulty level. The value should be between 1 to 5\n"
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
#define MSG_UNDO_WHITE "Undo move for player white : <%d,%d> -> <%d,%d>\n"
#define MSG_UNDO_BLACK "Undo move for player black : <%d,%d> -> <%d,%d>\n"
#define MSG_RESTART "Restarting...\n"
#define MSG_COM_MOVE_PAWN "Computer: move pawn at <%d,%d> -> <%d,%d>\n"
#define MSG_COM_MOVE_BISHOP "Computer: move bishop at <%d,%d> -> <%d,%d>\n"
#define MSG_COM_MOVE_knight "Computer: move knight at <%d,%d> -> <%d,%d>\n"
#define MSG_COM_MOVE_rook "Computer: move rook at <%d,%d> -> <%d,%d>\n"
#define MSG_COM_MOVE_queen "Computer: move queen at <%d,%d> -> <%d,%d>\n"


#define ERR_FILE_CANNOT_OPEN_DONT_EXISTS "Error: File does not exist or cannot be opened\n"
#define ERR_MALLOC "ERROR: in allocating memory\n"


int mainConsole();
bool printBoard(char** board);

void printStateBoard(void* state);
#endif //CHESS_CONSOLE_H
