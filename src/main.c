#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"							// Serveix per a fer funcionalitats generals. Dedicat a treballar amb strings.
#include "read/easy-read.h"
#include "menu/menu.h"
#include "serialize/serializer.h"
#include <ctype.h>

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
			if (isdigit(argv[1][0])) { // i es digit, llegira en base el dígit.
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

/******************
 * MENU FUNCTIONS *
 ******************/

/** Opcio del menu per llegit el arbre desde un fitxer binari. */
void opt_createTree() {
	int lineCount;            // Tamany real llegit i per a saber si continuar dins del bucle.
	char **linesRead;        // Llista on hi ha les N línies llegides.
	List **listHashTable;        // Array de llistes amb el format del hash.

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

		// Inserció de dades a la taula hash.
		listHashTable = flow_linesIntoHashTable(linesRead, lineCount);

		// Insercio a l'arbre binari
		flow_addHashtableToTree(tree, listHashTable);

		free(listHashTable);
	}
}

/** Opcio del menu per escriure l'arbre a un fitxer binari. */
void opt_saveTreeToFile() {
	char fileName[128];
	FILE *fp;

	if (!tree) {
		printf("Crea l'arbre primer\n");
		return;
	}

	printf("Nom del fitxer on guardar: ");
	gets(fileName);

	printf("Guardant l'arbre a %s...\n", fileName);

	fp = fopen(fileName, "w");
	ser_writeTree(tree, fp);
	fclose(fp);

	printf("Guardat correctament.\n");
}

/** Opcio del menu per llegit el arbre desde un fitxer binari. */
void opt_readTreeFromFile() {
	char fileName[128];
	FILE *fp;

	if (tree) {
		tree_delete(tree, list_delete);
		tree = NULL;
	}

	printf("Nom del fitxer des d'on cargar: ");
	gets(fileName);

	fp = fopen(fileName, "r");
	if (!fp) {
		printf("No s'ha trobat el fitxer\n");
		return;
	}
	tree = ser_readTree(fp);
	fclose(fp);

	if (tree)
		printf("Arbre carregat desde memoria correctament.\n");
}

/** Opcio del menu per mostrar una grafica de retards entre dos aeroports. */
void opt_showGraph() {
	char origAir[16];
	char destAir[16];

	if (!tree) {
		printf("Crea l'arbre primer.\n");
		return;
	}

	printf("Origin: ");
	gets(origAir);
	printf("Destination: ");
	gets(destAir);

	RBData* treeData = tree_findNode(tree, origAir);
	if(!treeData){
		printf("Origen no trobat.\n");
		return;
	}

	ListData* listData = list_findKey(treeData->list, destAir);
	if(!listData){
		printf("Destinacio no trobada.\n");
		return;
	}

	printf("Retard Mitg: %s -> %s\n", origAir, destAir);
	for(int i = 0; i < 7; i++){
		printf("\t\tDay %d: %.2f\n", i+1, (float)listData->total[i]/listData->count[i]);
	}

	// TODO Pipe data to GNUPlot
}

void opt_dumpTree() {
	if (tree) {
		tree_dump(tree);
	}
}

void opt_DEBUG() {
	RBData *tdata = tree_findNode(tree, "IND");

	if (tdata) {
		printf("\n%s", tdata->key);
		List *list = tdata->list;
		printf("\n num: %d", list->numItems);
	} else
		printf("\n No key found");
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
//	menu_addItem(menu, "RUN DEBUG CODE.", opt_DEBUG);
	menu_addItem(menu, "Sortir del programa.", opt_exitProgram);

	while (RUNNING)
		menu_show(menu);

	// Alliberar memoria de les estructures
	menu_delete(menu);
	if (tree != NULL) tree_delete(tree, list_delete);

	return EXIT_SUCCESS;
}
