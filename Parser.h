//
// Created by LenovoPc on 11-Sep-17.
//

#ifndef CHESS_PARSER_H
#define CHESS_PARSER_H

#include "string.h"
#include "GameManager.h"
#include "Location.h"
#include "Storage.h"



#define MAX_LINE_LENGTH 1024

bool IsInt(const char* str);

Location* parseLocation(const char* token);

#endif //CHESS_PARSER_H
