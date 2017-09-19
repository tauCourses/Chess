#include "Location.h"


Location* createLocation(int x, int y)
{
    Location* loc = (Location*) malloc(sizeof(Location));
    if(loc == NULL)
        return NULL;
    loc->x = x;
    loc->y = y;
    return loc;
}

Location* duplicateLocation(Location* location)
{
    Location* loc = (Location*) malloc(sizeof(Location));
    if(loc == NULL)
        return NULL;
    loc->x = location->x;
    loc->y = location->y;
    return loc;
}
void destroyLocation(Location* loc)
{
    free(loc);
}

bool isLocationOutOfBounds(Location* des)
{
    return ((des->x > 7) || (des->x < 0) || (des->y > 7) || (des->y < 0));
}

int compareLocations(const void * item1, const void * item2)
{
    const Location* loc1 = *(Location* const *)item1;
    const Location* loc2 = *(Location* const *)item2;
    if (loc1->x > loc2->x)
        return 1;

    if (loc1->x == loc2->x)
        return loc1->y - loc2->y;

    return -1;
}

char* getStringFromLocation(Location* loc)
{
	char* result = (char*) calloc(6, sizeof(char));
	if (result == NULL)
		return NULL;
	result[0] = '<';
	result[1] = loc->x + '1';
	result[2] = ',';
	result[3] = loc->y + 'A';
	result[4] = '>';
	return result;

}



void destroyLocationsList(Location** list)
{
    if(list == NULL)
        return;
    int i = 0;
    while(list[i] != NULL)
    {
        destroyLocation(list[i]);
        i++;
    }
    free(list);
}