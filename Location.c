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
    Location* loc1 = (Location*)item1;
    Location* loc2 = (Location*)item2;
    if (loc1->x > loc2->x)
        return 1;

    if (loc1->x == loc2->x)
        return loc1->y - loc2->y;

    return -1;
}

char* getStringFromLocation(Location* loc)
{
	char* result = (char*) malloc(sizeof(char)*6);
	if (result == NULL)
		return NULL;
	result[0] = '<';
	result[1] = loc->x + '1';
	result[2] = ',';
	result[3] = loc->y + 'A';
	result[4] = '>';
    result[5] = '\0';
	return result;

}

void printLocationsList(Location** locations)
{
	int index = 0 ;
	char* currentLoc;
	while (locations[index] != NULL)
	{
		currentLoc = getStringFromLocation(locations[index]);
		if (currentLoc != NULL)
			printf("%s\n",currentLoc);
		else
			printf("ERROR: failed to malloc in Location.c - getStringFromLocation");
        index++;
        free(currentLoc);
	}

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