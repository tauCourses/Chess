//
// Created by LenovoPc on 11-Sep-17.
//

#ifndef CHESS_PARSER_H
#define CHESS_PARSER_H

#include "infrastructure.h"
#include "string.h"

bool IsInt(const char* str);

Command PraseLine(const char* str);

CommandType commandFromStr(char* token);

bool IsValidPath(char* token);

Location* parseLocation(char* token);

#endif //CHESS_PARSER_H
