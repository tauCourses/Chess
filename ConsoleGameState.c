#include "ConsoleGameState.h"
#include "GameState.h"
#include "GameManager.h"
#include "Location.h"

void getGameStateCommandFromUser(GameStateCommand** GCommand)
{
    char input[MAX_LINE_LENGTH];
    fgets(input,MAX_LINE_LENGTH,stdin);
	if (input == NULL)//error in fgets
    {
        printf(ERR_FGETS);
        GameStateCommand errorCommand;
		(*GCommand)->type = GAME_STATE_COMMAND_INVALID;
        return;
    }
	*GCommand = PraseGameStateLine(input);
}

GAME_INPUT_STATE executeGameStateCommand(GameManager* game, GameStateCommand* GCommand)
{
	printf("TestPrint executeGameStateCommand BEGIN\n");
	switch (GCommand->type)
	{
	case GAME_STATE_COMMAND_MOVE:
		return executeCommandMove(game,GCommand);

	case GAME_STATE_COMMAND_GET_POSSIBLE_MOVES:
		executeCommandGetPossibleMoves(game,GCommand);
		return GAME_INPUT_GAME_STATE;

	case GAME_STATE_COMMAND_SAVE:
		executeCommandSave(game,*GCommand);
		return GAME_INPUT_GAME_STATE;

	case GAME_STATE_COMMAND_UNDO:
		executeCommandUndo(game);
		return GAME_INPUT_GAME_STATE;

    case GAME_STATE_COMMAND_CASTLE:
        executeCommandCastle(game,GCommand);
        return GAME_INPUT_GAME_STATE;

	case GAME_STATE_COMMAND_RESET:
		executeCommandReset(game);
		return GAME_INPUT_SETTINGS_STATE;

	case GAME_STATE_COMMAND_INVALID:
		printf(MSG_INVALID_IN_GAME);
		return GAME_INPUT_GAME_STATE;

	case GAME_STATE_COMMAND_QUIT:
		break;

	default:
		break;
	}
	return GAME_STATE_COMMAND_INVALID; //TODO -> IS THIS A REAL VALUE? WHY CLION HATE IT?
}


GameStateCommand* PraseGameStateLine(const char* str) {
	const char delimeter[] = " \t\r\n";
	char line[MAX_LINE_LENGTH], *token;

	GameStateCommand* result = (GameStateCommand*) malloc(sizeof(GameStateCommand));
	if (result == NULL)
	{
		printf(ERR_MALLOC);
		return NULL;
	}

	strcpy(line, str);
	token = strtok(line, delimeter);
	result->type = gameStateCommandFromStr(token);

	printf("TestPrint PraseGameStateLine: this is result.type %d\n",result->type);

	if (result->type == GAME_STATE_COMMAND_SAVE) {
		token = strtok(NULL, delimeter);
		strcpy(result->path,token);
	}
	parseMoveCommand(result,token,delimeter);
	parsePossibleMovesCommand(result,token,delimeter);
    parseCastle(result,token,delimeter);


	token = strtok(NULL, delimeter);
	if (token != NULL )
		result->type = GAME_STATE_COMMAND_INVALID;

	printf("TestPrint PraseGameStateLine: this is result.type %d\n",result->type);

	return result;
}

void parseSaveCommand(GameStateCommand* result, const char* token,const char delimeter[])
{
	if (result->type == GAME_STATE_COMMAND_SAVE) {
		token = strtok(NULL, delimeter);
		strcpy(result->path,token);
	}
}

void parseMoveCommand(GameStateCommand* result, const char* token,const char delimeter[])
{
	printf("TestPrint in parseMoveCommand\n ");
	if (result->type == GAME_STATE_COMMAND_MOVE) {
		token = strtok(NULL, delimeter);
		printf("TestPrint in parseMoveCommand before parseLocation\n ");
		result->org = parseLocation(token);
		printf("TestPrint in parseMoveCommand after parseLocation\n ");
		token = strtok(NULL, delimeter);
		if (strcmp(token, "to") == 0) {
			token = strtok(NULL, delimeter);
			result->des = parseLocation(token);
		} else
			result->type = GAME_STATE_COMMAND_INVALID;
		if ((result->org == NULL )||(result->des == NULL))
			result->type = GAME_STATE_COMMAND_INVALID;
	}
}

