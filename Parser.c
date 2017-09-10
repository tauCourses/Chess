#include "Parser.h"

bool IsInt(const char* str)
{
    if(str == NULL)
        return false;

    if (*str == '-')
        str++;
    do
    {
        if ((*str < '0') || (*str > '9'))
            return false;
        str++;
    }while (*str != '\0' && *str != '\n');

    return true;
}

Command PraseLine(const char* str)
{
    const char delimeter[] = " \t\r\n";
    char line[MAX_LINE_LENGTH], *token;

    Command result;

    strcpy(line, str);
    token = strtok(line, delimeter);
    result.type = commandFromStr(token);

    if((result.type == gameMode)||(result.type == difficutly)||(result.type == userColor))
    {
        token = strtok(NULL, delimeter);
        if (IsInt(token))
        {
            result.value = atoi(token);
        }
        else
            result.type = invalid;
    }

    if((result.type == save)||(result.type == load))
    {
        token = strtok(NULL, delimeter);
        if (IsValidPath(token))
        {
            result.path = token;
        }
        else
            result.type = invalid;
    }

    if (result.type == move){
        token = strtok(NULL, delimeter);
        result.org = parseLocation(token);
        token = strtok(NULL, delimeter);
        if (strcmp(token,"to") == 0){
            token = strtok(NULL, delimeter);
            result.des = parseLocation(token);
        }
        else
            result.type = invalid;
        if ((result.org == NULL)||(result.des == NULL))
            result.type = invalid;
    }

    if (result.type == getPossibleMoves){
        token = strtok(NULL, delimeter);
        result.org = parseLocation(token);
        if (result.org == NULL)
            result.type = invalid;
    }

    token = strtok(NULL, delimeter);
    if (token != NULL)
        result.type = invalid;

    return result;
}

CommandType commandFromStr(char* token)
{
    if(token == NULL)
        return invalid;
    if(strcmp(token,"game_mode") == 0)
        return gameMode;
    if(strcmp(token,"difficulty") == 0)
        return difficutly;
    if(strcmp(token,"user_color") == 0)
        return userColor;
    if(strcmp(token,"load") == 0)
        return load;
    if(strcmp(token,"default") == 0)
        return defaultValues;
    if(strcmp(token,"print_setting") == 0)
        return printSetting;
    if(strcmp(token,"start") == 0)
        return start;


    if(strcmp(token,"move") == 0)
        return move;
    if(strcmp(token,"get_moves") == 0)
        return getPossibleMoves;
    if(strcmp(token,"save") == 0)
        return save;
    if(strcmp(token,"undo") == 0)
        return undo;
    if(strcmp(token,"reset") == 0)
        return reset;

    if(strcmp(token,"quit") == 0)
        return quit;

    return invalid;

}

bool IsValidPath(char* token)
{


}

Location* parseLocation(char* token)
{

}