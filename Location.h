#ifndef CHESS_LOCATION_H
#define CHESS_LOCATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x,y;
} Location;

Location* createLocation(int x, int y);

Location* duplicateLocation(Location* location);

void destroyLocation(Location* loc);

bool isLocationOutOfBounds(Location* des);

int compareLocations(const void * item1, const void * item2);

char* getStringFromLocation(Location* loc);

void printLocationsList(Location** locations);


#endif //CHESS_LOCATION_H