void parsePossibleMovesCommand(GameStateCommand* result, const char* token,const char delimeter[])
{
	if (result->type == GAME_STATE_COMMAND_GET_POSSIBLE_MOVES) {
		token = strtok(NULL, delimeter);
		result->org = parseLocation(token);
		if (result->org == NULL )
			result->type = GAME_STATE_COMMAND_INVALID;
	}
}

void parseCastle(GameStateCommand* result, const char* token,const char delimeter[])
{
    if (result->type == GAME_STATE_COMMAND_CASTLE) {
        token = strtok(NULL, delimeter);
        result->org = parseLocation(token);
        if (result->org == NULL )
            result->type = GAME_STATE_COMMAND_INVALID;
    }
}


GAME_STATE_COMMAND_TYPE gameStateCommandFromStr(char* token) {

    if (token == NULL )
		return GAME_STATE_COMMAND_INVALID;

    if (strcmp(token, "game_mode") == 0)
		return GAME_STATE_COMMAND_MOVE;

    if (strcmp(token, "start") == 0)
		return GAME_STATE_COMMAND_SAVE;

    if (strcmp(token, "move") == 0)
		return GAME_STATE_COMMAND_MOVE;

    if (strcmp(token, "get_moves") == 0)
		return GAME_STATE_COMMAND_GET_POSSIBLE_MOVES;

    if (strcmp(token, "save") == 0)
		return GAME_STATE_COMMAND_SAVE;

    if (strcmp(token, "undo") == 0)
		return GAME_STATE_COMMAND_UNDO;

    if (strcmp(token, "castle") == 0)
        return GAME_STATE_COMMAND_CASTLE;

    if (strcmp(token, "reset") == 0)
		return GAME_STATE_COMMAND_RESET;

	if (strcmp(token, "quit") == 0)
		return GAME_STATE_COMMAND_QUIT;

	return GAME_STATE_COMMAND_INVALID;

}

GAME_INPUT_STATE executeCommandMove(GameManager* game, GameStateCommand* GCommand)
{
	GAME_MOVE_MESSAGE moveMessage;
	if (GCommand->org != NULL && GCommand->des != NULL)
	{
		moveMessage = movePiece(game,GCommand->org,GCommand->des);
	}
	else
	{
		printf(MSG_INVALID_POSTION);
		return GAME_INPUT_GAME_STATE;
	}

	switch (moveMessage)
	{
		case MOVE_VALID:
			if (afterValidMove(game) == GAME_INPUT_GAME_QUIT)
				return GAME_INPUT_GAME_QUIT;
			break;
		case MOVE_PAWN_REACH_END:
            printf(MSG_PAWN_PROMOTION);
			executePawnPromotion(game,GCommand->des);
			if (afterValidMove(game) == GAME_INPUT_GAME_QUIT)
				return GAME_INPUT_GAME_QUIT;
			break;
		case MOVE_INVALID_POSITION:
			printf(MSG_INVALID_POSTION);
			break;
		case MOVE_NOT_USER_PIECE:
			printf(MSG_NOT_YOUR_PIECE);
			break;
		case MOVE_INVALID_DUE_TO_CHESS_RULES:
			printf(MSG_ILLEGAL_MOVE);
			break;
		default:
			break;
	}

	destroyLocation(GCommand->org);
	destroyLocation(GCommand->des);

	return GAME_INPUT_GAME_STATE;
}

