#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "util.h"							// Serveix per a fer funcionalitats generals. Dedicat a treballar amb strings.
#include "read/easy-read.h"
#include "menu/menu.h"
#include "serialize/serializer.h"


int RUNNING = 1;        // Flag per continuar el menu
// Globals
RBTree *tree = NULL;    // Estructura del abre binari.
int readBlockSize;      // Nombre de línies en que llegirà el fitxer. (primer apartat de la pràctica 2).


/**
  * Funció per simplificar el codi del main, tot i donar-li tota la funcionalitat.
  * @return Numero de linies que llegir cada vegada
  */
int parseArgument(int argc, char **argv) {
	switch (argc) {
		case 1: // Quan no indica res, per defecte.
			read_initFile("file.csv");
			break;
		case 2: // Si posa una entrada,
			if (isdigit (argv[1][0])) { // i es digit, llegira en base el dígit.
				argc = atoi(argv[1]);
				if (!argc) {
					printf("S'ha de llegir un nombre de línies.\n");
					printf("Ha entrat: %d\n", argc);
					exit(7);
				}
				// Posem el read al final, per evitar problemes. Ja que si entres un zero donaria un alloc.
				read_initFile("file.csv");
				return argc;
			} // Sino, llegira el fitxer indicat.
			read_initFile(argv[1]);
			break;
		case 3: // Cas de posar 2 entrades, la primera sera per llegir, el segon les línies.
			read_initFile(argv[1]);
			return atoi(argv[2]);
		default: // Altres casos (+2) enviara un missatge d'error.
			printf("Usage: [nameFile [lines]]\n");
			exit(1);
	}
	return 1000;
}


// MENU FUNCTIONS
void opt_createTree() {
	int lineCount;            // Tamany real llegit i per a saber si continuar dins del bucle.
	char **linesRead;        // Llista on hi ha les N línies llegides.
	List **listHash;        // Array de llistes amb el format del hash.

	if (readBlockSize <= 0) {
		printf("Ha de ser un valor positiu. Heu entrat: %d\n", readBlockSize);
		exit(EXIT_FAILURE);
	}

	// Crear l'arbre de nou
	if (tree) {
		printf("L'arbre ja existeix, es procedirá a destruir-lo\n");
		tree_delete(tree, list_delete);
	}
	tree = tree_new();

	// Mentres hi hagi línies per llegir.
	while (1) {
		// Lectura en blocks de N lines o menys
		linesRead = read_readLines(readBlockSize, &lineCount);

		// Si no s'han llegit mes linies, sortir del bucle
		if (!lineCount)
			break;

		// Segon apartat de l'enunciat: Incerció de dades a la taula hash.
		//printf("Putting %d lines into hash\n", lineCount);
		listHash = flow_linesIntoHashTable(linesRead, lineCount);

		//printf ( "%s\n", read[--size]);

		// Insercio a l'arbre binari
		flow_addHashtableToTree(tree, listHash);

		// Lliberar memoria de la taula Hash
//		for (int i = 0; i < HASH_SIZE; i++)
//			if (listHash[i]) list_delete(listHash[i]);
		free(listHash);
	}

//	for (int i = 0; i < HASH_SIZE; i++) {
//		if (listHash[i]) {
//			printf("%3d: %s\n", i, listHash[i]->first->data->key_sec);
//			list_dump(listHash[i]);
//		}
//	}
}

void opt_saveTreeToFile() {
	if (!tree) {
		printf("Crea l'arbre primer\n");
		return;
	}

	FILE *fp = fopen("write.txt", "w");
	ser_writeTree(tree, fp);
	fclose(fp);
}

void opt_readTreeFromFile() {
	FILE *fp = fopen("write.txt", "r");
	if (!fp) {
		printf("No s'ha trobat el fitxer\n");
		return;
	}

	if(tree){
		tree_delete(tree, list_delete);
	}

	tree = ser_readTree(fp);
	fclose(fp);
}

void opt_showGraph() {
	// TODO Pipe data to GNUPlot
}

void opt_dumpTree(){
	if(tree){
		tree_dump(tree);
	}
}

void opt_exitProgram() {
	RUNNING = 0;
}

int main(int argc, char **argv) {
	readBlockSize = parseArgument(argc, argv);

	// Crear el menu i els seus items.
	Menu *menu = menu_new("Menu de l'Aplicacio");
	menu_addItem(menu, "Crear arbre a partit de Dades.", opt_createTree);
	menu_addItem(menu, "Emmagatzemar arbre a fitxer.", opt_saveTreeToFile);
	menu_addItem(menu, "Llegir arbre desde fitxer.", opt_readTreeFromFile);
	menu_addItem(menu, "Mostrar Grafica de retards.", opt_showGraph);
	menu_addItem(menu, "Mostrar estructura del Arbre.", opt_dumpTree);
	menu_addItem(menu, "Sortir del programa.", opt_exitProgram);

	while (RUNNING)
		menu_show(menu);

	// Alliberar memoria de les estructures
	menu_delete(menu);
	if (tree != NULL) tree_delete(tree, list_delete);

	return EXIT_SUCCESS;
}
