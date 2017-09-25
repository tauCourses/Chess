#ifndef CHESS_CONSOLEGAMESTATE_H
#define CHESS_CONSOLEGAMESTATE_H

#include <stdio.h>
#include "GameManager.h"
#include "Storage.h"
#include "Parser.h"
#include "AI.h"

/**
 * ConsoleGameState summary:
 * Handles the console game state.
 */

typedef enum GAME_STATE_COMMAND_TYPE{
	GAME_STATE_COMMAND_QUIT, GAME_STATE_COMMAND_MOVE ,GAME_STATE_COMMAND_GET_POSSIBLE_MOVES,
	GAME_STATE_COMMAND_SAVE, GAME_STATE_COMMAND_UNDO, GAME_STATE_COMMAND_CASTLE ,GAME_STATE_COMMAND_RESET, GAME_STATE_COMMAND_INVALID
} GAME_STATE_COMMAND_TYPE;

typedef struct GameStateCommand{
	GAME_STATE_COMMAND_TYPE type;
    char path[MAX_LINE_LENGTH];
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
#define MSG_UNDO_COM_CASTLE "Computer: castle King at %s and Rook at %s\n"
#define MSG_CASTLE_WRONG_POSITION_ROOK "Wrong position for a rook\n"
#define MSG_CASTLE_ILLEGAL "Illegal castling move\n"
#define MSG_INVALID_GET_MOVES "get_moves is not available in difficulty above 2 and in two players mode\n"
#define MSG_RESTART "Restarting...\n"

#define MSG_COM_MOVE_PAWN "Computer: move pawn at %s to %s\n"
#define MSG_COM_MOVE_BISHOP "Computer: move bishop at %s to %s\n"
#define MSG_COM_MOVE_knight "Computer: move knight at %s to %s\n"
#define MSG_COM_MOVE_rook "Computer: move rook at %s to %s>\n"
#define MSG_COM_MOVE_queen "Computer: move queen at %s to %s\n"
#define MSG_COM_MOVE_king "Computer: move king at %s to %s\n"

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

/**
 *  get a command from the user in game state mode.
 *  @param GCommand - the command to be updated.
 *  @return void
 */
void getGameStateCommandFromUser(GameStateCommand** GCommand);
/**
 *  execute a command from the user in game state mode.
 *  @param game - the game to execute the game on.
 *  GCommand - the command to be execute.
 *  @return the next state of console.
 */
GAME_INPUT_STATE executeGameStateCommand(GameManager* game, GameStateCommand* GCommand);
/**
 *  parse a command from the user in game state mode.
 *  @param str - the string as received from user.
 *  @return the command from user.
 */
GameStateCommand* PraseGameStateLine(const char* str);
/**
 *  parse a command type from the user in game state mode.
 *  @param str - the string as received from user.
 *  @return the command type from user.
 */
GAME_STATE_COMMAND_TYPE gameStateCommandFromStr(char* token);
/**
 *  parse a save command from the user in game state mode.
 *  @param token - the part after the command from the string as received from user.
 *  result - the command to be updated.
 *  delimeter - the chars that are delimeters
 *  @return void
 */
void parseSaveCommand(GameStateCommand* result, const char* token,const char delimeter[]);
/**
 *  parse a move command from the user in game state mode.
 *  @param token - the part after the command from the string as received from user.
 *  result - the command to be updated.
 *  delimeter - the chars that are delimeters
 *  @return void
 */
void parseMoveCommand(GameStateCommand* result, const char* token,const char delimeter[]);
/**
 *  parse a get_moves command from the user in game state mode.
 *  @param token - the part after the command from the string as received from user.
 *  result - the command to be updated.
 *  delimeter - the chars that are delimeters
 *  @return void
 */
void parsePossibleMovesCommand(GameStateCommand* result, const char* token,const char delimeter[]);
/**
 *  parse a castle command from the user in game state mode.
 *  @param token - the part after the command from the string as received from user.
 *  result - the command to be updated.
 *  delimeter - the chars that are delimeters
 *  @return void
 */
void parseCastle(GameStateCommand* result, const char* token,const char delimeter[]);



/**
 *  execute a move command from the user in game state mode.
 *  @param game - the game to execute the game on.
 *  GCommand - the command to be execute.
 *  @return the next state of console.
 */
GAME_INPUT_STATE executeCommandMove(GameManager* game, GameStateCommand* GCommand);
/**
 *  the part of execute a move command that deals after valid moves actions.
 *  @param game - the game to execute the game on.
 *  @return the next state of console.
 */
GAME_INPUT_STATE afterValidMove(GameManager* game);
/**
 *  execute a get_moves command from the user in game state mode.
 *  @param game - the game to execute the game on.
 *  GCommand - the command to be execute.
 *  @return void
 */
void executeCommandGetPossibleMoves(GameManager* game, GameStateCommand* GCommand);
/**
 *  checks if get_moves command is legal in current game.
 *  @param game - the game to check on.
 *  GCommand - the command to be execute.
 *  @return true if legal, false otherwise.
 */
bool isLegalGetPossibleMoves(GameManager* game, GameStateCommand* GCommand);
/**
 *  prints the list of locations for get_moves
 *  @param gameState - the gameState to print for.
 *  locations - list of possible locations.
 *  org - original piece location.
 *  @return void
 */
void printLocationsList(GameState* gameState, Location** locations,Location* org);
/**
 *  execute a save command from the user in game state mode.
 *  @param game - the game to execute the game on.
 *  GCommand - the command to be execute.
 *  @return void
 */
void executeCommandSave(GameManager* game, GameStateCommand GCommand);
/**
 *  execute a undo command from the user in game state mode.
 *  @param game - the game to execute the game on.
 *  @return void
 */
void executeCommandUndo(GameManager* game);
/**
 *  execute a castle command from the user in game state mode.
 *  @param game - the game to execute the game on.
 *  GCommand - the command to be execute.
 *  @return void
 */
void executeCommandCastle(GameManager* game,GameStateCommand* GCommand);
/**
 *  gets the destenation of the king in case of castle.
 *  @param game - the game to execute the game on.
 *  GCommand - the command to be execute.
 *  @return location of king.
 */
Location* castleGetKingDes(GameManager* game,GameStateCommand* GCommand);
/**
 *  execute a reset command from the user in game state mode.
 *  @param game - the game to execute the game on.
 *  @return void
 */
void executeCommandReset(GameManager* game);
/**
 *  execute a pawn promotion command from the user in game state mode.
 *  @param game - the game to execute the game on.
 *  des - the destination of the promoted pawn.
 *  @return void
 */
void executePawnPromotion(GameManager* game, Location* des);
/**
 *  parse a pawn promotion command from the user in game state mode.
 *  @param input - user input.
 *  playerColor - the current player color
 *  @return the promoted piece.
 */
char parsePawnPromotion(PLAYER_COLOR playerColor, char* input);
/**
 *  handle input in pawn promotion command.
 *  @param
 *  playerColor - the current player color
 *  @return the promoted piece.
 */
char getPiecePawnPromotion(PLAYER_COLOR playerColor);

/**
 *  make the computer move in one player mode.
 *  @param game - the game to do the move on.
 *  @return the next console state.
 */
GAME_INPUT_STATE makeComputerMove(GameManager* game);
/**
 *  prints the computer move.
 *  @param move - the move that had been done by the computer.
 *  piece - the piece that was moved.
 *  @return void
 */
void printComMove(GameMove* move, char piece);
/**
 *  prints the computer pawn promotion move.
 *  @param move - the move that had been done by the computer.
 *  piece - the piece that was moved.
 *  @return void
 */
void printComPawnPromotion(GameMove* move,char desPiece);



#endif //CHESS_CONSOLEGAMESTATE_H