GAME_INPUT_STATE afterValidMove(GameManager* game)
{
	GAME_STATE gameStateMessage;
	gameStateMessage = getGameState(game);
	if (gameStateMessage == GAME_CHECKMATE)
	{
		if (oppositeColor(game->state->currentPlayer) == WHITE_PLAYER)
			printf(MSG_WHITE_WIN);
		else
			printf(MSG_BLACK_WIN);
		return GAME_INPUT_GAME_QUIT;
	}
	if (gameStateMessage == GAME_TIE)
	{
		printf(MSG_TIE);
		return GAME_INPUT_GAME_QUIT;
	}
	if (isKingThreatened(game->state))
	{
		if (game->mode == ONE_PLAYER_GAME_MODE && game->state->currentPlayer == game->userColor)
			printf(MSG_CHECK_BY_COM);
		else
		{
			if (game->state->currentPlayer == WHITE_PLAYER)
				printf(MSG_CHECK_AGAINST_WHITE);
			else
				printf(MSG_CHECK_AGAINST_BLACK);
		}

	}

	return GAME_INPUT_GAME_STATE;
}

void executeCommandGetPossibleMoves(GameManager* game, GameStateCommand* GCommand)
{
	if (isLegalGetPossibleMoves(game,GCommand))
	{
		Location** allMoves = getAllAvailableMovesFromLocation(game->state,GCommand->org);
		if (allMoves == NULL)
			printf(ERR_MALLOC); //TODO->shouldn't we terminate in this case
		else
		{
			printLocationsList(allMoves);
			destroyLocationsList(allMoves);
		}
	}
	destroyLocation(GCommand->org);

}

bool isLegalGetPossibleMoves(GameManager* game, GameStateCommand* GCommand)
{
	if (game->difficulty > 2 || game->mode == TWO_PLAYERS_GAME_MODE)
	{
		printf(MSG_INVALID_IN_GAME);
		return false;
	}
	if (GCommand->org == NULL)
	{
		printf(MSG_INVALID_POSTION);
		return false;
	}

	if (getPieceColor(game->state->board[GCommand->org->x][GCommand->org->y]) != game->state->currentPlayer)
	{
		printf(MSG_NOT_YOUR_PIECE);
		return false;
	}
	return true;
}

void executeCommandSave(GameManager* game, GameStateCommand GCommand)
{
	printf("\nexecuteCommandSave: started function\n");
	if (!saveGame(game,GCommand.path))
		printf(MSG_FILE_CANNOT_CREATED_MODIFIED);
}

void executeCommandUndo(GameManager* game)
{
	switch (candoundo(game))
	{
		case UNDO_REFUSED:
			printf(MSG_UNDO_2_PLAYERS);
			return;
		case UNDO_NO_HISTORY:
			printf(MSG_UNDO_EMPTY_HISTORY);
			return;
		default:
			break;
	}

	GameMove* move = undoMove(game);
    char* originString = getStringFromLocation(move->origin);
    char* destString = getStringFromLocation(move->des);
    bool isCastleMoveRight = isKing(game->state->board,move->des) && move->des->y + 2 == move->origin->y;
    bool isCastleMoveLeft = isKing(game->state->board,move->des) && move->des->y - 2 == move->origin->y;
    if (isCastleMoveRight && game->userColor == WHITE_PLAYER)
        printf(MSG_UNDO_COM_CASTLE,getStringFromLocation(move->origin),"<1,H>" );
    if (isCastleMoveRight && game->userColor == BLACK_PLAYER)
        printf(MSG_UNDO_COM_CASTLE,getStringFromLocation(move->origin),"<8,H>" );
    if (isCastleMoveLeft && game->userColor == WHITE_PLAYER)
        printf(MSG_UNDO_COM_CASTLE,getStringFromLocation(move->origin),"<1,A>" );
    if (isCastleMoveLeft && game->userColor == BLACK_PLAYER)
        printf(MSG_UNDO_COM_CASTLE,getStringFromLocation(move->origin),"<8,A>" );

    if (!isCastleMoveRight && !isCastleMoveLeft)
    {
        if (game->state->currentPlayer == WHITE_PLAYER)
            printf(MSG_UNDO_BLACK,originString,destString);
        else
            printf(MSG_UNDO_WHITE,originString,destString);
    }

    free(originString);
    free(destString);

	move = undoMove(game);
    originString = getStringFromLocation(move->origin);
    destString = getStringFromLocation(move->des);
	if (game->state->currentPlayer == WHITE_PLAYER)
		printf(MSG_UNDO_WHITE,originString,destString);
	else
		printf(MSG_UNDO_BLACK,originString,destString);
    free(originString);
    free(destString);
}

