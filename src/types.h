#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//The max maze size for the random generator, otherwise it would take too long, you can change it
#define LABY_MAX_SIZE 50

//Maze int configuration, don't change it
#define LABY_EMPTY_INT 0
#define LABY_ENTRANCE_INT 1
#define LABY_EXIT_INT 2
#define LABY_WALL_INT 9
#define LABY_PATH_INT 5

//How the program show each item, you can change it
#define LABY_EMPTY_SYMBOL "0"
#define LABY_ENTRANCE_SYMBOL "E"
#define LABY_EXIT_SYMBOL "S"
#define LABY_WALL_SYMBOL "M"
#define LABY_PATH_SYMBOL "X"

//The save file, you can change it
#define LABY_SAVE_FILE "saved_labyrinth.txt"

typedef struct labyCase
{
    int value;
    int parent_x;
    int parent_y;
} labyCase;

typedef struct _coord
{
    int x;
    int y;
} coord;

int LABY_SIZE_X;
int LABY_SIZE_Y;
labyCase **laby;

int LABY_ENTRANCE_x;
int LABY_ENTRANCE_y;
int LABY_EXIT_x;
int LABY_EXIT_y;


#endif // TYPES_H_INCLUDED
