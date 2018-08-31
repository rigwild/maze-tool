#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "types.h"

//Show a path from entrance to exit if exist
void showPath()
{
	//Firstly, we copy the laby array to not edit its values.
	int i, j;
	int** pathArray = (int **) malloc(LABY_SIZE_X*sizeof(int *));
	for(i=0;i < LABY_SIZE_X;i++)
		pathArray[i] = (int *) malloc(LABY_SIZE_Y*sizeof(int));

	for (i = 0; i < LABY_SIZE_X; i++)
		for (j = 0; j < LABY_SIZE_Y; j++)
			pathArray[i][j] = laby[i][j].value;

	coord temp, temp2;
	if (laby[LABY_EXIT_x][LABY_EXIT_y].value == LABY_EXIT_INT
		&& laby[LABY_EXIT_x][LABY_EXIT_y].parent_x != -1
		&& laby[LABY_EXIT_x][LABY_EXIT_y].parent_y != -1)
	{
		temp.x = LABY_EXIT_x;
		temp.y = LABY_EXIT_y;
		while (temp.x != LABY_ENTRANCE_x && temp.y != LABY_ENTRANCE_y)
		{
			pathArray[temp.x][temp.y] = LABY_PATH_INT;
			temp2.x = laby[temp.x][temp.y].parent_x;
			temp2.y = laby[temp.x][temp.y].parent_y;
			temp.x = temp2.x;
			temp.y = temp2.y;
		}
		pathArray[LABY_EXIT_x][LABY_EXIT_y] = LABY_EXIT_INT;
	}
	else
	{
		//Placing a wall is initiating the path by setting each cell's parent coordinates
		//So we just execute this function, even if it does nothing here.
		isWallBlockingPath(0, 0);
	}


	//Eventually, we print the maze with the path in it. (showLaby function clone!)

	printf("\nCase vide : %s # Entrée : %s # Sortie : %s # Mur : %s # Chemin : %s\n", LABY_EMPTY_SYMBOL, LABY_ENTRANCE_SYMBOL, LABY_EXIT_SYMBOL, LABY_WALL_SYMBOL, LABY_PATH_SYMBOL);

	for (j = LABY_SIZE_Y-1;j >= 0;j--) {
		//Laby line indicator
		if (LABY_SIZE_Y > 100)
			printf("\n%03d--", j);
		else if (LABY_SIZE_Y > 10)
			printf("\n%02d--", j);
		else
			printf("\n%d--", j);

		for (i = 0;i < LABY_SIZE_X;i++) {
			switch (pathArray[i][j]) {
				case LABY_ENTRANCE_INT:
				printf("%s ", LABY_ENTRANCE_SYMBOL);
				break;
				case LABY_EXIT_INT:
				printf("%s ", LABY_EXIT_SYMBOL);
				break;
				case LABY_WALL_INT:
				printf("%s ", LABY_WALL_SYMBOL);
				break;
				case LABY_PATH_INT:
				printf("%s ", LABY_PATH_SYMBOL);
				break;
				default:
				case LABY_EMPTY_INT:
				printf("%s ", LABY_EMPTY_SYMBOL);
				break;
			}
		}
	}

	char space[20] = "";
	if (LABY_SIZE_Y > 100)
		strcpy(space, "\n     ");
	else if (LABY_SIZE_Y > 10)
		strcpy(space, "\n    ");
	else
		strcpy(space, "\n   ");

	printf("%s", space);

	//Laby row indicator
	for (i = 0;i < LABY_SIZE_X;i++) {
		printf("| ");
	}

	if (LABY_SIZE_X >= 100) {
		printf("%s", space);
		for (i = 0;i < LABY_SIZE_X;i++) {
			printf("%d ", (int)i%1000/100);
		}
	}
	if (LABY_SIZE_X >= 10) {
		printf("%s", space);
		for (i = 0;i < LABY_SIZE_X;i++) {
			printf("%d ", (int)i%100/10);
		}
	}
	printf("%s", space);
	for (i = 0;i < LABY_SIZE_X;i++) {
		printf("%d ", i%10);
	}
}
