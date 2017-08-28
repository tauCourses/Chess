//
// Created by LenovoPc on 27-Aug-17.
//

#ifndef CHESS_INFRASTRUCTURE_H
#define CHESS_INFRASTRUCTURE_H

typedef struct Location{
    int x,y;
} Location;

typedef struct sp_array_list_t {
    Location* elements;
    int actualSize;
    int maxSize;
} SPArrayList;


typedef struct Game{
    char** board;
    int mode;
    int difficulty;
    bool userColor;
    SPArrayList *history;
    Location* WKingLoc;
    Location* BKingLoc;
} Game;



//typedef struct Piece{
//    char type;
//    bool color;
//    Location location;
//} Piece;

#endif //CHESS_INFRASTRUCTURE_H
