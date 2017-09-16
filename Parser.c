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
    printf("TestPrint this is token in parseLocation %s\n", token );
    if (token[0] != '<')
		return NULL;
	if ('8' < token[1] || token[1] < '1')
		return NULL;
    printf("after token[1]\n");
	if (token[2] != ',')
		return NULL;
	if ('A' > token[3] || token[3] > 'I')
		return NULL;
    printf("after token[3]\n");
	if (token[4] != '>')
		return NULL;
	printf("TestPrint i'm about to create and send Location\n");
    return createLocation(token[1]-'1', token[3]-'A');
}
