#ifndef CHESS_LOCATION_H
#define CHESS_LOCATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Location summary:
 * a module that handle the location struct and related functions.
 */

typedef struct {
    int x,y;
} Location;

/**
 *  create a new location
 *  @param x - x parameter of location
 *  y - y parameter of location
 *  @return the new location
 */
Location* createLocation(int x, int y);

/**
 *  create a new duplicated location
 *  @param location - location to duplicate
 *  @return the new location
 */
Location* duplicateLocation(Location* location);

/**
 *  destroy location
 *  @param location - location to destroy
 *  @return void
 */
void destroyLocation(Location* loc);

/**
 *  check if location is out of bounds
 *  @param des - location to check
 *  @return true if out of bounds, false otherwise.
 */
bool isLocationOutOfBounds(Location* des);

/**
 *  compare two location according to x parameter, and if equal according to y.
 *  @param item1 - first location to compare
 *  item2 - second location to compare
 *  @return 1 if item1 is bigger, -1 if item2, 0 if they're equal.
 */
int compareLocations(const void * item1, const void * item2);

/**
 *  get a string represting location in correct format for print
 *  @param loc - location to get string from.
 *  @return string represting location in correct format for print
 */
char* getStringFromLocation(Location* loc);

/**
 *  destroy a list of locations
 *  @param list - list of location to destroy
 *  @return void
 */
void destroyLocationsList(Location** list);


#endif //CHESS_LOCATION_H
