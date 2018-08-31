#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "functions.h"
#include "types.h"

//Initializing the laby array
void initArray()
{
	int i;
	laby = (labyCase **) malloc(LABY_SIZE_X*sizeof(labyCase *));
	for(i=0;i < LABY_SIZE_X;i++)
		laby[i] = (labyCase *) malloc(LABY_SIZE_Y*sizeof(labyCase));

	int k = 0;
	int l = 0;
	for (k = 0; k < LABY_SIZE_X; k++) {
		for (l = 0; l < LABY_SIZE_Y; l++) {
			laby[k][l].value = LABY_EMPTY_INT;
			laby[k][l].parent_x = -1;
			laby[k][l].parent_y = -1;
		}
	}
}

//Ask the maze's settings to the user and create it
void initLaby()
{
	askInt("Entrez la taille horizontale du labyrinthe (Taille en X) : ", &LABY_SIZE_X);
	while (LABY_SIZE_X > LABY_MAX_SIZE) {
		printf("\nTaille incorrecte. Taille maximale définie dans LABY_MAX_SIZE : %d\n", LABY_MAX_SIZE);
		askInt("Entrez la taille horizontale du labyrinthe (Taille en X) : ", &LABY_SIZE_X);
	}

	askInt("Entrez la taille verticale du labyrinthe (Taille en Y) : ", &LABY_SIZE_Y);
	while (LABY_SIZE_Y > LABY_MAX_SIZE) {
		printf("\nTaille incorrecte. Taille maximale définie dans LABY_MAX_SIZE : %d\n", LABY_MAX_SIZE);
		askInt("Entrez la taille verticale du labyrinthe (Taille en Y) : ", &LABY_SIZE_Y);
	}

	initArray();
	showLaby();
	askLabyEntranceExit();
}

//Generate a random sized maze
void initLabyRandom()
{
	//Generate random size
	srand(time(NULL)); //Reset randomness seed with local time, so you don't get a pseudo-random maze

	LABY_SIZE_X = rand() % LABY_MAX_SIZE + 1;
	LABY_SIZE_Y = rand() % LABY_MAX_SIZE + 1;

	printf("Génération d'un labyrinthe aléatoire de taille %dx%d. Veuillez patienter, cela peut prendre un moment...\n", LABY_SIZE_X, LABY_SIZE_Y);

	initArray();

	//We set entrance and exit in the opposite corners
	LABY_ENTRANCE_x = 0;
	LABY_ENTRANCE_y = 0;

	LABY_EXIT_x = LABY_SIZE_X-1;
	LABY_EXIT_y = LABY_SIZE_Y-1;

	laby[LABY_ENTRANCE_x][LABY_ENTRANCE_y].value = LABY_ENTRANCE_INT;
	laby[LABY_EXIT_x][LABY_EXIT_y].value = LABY_EXIT_INT;

	int i, j, random;

	//Generate walls
	for (i = 0;i < LABY_SIZE_X;i++) {
		for (j = 0;j < LABY_SIZE_Y;j++) {
			//We check there's no walls around the entrance or exit (makes the path algorithm bug otherwise
			//and don't really know why it happens!)
			if (!((i == LABY_ENTRANCE_x && j == LABY_ENTRANCE_x+1) || (i == LABY_ENTRANCE_x+1 && j == LABY_ENTRANCE_x)
				|| (i == LABY_EXIT_x && j == LABY_EXIT_x-1) || (i == LABY_EXIT_x-1 && j == LABY_EXIT_x)))
			{
				random = rand() % 2; //1 on 2 chances
				if (random == 1 && laby[i][j].value == LABY_EMPTY_INT && !isWallBlockingPath(i, j))
					laby[i][j].value = LABY_WALL_INT;
			}
		}
	}
	showLaby();
}

//Ask the user where to place maze's entrance and exit
void askLabyEntranceExit()
{
	int x, y;
	printf("\n\nVoici le labyrinthe. Veuillez indiquer l'entrée et la sortie.\nLes coordonnées entrées doivent se situer dans le contour du labyrinthe.");
	printf("\n\nEntrez les coordonnées de l'entrée :\n");
	askInt("Entrez x : ", &x);
	askInt("Entrez y : ", &y);
	while(!isInLabyOutLine(x, y) || !setContent(x, y, LABY_ENTRANCE_INT)) {
		printf("\nLa case sélectionnée n'est pas dans le contour du labyrinthe ou est déjà occupée. Veuillez réessayer.\n");
		askInt("Entrez x : ", &x);
		askInt("Entrez y : ", &y);
	}
	printf("\nL'entrée a bien été positionné en (%d, %d).\n", x, y);
	LABY_ENTRANCE_x = x;
	LABY_ENTRANCE_y = y;

	printf("\n\nEntrez les coordonnées de la sortie :\n");
	askInt("Entrez x : ", &x);
	askInt("Entrez y : ", &y);
	while(!isInLabyOutLine(x, y) || !setContent(x, y, LABY_EXIT_INT)) {
		printf("\nLa case sélectionnée n'est pas dans le contour du labyrinthe ou est déjà occupée. Veuillez réessayer.\n");
		askInt("Entrez x : ", &x);
		askInt("Entrez y : ", &y);
	}
	printf("\nLa sortie a bien été positionnée en (%d, %d).\n", x, y);
	LABY_EXIT_x = x;
	LABY_EXIT_y = y;

	showLaby();
}

