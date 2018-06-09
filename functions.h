#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "types.h"
#include <stdbool.h>

extern void initArray();
extern void initLaby();
extern void initLabyRandom();
extern void showLaby();
extern void askLabyEntranceExit();
extern bool setContent(int x, int y, int value);
extern void askAddWall();
extern bool isWallBlockingPath(int x, int y);
extern bool isAlreadyInArray(coord *labySearchPathList, coord c, int afterLastOfArray);
extern int askInt(char* message, int* x);
extern bool isInLabyOutLine(int x, int y);
extern bool isInBound(int x, int y);

#endif // FUNCTIONS_H_INCLUDED
