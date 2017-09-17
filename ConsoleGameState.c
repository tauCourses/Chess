#include "ConsoleGameState.h"
#include "GameState.h"
#include "GameManager.h"
#include "Location.h"

GameStateCommand getGameStateCommandFromUser()
{
    char input[MAX_LINE_LENGTH];
    fgets(input,MAX_LINE_LENGTH,stdin);
	if (input == NULL)//error in fgets
    {
        printf(ERR_FGETS);
        GameStateCommand errorCommand;
        errorCommand.type = GAME_STATE_COMMAND_INVALID;
        return errorCommand;
    }
    return PraseGameStateLine(input);
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
		executeCommandUndo(game,*GCommand);
		return GAME_INPUT_GAME_STATE;

    case GAME_STATE_COMMAND_CASTLE:
        executeCommandCastle(game,GCommand);
        return GAME_INPUT_GAME_STATE;

	case GAME_STATE_COMMAND_RESET:
		executeCommandReset(game,*GCommand);
		return GAME_INPUT_SETTINGS_STATE;

	case GAME_STATE_COMMAND_INVALID:
		printf(MSG_INVALID_IN_GAME);
		return GAME_INPUT_GAME_STATE;

	case GAME_STATE_COMMAND_QUIT:
		break;

	default:
		break;
	}
	return GAME_STATE_COMMAND_INVALID;
}


GameStateCommand PraseGameStateLine(const char* str) {
	const char delimeter[] = " \t\r\n";
	char line[MAX_LINE_LENGTH], *token;

	GameStateCommand result;

	strcpy(line, str);
	token = strtok(line, delimeter);
	result.type = gameStateCommandFromStr(token);

	printf("TestPrint PraseGameStateLine: this is result.type %d\n",result.type);

	parseSaveCommand(&result,token,delimeter);
	parseMoveCommand(&result,token,delimeter);
	parsePossibleMovesCommand(&result,token,delimeter);
    parseCastle(&result,token,delimeter);


	token = strtok(NULL, delimeter);
	if (token != NULL )
		result.type = GAME_STATE_COMMAND_INVALID;

	printf("TestPrint PraseGameStateLine: this is result.type %d\n",result.type);

	return result;
}

void parseSaveCommand(GameStateCommand* result, const char* token,const char delimeter[])
{
	if (result->type == GAME_STATE_COMMAND_SAVE) {
		token = strtok(NULL, delimeter);
		result->path = (char*)token;
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
	GAME_STATE gameState;
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
			printf(ERR_MALLOC);
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
	if (!saveGame(game,GCommand.path))
		printf(MSG_FILE_CANNOT_CREATED_MODIFIED);
}

void executeCommandUndo(GameManager* game, GameStateCommand GCommand)
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
	if (game->state->currentPlayer == WHITE_PLAYER)
		printf(MSG_UNDO_BLACK,getStringFromLocation(move->origin),getStringFromLocation(move->des));
	else
		printf(MSG_UNDO_WHITE,getStringFromLocation(move->origin),getStringFromLocation(move->des));

	move = undoMove(game);
	if (game->state->currentPlayer == WHITE_PLAYER)
		printf(MSG_UNDO_WHITE,getStringFromLocation(move->origin),getStringFromLocation(move->des));
	else
		printf(MSG_UNDO_BLACK,getStringFromLocation(move->origin),getStringFromLocation(move->des));

}

void executeCommandReset(GameManager* game, GameStateCommand GCommand)
{
	printf(MSG_RESTART);
	destroyGame(game);
}

void executeCommandCastle(GameManager* game,GameStateCommand* GCommand)
{
    Location* kingLoc = findKingLocation(game->state, game->state->currentPlayer);
	Location* kingDes = castleGetKingDes(game,GCommand);
	bool isPieceRook = false;
	if (!isLocationOutOfBounds(GCommand->org) && game->state->currentPlayer == WHITE_PLAYER && game->state->board[GCommand->org->x][GCommand->org->y] == 'r' )
		isPieceRook = true;
	if (!isLocationOutOfBounds(GCommand->org) && game->state->currentPlayer == BLACK_PLAYER && game->state->board[GCommand->org->x][GCommand->org->y] == 'R' )
		isPieceRook = true;
	if (isPieceRook)
	{
		if (kingDes != NULL && checkCastleMove(game->state,kingLoc,kingDes))
			applyMove(game->state,kingLoc,kingDes);
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
	bool isCastleMove = isKing(game->state->board,move->des) && (move->des->x + 2 == move->origin->x || move->des->x - 2 == move->origin->x);
    if (!move->pawnChanged && !isCastleMove)
        printComMove(move,game->state->board[move->des->x][move->des->y]);
    if (move->pawnChanged)
        printComPawnPromotion(move,game->state->board[move->des->x][move->des->y]);
	if (isCastleMove)
		printf(MSG_COM_CASTLE);

	return afterValidMove(game);
}

void printComMove(GameMove* move, char piece)
{
    switch (piece)
    {
        case 'm':
        case 'M':
            printf(MSG_COM_MOVE_PAWN,getStringFromLocation(move->origin), getStringFromLocation(move->des));
            break;
        case 'r':
        case 'R':
            printf(MSG_COM_MOVE_rook,getStringFromLocation(move->origin), getStringFromLocation(move->des));
            break;
        case 'b':
        case 'B':
            printf(MSG_COM_MOVE_BISHOP,getStringFromLocation(move->origin), getStringFromLocation(move->des));
            break;
        case 'n':
        case 'N':
            printf(MSG_COM_MOVE_knight,getStringFromLocation(move->origin), getStringFromLocation(move->des));
            break;
        case 'q':
        case 'Q':
            printf(MSG_COM_MOVE_queen,getStringFromLocation(move->origin), getStringFromLocation(move->des));
            break;
        case 'k':
        case 'K':
            printf(MSG_COM_MOVE_king,getStringFromLocation(move->origin), getStringFromLocation(move->des));
            break;
        default:
            break;
    }
}

void printComPawnPromotion(GameMove* move,char desPiece)
{
    switch (desPiece)
    {
        case 'm':
        case 'M':
            printf(MSG_COM_PAWN_PROMTION_PAWN,getStringFromLocation(move->origin), getStringFromLocation(move->des));
            break;
        case 'r':
        case 'R':
            printf(MSG_COM_PAWN_PROMTION_ROOK,getStringFromLocation(move->origin), getStringFromLocation(move->des));
            break;
        case 'b':
        case 'B':
            printf(MSG_COM_PAWN_PROMTION_BISHOP,getStringFromLocation(move->origin), getStringFromLocation(move->des));
            break;
        case 'n':
        case 'N':
            printf(MSG_COM_PAWN_PROMTION_KNIGHT,getStringFromLocation(move->origin), getStringFromLocation(move->des));
            break;
        case 'q':
        case 'Q':
            printf(MSG_COM_PAWN_PROMTION_QUEEN,getStringFromLocation(move->origin), getStringFromLocation(move->des));
            break;

        default:
            break;
    }
}