void executeCommandReset(GameManager* game)
{
	printf(MSG_RESTART);
	destroyGame(game);
}

void executeCommandCastle(GameManager* game,GameStateCommand* GCommand)
{
    Location* kingLoc = findKingLocation(game->state, game->state->currentPlayer); //TODO-> MIGHT FAIL! MALLOC INSIDE!
	Location* kingDes = castleGetKingDes(game,GCommand); //TODO -> AND WHAT IF, IN A VERY NOT COMMON SENARIO, THE MALLOC INSIDE WILL FAIL?!?!
	bool isPieceRook = false;
	if (!isLocationOutOfBounds(GCommand->org) && game->state->currentPlayer == WHITE_PLAYER && game->state->board[GCommand->org->x][GCommand->org->y] == 'r' )
		isPieceRook = true;
	if (!isLocationOutOfBounds(GCommand->org) && game->state->currentPlayer == BLACK_PLAYER && game->state->board[GCommand->org->x][GCommand->org->y] == 'R' )
		isPieceRook = true;
	if (isPieceRook)
	{
		if (kingDes != NULL && checkCastleMove(game->state,kingLoc,kingDes))
			applyMove(game->state,kingLoc,kingDes); //TODO -> applyMove may FAILED because of malloc!!!
		else
			printf(MSG_CASTLE_ILLEGAL);
	}
	else
		printf(MSG_CASTLE_WRONG_POSITION_ROOK);

	destroyLocation(kingLoc);
	destroyLocation(kingDes);
	destroyLocation(GCommand->org);
}

Location* castleGetKingDes(GameManager* game,GameStateCommand* GCommand)
{
	Location* kingDes = NULL;
	if (game->state->currentPlayer == WHITE_PLAYER && GCommand->org->x == 0 && GCommand->org->y == 7)
		kingDes = createLocation(0,6);
	if (game->state->currentPlayer == WHITE_PLAYER && GCommand->org->x == 0 && GCommand->org->y == 0)
		kingDes = createLocation(0,2);
	if (game->state->currentPlayer == BLACK_PLAYER && GCommand->org->x == 7 && GCommand->org->y == 7)
		kingDes = createLocation(7,6);
	if (game->state->currentPlayer == BLACK_PLAYER && GCommand->org->x == 7 && GCommand->org->y == 0)
		kingDes = createLocation(7,2);
	return kingDes;
}

void executePawnPromotion(GameManager* game, Location* des)
{
	char piece = getPiecePawnPromotion(game->state->currentPlayer);
	while (piece == '\0')
	{
		printf(MSG_PAWN_PROMOTION_INVALID_TYPE);
		piece = getPiecePawnPromotion(oppositeColor(game->state->currentPlayer));
	}
	game->state->board[des->x][des->y] = piece;
}

char getPiecePawnPromotion(PLAYER_COLOR playerColor)
{
    char input[MAX_LINE_LENGTH];

    fgets(input,MAX_LINE_LENGTH,stdin);
    if (input == NULL)//error in fgets
    {
        printf(ERR_FGETS);
        return '\0';
    }

	return parsePawnPromotion(playerColor,input);
}

char parsePawnPromotion(PLAYER_COLOR playerColor, char* input)
{
    const char delimeter[] = " \t\r\n";
    char piece = '\0';
	char *token;

	token = strtok(input, delimeter);

	if (token == NULL )
		return '\0';
	if (strcmp(token, "rook") == 0)
	{
		if (playerColor == WHITE_PLAYER)
			piece = 'r';
		else
			piece = 'R';
	}
	if (strcmp(token, "knight") == 0)
	{
		if (playerColor == WHITE_PLAYER)
			piece = 'n';
		else
			piece = 'N';
	}
	if (strcmp(token, "bishop") == 0)
	{
		if (playerColor == WHITE_PLAYER)
			piece = 'b';
		else
			piece = 'B';
	}
	if (strcmp(token, "pawn") == 0)
	{
		if (playerColor == WHITE_PLAYER)
			piece = 'm';
		else
			piece = 'M';
	}
    if (strcmp(token, "queen") == 0)
    {
        if (playerColor == WHITE_PLAYER)
            piece = 'q';
        else
            piece = 'Q';
    }
	token = strtok(NULL, delimeter);
	if (token != NULL )
		piece = '\0';

	return piece;
}

