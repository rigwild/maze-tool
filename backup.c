#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "types.h"

//Save the maze in a file
void saveLaby(char* filePath)
{
	FILE * fp;
	fp = fopen (filePath, "w");
	fprintf(fp, "%d %d\n", LABY_SIZE_X, LABY_SIZE_Y);
	int i, j;
	for (j = LABY_SIZE_Y-1;j >= 0;j--) {
		for (i = 0;i < LABY_SIZE_X;i++) {
			fprintf(fp, "%d ", laby[i][j].value);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

//Load the maze from a file
void loadLaby(char* filePath)
{
	FILE * fp;
	fp = fopen (filePath, "r");
	fscanf(fp, "%d %d\n", &LABY_SIZE_X, &LABY_SIZE_Y);
	initArray();

	int i, j;
	for (j = LABY_SIZE_Y-1;j >= 0;j--) {
		for (i = 0;i < LABY_SIZE_X;i++) {
			fscanf(fp, "%d ", &laby[i][j].value);
			if (laby[i][j].value == LABY_ENTRANCE_INT)
			{
				LABY_ENTRANCE_x = i;
				LABY_ENTRANCE_y = j;
			}
			else if (laby[i][j].value == LABY_EXIT_INT)
			{
				LABY_EXIT_x = i;
				LABY_EXIT_y = j;
			}
		}
		fscanf(fp, "\n");
	}
	fclose(fp);
}