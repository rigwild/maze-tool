#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#include "functions.h"
#include "path.h"
#include "backup.h"
#include "types.h"

void menu()
{
	bool labyInitialised = false;

	bool continuer = true;
	int choixMenu;

	while (continuer) {
		printf("\n\n###################### MENU ######################\n");
		printf("#                                                #\n");
		printf("#  1. Créer un labyrinthe                        #\n");
		printf("#  2. Créer un labyrinthe aléatoire              #\n");
		printf("#  3. Ajouter un mur au labyrinthe               #\n");
		printf("#  4. Afficher le chemin entrée-sortie           #\n");
		printf("#  5. Sauvegarder le labyrinthe dans un fichier  #\n");
		printf("#  6. Charger un labyrinthe depuis un fichier    #\n");
		printf("#  0. Quitter                                    #\n");
		printf("#                                                #\n");
		printf("##################################################\n");

		askInt("-> ", &choixMenu); /* Lecture du choix de l'utilisateur */
		printf("\n\n");

		switch (choixMenu)
		{
			case 1 ://Create laby
			initLaby();
			labyInitialised = true;
			break;

			case 2 ://Create random laby
			initLabyRandom();
			labyInitialised = true;
			break;

			case 3 ://Add a wall
			if (!labyInitialised) {
				printf("\nLe labyrinthe n'est pas initialisé.");
				break;
			}
			askAddWall();
			break;

			case 4 ://Draw entrance-exit path
			if (!labyInitialised) {
				printf("\nLe labyrinthe n'est pas initialisé.");
				break;
			}
			showPath();
			break;

			case 5 ://Save the labyrinth to file
			if (!labyInitialised) {
				printf("\nLe labyrinthe n'est pas initialisé.");
				break;
			}
			saveLaby(LABY_SAVE_FILE);
			printf("\nLe labyrinthe a été sauvegardé dans le fichier %s.\n", LABY_SAVE_FILE);
			break;

			case 6 ://Save labyrinth from file
			loadLaby(LABY_SAVE_FILE);
			printf("\nLe labyrinthe a été chargé depuis le fichier %s.\nVoici le labyrinthe :\n", LABY_SAVE_FILE);
			showLaby();
			labyInitialised = true;
			break;

			case 0 :
			continuer = false;
			break;

			default:
			printf("Choix non reconnu.\n");
			break;
		}
	}
}