//Print the maze to the console
void showLaby()
{
	int i, j;

	printf("\nCase vide : %s # Entrée : %s # Sortie : %s # Mur : %s\n", LABY_EMPTY_SYMBOL, LABY_ENTRANCE_SYMBOL, LABY_EXIT_SYMBOL, LABY_WALL_SYMBOL);

	for (j = LABY_SIZE_Y-1;j >= 0;j--) {
		//Laby line indicator
		if (LABY_SIZE_Y > 100)
			printf("\n%03d--", j);
		else if (LABY_SIZE_Y > 10)
			printf("\n%02d--", j);
		else
			printf("\n%d--", j);

		for (i = 0;i < LABY_SIZE_X;i++) {
			switch (laby[i][j].value) {
				case LABY_ENTRANCE_INT:
				printf("%s ", LABY_ENTRANCE_SYMBOL);
				break;
				case LABY_EXIT_INT:
				printf("%s ", LABY_EXIT_SYMBOL);
				break;
				case LABY_WALL_INT:
				printf("%s ", LABY_WALL_SYMBOL);
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

//Check if coordinate is in the maze's bounds
bool isInBound(int x, int y)
{
	return (!(x > LABY_SIZE_X-1 || y > LABY_SIZE_Y-1 || x < 0 || y < 0));
}

//Check if coordinate is in the maze's outline
bool isInLabyOutLine(int x, int y)
{
	return (isInBound(x, y) && (x == 0 || y == 0 || x == LABY_SIZE_X-1 || y == LABY_SIZE_Y-1));
}

//Set the given coordinates to the asked value, cancel if out of bounds
bool setContent(int x, int y, int value)
{
	if (isInBound(x, y) && laby[x][y].value == LABY_EMPTY_INT) {
		laby[x][y].value = value;
		return true;
	}
	return false;
}

//Ask safely an int to the user
int askInt(char* message, int* x)
{
	printf("%s", message);
	fflush(stdin);

	char buffer[10];
	fgets(buffer, sizeof buffer, stdin);
	while (sscanf(buffer, "%d", x) != 1) {
		printf("\nEntrée invalide. Un nombre est attendu.\n");
		printf("%s", message);
		fgets(buffer, sizeof buffer, stdin);
	}
	return *x;
}

//Ask the user where to place the wall, check if possible before applying
void askAddWall()
{
	int x, y;
	showLaby();
	printf("\n\nVoici le labyrinthe. Saisissez les coordonnées où placer le mur.\n");
	askInt("Entrez x : ", &x);
	askInt("Entrez y : ", &y);
	bool continuer = true;
	bool continuerCheck;
	while(continuer) {
		continuerCheck = true;
		if (!isInBound(x, y)) {
			printf("\nLa case sélectionnée est en dehors du labyrinthe. Veuillez réessayer.\n");
			continuerCheck = false;
		}
		if (continuerCheck && laby[x][y].value != LABY_EMPTY_INT) {
			printf("\nLa case sélectionnée n'est pas vide. Veuillez réessayer.\n");
			continuerCheck = false;
		}
		if (continuerCheck && isWallBlockingPath(x, y)) {
			printf("\nLa case sélectionnée bloque le chemin de l'entrée vers la sortie. Veuillez réessayer.\n");
			continuerCheck = false;
		}
		if (continuerCheck)
		{
			setContent(x, y, LABY_WALL_INT);
			continuer = false;
		}
		else {
			askInt("Entrez x : ", &x);
			askInt("Entrez y : ", &y);
		}
	}
	showLaby();
	printf("\n\nLe mur a bien été positionné en (%d, %d).\n", x, y);
}

//Check if placing a wall at these coordinates would block the path from the maze's entrance to exit
bool isWallBlockingPath(int Wx, int Wy)
{
	//Temporarly adding a wall
	laby[Wx][Wy].value = LABY_WALL_INT;

	//Allocating memory for searching the path from entrance to exit
	coord *labySearchPathList = malloc(LABY_SIZE_X*LABY_SIZE_Y*sizeof(coord *)*2);
	//coord labySearchPathList[50000];

	coord tempCoord;

	int i = 0;
	bool continuer = true;
	labySearchPathList[0].x = LABY_ENTRANCE_x;
	labySearchPathList[0].y = LABY_ENTRANCE_y;
	int arraySize = 1;
	while (continuer && i < arraySize) {
        //printf("\ntest de : (%d, %d)", labySearchPathList[i].x, labySearchPathList[i].y);

        //printf("gauche : ");
		tempCoord.x = labySearchPathList[i].x-1;
		tempCoord.y = labySearchPathList[i].y;
		if (isInBound(tempCoord.x, tempCoord.y) && !isAlreadyInArray(labySearchPathList, tempCoord, arraySize)) {//left
			if (laby[tempCoord.x][tempCoord.y].value == LABY_EMPTY_INT || (tempCoord.x == LABY_EXIT_x && tempCoord.y == LABY_EXIT_y))
			{
				laby[tempCoord.x][tempCoord.y].parent_x = labySearchPathList[i].x;
				laby[tempCoord.x][tempCoord.y].parent_y = labySearchPathList[i].y;
				if (tempCoord.x == LABY_EXIT_x && tempCoord.y == LABY_EXIT_y) {
					laby[Wx][Wy].value = LABY_EMPTY_INT;
					//printf("\n SORTIE TROUVEE !! en : %d, %d", tempCoord.x, tempCoord.y);
					return false; //Found exit
				}
				labySearchPathList[arraySize].x = tempCoord.x;
				labySearchPathList[arraySize].y = tempCoord.y;
				arraySize++;
			}
		}

		//printf("droite : ");
		tempCoord.x = labySearchPathList[i].x+1;
		tempCoord.y = labySearchPathList[i].y;
		if (isInBound(tempCoord.x, tempCoord.y) && !isAlreadyInArray(labySearchPathList, tempCoord, arraySize)) {//right
			if (laby[tempCoord.x][tempCoord.y].value == LABY_EMPTY_INT || (tempCoord.x == LABY_EXIT_x && tempCoord.y == LABY_EXIT_y))
			{
				laby[tempCoord.x][tempCoord.y].parent_x = labySearchPathList[i].x;
				laby[tempCoord.x][tempCoord.y].parent_y = labySearchPathList[i].y;
				if (tempCoord.x == LABY_EXIT_x && tempCoord.y == LABY_EXIT_y) {
					laby[Wx][Wy].value = LABY_EMPTY_INT;
					//printf("\n SORTIE TROUVEE !! en : %d, %d", tempCoord.x, tempCoord.y);
					return false; //Found exit
				}
				labySearchPathList[arraySize].x = tempCoord.x;
				labySearchPathList[arraySize].y = tempCoord.y;
				arraySize++;
			}
		}

		//printf("haut : ");
		tempCoord.x = labySearchPathList[i].x;
		tempCoord.y = labySearchPathList[i].y+1;
		if (isInBound(tempCoord.x, tempCoord.y) && !isAlreadyInArray(labySearchPathList, tempCoord, arraySize)) {//top
			if (laby[tempCoord.x][tempCoord.y].value == LABY_EMPTY_INT || (tempCoord.x == LABY_EXIT_x && tempCoord.y == LABY_EXIT_y))
			{
				laby[tempCoord.x][tempCoord.y].parent_x = labySearchPathList[i].x;
				laby[tempCoord.x][tempCoord.y].parent_y = labySearchPathList[i].y;
				if (tempCoord.x == LABY_EXIT_x && tempCoord.y == LABY_EXIT_y) {
					laby[Wx][Wy].value = LABY_EMPTY_INT;
					//printf("\n SORTIE TROUVEE !! en : %d, %d", tempCoord.x, tempCoord.y);
					return false; //Found exit
				}
				labySearchPathList[arraySize].x = tempCoord.x;
				labySearchPathList[arraySize].y = tempCoord.y;
				arraySize++;
			}
		}

		//printf("bas : ");
		tempCoord.x = labySearchPathList[i].x;
		tempCoord.y = labySearchPathList[i].y-1;
		if (isInBound(tempCoord.x, tempCoord.y) && !isAlreadyInArray(labySearchPathList, tempCoord, arraySize)) {//bottom
			if (laby[tempCoord.x][tempCoord.y].value == LABY_EMPTY_INT || (tempCoord.x == LABY_EXIT_x && tempCoord.y == LABY_EXIT_y))
			{
				laby[tempCoord.x][tempCoord.y].parent_x = labySearchPathList[i].x;
				laby[tempCoord.x][tempCoord.y].parent_y = labySearchPathList[i].y;
				if (tempCoord.x == LABY_EXIT_x && tempCoord.y == LABY_EXIT_y) {
					laby[Wx][Wy].value = LABY_EMPTY_INT;
					//printf("\n SORTIE TROUVEE !! en : %d, %d", tempCoord.x, tempCoord.y);
					return false; //Found exit
				}
				labySearchPathList[arraySize].x = tempCoord.x;
				labySearchPathList[arraySize].y = tempCoord.y;
				arraySize++;
			}
		}

		i++;
	}

	//freeing memory
	free(labySearchPathList);
	//remove the wall previously set
	laby[Wx][Wy].value = LABY_EMPTY_INT;

	return true;
}

//Check if the given coordinate is already stacked
bool isAlreadyInArray(coord *labySearchPathList, coord c, int arraySize)
{
	int i = 0;
	while (i < arraySize)
	{
		if (labySearchPathList[i].x == c.x && labySearchPathList[i].y == c.y) {
			//printf(" Trouvé ! ");
			return true;
		}
		i++;
	}
	return false;
}