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


Location* parseLocation(const char* token)
{
	if (token[0] != '<')
		return NULL;
	if (!IsInt(token[1]))
		return NULL;
	if (token[2] != ',')
		return NULL;
	if (!IsInt(token[3]))
		return NULL;
	if (token[0] != '>')
		return NULL;
	return createLocation(token[1], token[3]);
}
