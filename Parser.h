//
// Created by LenovoPc on 11-Sep-17.
//

#ifndef CHESS_PARSER_H
#define CHESS_PARSER_H

#include <string.h>
#include "Location.h"

/**
 * Parse summary:
 * a module that handle only the general parsing of strings that
 * are user input.
 */

#define MAX_LINE_LENGTH 1024

/**
 *  checks if a string consists of an int
 *  @param str - string to check
 *  @return true if string represent an int, false otherwise
 */
bool IsInt(const char* str);

/**
 *  checks if a string consists of a location, return null otherwise.
 *  @param token - string to check
 *  @return the location if token is location format, null otherwise.
 */
Location* parseLocation(const char* token);

#endif //CHESS_PARSER_H