GAME_INPUT_STATE makeComputerMove(GameManager* game)
{
    GameMove* move = applyAIMove(game);
	bool isCastleMoveRight = isKing(game->state->board,move->des) && move->des->y + 2 == move->origin->y;
    bool isCastleMoveLeft = isKing(game->state->board,move->des) && move->des->y - 2 == move->origin->y;
    if (!move->pawnChanged && !(isCastleMoveRight||isCastleMoveLeft))
        printComMove(move,game->state->board[move->des->x][move->des->y]);
    if (move->pawnChanged)
        printComPawnPromotion(move,game->state->board[move->des->x][move->des->y]);
	if (isCastleMoveRight && game->userColor == WHITE_PLAYER)
		printf(MSG_COM_CASTLE,getStringFromLocation(move->origin),"<1,H>" );
    if (isCastleMoveRight && game->userColor == BLACK_PLAYER)
        printf(MSG_COM_CASTLE,getStringFromLocation(move->origin),"<8,H>" );
    if (isCastleMoveLeft && game->userColor == WHITE_PLAYER)
        printf(MSG_COM_CASTLE,getStringFromLocation(move->origin),"<1,A>" );
    if (isCastleMoveLeft && game->userColor == BLACK_PLAYER)
        printf(MSG_COM_CASTLE,getStringFromLocation(move->origin),"<8,A>" );
    return afterValidMove(game);
}

void printComMove(GameMove* move, char piece)
{
	char* originString = getStringFromLocation(move->origin);
	char* destString = getStringFromLocation(move->des);
	if(originString == NULL || destString == NULL)
	{
		free(originString);
		free(destString);
		return;
	}
    switch (piece)
    {
        case 'm':
        case 'M':
            printf(MSG_COM_MOVE_PAWN,originString, destString);
            break;
        case 'r':
        case 'R':
            printf(MSG_COM_MOVE_rook,originString, destString);
            break;
        case 'b':
        case 'B':
            printf(MSG_COM_MOVE_BISHOP,originString, destString);
            break;
        case 'n':
        case 'N':
            printf(MSG_COM_MOVE_knight,originString, destString);
            break;
        case 'q':
        case 'Q':
            printf(MSG_COM_MOVE_queen,originString, destString);
            break;
        case 'k':
        case 'K':
            printf(MSG_COM_MOVE_king,originString, destString);
            break;
        default:
            break;
    }
	free(originString);
	free(destString);
}

void printComPawnPromotion(GameMove* move,char desPiece)
{
	char* originString = getStringFromLocation(move->origin);
	char* destString = getStringFromLocation(move->des);
	if(originString == NULL || destString == NULL)
	{
		free(originString);
		free(destString);
		return;
	}
    switch (desPiece)
    {
        case 'm':
        case 'M':
            printf(MSG_COM_PAWN_PROMTION_PAWN,originString, destString);
            break;
        case 'r':
        case 'R':
            printf(MSG_COM_PAWN_PROMTION_ROOK,originString, destString);
            break;
        case 'b':
        case 'B':
            printf(MSG_COM_PAWN_PROMTION_BISHOP,originString, destString);
            break;
        case 'n':
        case 'N':
            printf(MSG_COM_PAWN_PROMTION_KNIGHT,originString, destString);
            break;
        case 'q':
        case 'Q':
            printf(MSG_COM_PAWN_PROMTION_QUEEN,originString, destString);
            break;

        default:
            break;
    }
	free(originString);
	free(destString);
}


