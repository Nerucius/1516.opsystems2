#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "def.h"							// Defineix el node
#include "util.h"							// Serveix per a fer funcionalitats generals. Dedicat a treballar amb strings.
#include "hash/hash.h"						// Té una funció per a poder treballar amb la hash table.
#include "llegir-csv/easyRead.h"			// Llegeix el fitxer indicat.
#include "linked-list/linked-list.h"		// Té la funcionalitat bàsica d'una llista.
#include "arbre-binari/red-black-tree.h"	// Té la funcionalitat bàsica d'un abre binari.
#include "menu/menu.h"
#include "serialize/serializer.h"

int RUNNING = 1;        // Flag per continuar el menu

// Globals
RBTree *tree = NULL;    // Estructura del abre binari.
int readBlockSize;        // Nombre de línies en que llegirà el fitxer. (primer apartat de la pràctica 2).


/**
  * Funció per simplificar el codi del main, tot i donar-li tota la funcionalitat.
  */
int parseArgument(int argc, char **argv) {
	switch (argc) {
		case 1: // Quan no indica res, per defecte.
			readInitFile("file.csv");
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
				readInitFile("file.csv");
				return argc;
			} // Sino, llegira el fitxer indicat.
			readInitFile(argv[1]);
			break;
		case 3: // Cas de posar 2 entrades, la primera sera per llegir, el segon les línies.
			readInitFile(argv[1]);
			return atoi(argv[2]);
		default: // Altres casos (+2) enviara un missatge d'error.
			printf("Usage: [nameFile [lines]]\n");
			exit(1);
	}
	return 1000;
}

/**
  * A partir d'una llista de strings, extreiem les columnes que ens interessen.
  */
DataNode createNode(char **elements) {
	DataNode n;
	char **p = elements - 1;

	n.dia = atoi(p[4]);    // Afegeix la informació del dia.
	n.retard = atoi(p[15]);    // Afegeix la informació del retard.
	n.origen = copyMalloc(p[17]);    // Diu d'on surt l'avio.
	n.desti = copyMalloc(p[18]); // Diu on arriva l'avio.
	//printf ("or: %s\tde: %s\tdi: %d\tre: %d\n", n.origen, n.desti, n.dia, n.retard);
	return n;
}

/**
  * Funció especialitzada en afegir un element dins la llista.
  *
  * Amb entrada, la clau, per a diferenciar-se entre els seus elements.
  * Amb el seu contingut, que aquí són el dia i retard.
  */
List *inputElementInList(List *list, char *key, DataNode *node) {
	ListData *ld;

	// En cas que no existeixi la llista.
	if (!list)
		list = createList();

	// Search if the key is in the list
	ld = findList(list, key);

	// Toca alliverar la memòria exedent.
	if (ld) {
		free(key);
		free(node->origen);
		free(node->desti);
		free(node);
	} else { // Toca generar un ListData.
		ld = (ListData *) malloc(sizeof(ListData));

		// Definim la clau.
		ld->key = key;

		// Ens assegurem inicialitzar els valors a zero (calloc).
		ld->count = (int *) calloc(7, sizeof(int)); // Contador de vegades.
		ld->total = (int *) calloc(7, sizeof(int)); // Total del retard.
		ld->node = (void *) node;

		// Afegim la data dins de la llista.
		insertList(list, ld);
	}

	// Actualitzem la informació.
	ld->count[node->dia - 1]++;
	ld->total[node->dia - 1] += node->retard;
	return list;
}

/**
  * Funció per afegir elements en la llista.
  *
  * Amb entrada, la clau per a diferenciar-se.
  * També amb les llistes del seu contingut.
  */
void inputElementsInList(List *list, char *key, int *dia, int *retard) {
	int i;
	ListData *ld;

	/* Search if the key is in the tree */
	ld = findList(list, key);

	if (!ld) {
		ld = malloc(sizeof(ListData));

		// Clau.
		ld->key = copyMalloc(key);

		// Contingut.
		// Ens assegurem inicialitzar els valors a zero (calloc).
		ld->count = (int *) calloc(7, sizeof(int)); // Contador de vegades.
		ld->total = (int *) calloc(7, sizeof(int)); // Total del retard.

		// Insertem el listData.
		insertList(list, ld);
	}

	// Actualitzem la informació.
	for (i = 6; i--;) {
		ld->count[i] += dia[i];
		ld->total[i] += retard[i];
	}
}


/**
  * 2n apartat de l'enunciat de la pràctica 2.
  * Fet tot això en una sola funció per l'enunciat de la pràctica 2.
  *
  * Encarregat de: - traduir el text - fer un hash - omplir la taula amb llistes -
  *
  * Retorna una llista de List.
  */
List **linesIntoHashTable(char **lines, int count) {
	int i;            // Pel loop.
	List **hashTable;    // La llista a retornar.
	int hash;        // La clau hash.
	char *splits[CSV_COLS];    // El separador CSV per columnes.
	char *listKey;        // La clau que farem anar per la llista.
	DataNode node, *nodePointer;// Node on enmagatzem la informació necessaria.
	// Ens assegurem que tot està a zero, per evitar confucions d'interpretar llistes que no existeixen.
	hashTable = calloc(HASH_SIZE, sizeof(List *));
//printf ("Has: %p\t", hashTable );

	// Recorrem totes les línies entrades.
	for (i = 0; i < count; i++) {
		// Split the line
		splitLine(lines[i], splits, ',');

		// Generem la informació un cop fet l'esplit.
		node = createNode(splits);
		free(lines[i]);    // Alliberem l'estring usat. No ho podem fer abans, ja que fem anar splits.

		// Ens assegurem que origen no és diferent de 3. (enunciat pràctica 1)
		if (strlen(node.origen) != 3) { // Ens toca alliberar la memòria.
			free(node.origen);
			free(node.desti);
			continue;
		}

		// Fem anar la funció hash.
		hash = hashCode(node.origen);

		// Redefinim listKey, ja que el canviarem de tamany. +4 = 3 origen + 1 del zero final.
		listKey = encadenar2strings(node.origen, node.desti);

		// Afegim un element a la llista.
		nodePointer = malloc(sizeof(DataNode));
		*nodePointer = node;
		hashTable[hash] = inputElementInList(hashTable[hash], listKey, nodePointer);
	}

	free(lines); // Alliberem la llista d'estrings.
	return hashTable;
}

void addListIntoTree(RBTree *tree, List **listHash) {
	ListItem *current;
	ListData *listData;    // Simplifica el codi.
	List *listH, *listT;    // Simplifica el codi.
	RBData *treeData;    // Node del abre, per a poder treballar comodament
	int i = HASH_SIZE;    // Comptador, per a recorre tota la llista hash.
	char *origen;        // Origen del vol.
	char *desti;        // Desti del vol.
	char tmp;        // Fet per treure els 2 strings.

	while (i--) {
		listH = listHash[i];
		// Ens asegurem que hi ha algun element.
		if (!listH) continue;

		// Recorrem tots els elements de la llista.
		current = listH->first;
		while (current) {
			listData = current->data;
			origen = listData->key;
			desti = origen + 3;

			// Simulem l'origen.
			tmp = *desti;
			*desti = '\0';

			treeData = findNode(tree, origen);

			if (!treeData) {
				// Reservem memòria per el nou node del abre.
				treeData = (RBData *) malloc(sizeof(RBData));

				// Clau.
				treeData->key = copyMalloc(origen);

				// Contingut.
				listT = createList();
				treeData->data = listT;

				// Afegim el node al abre.
				insertNode(tree, treeData);
			}

			// Recuperem el desti.
			*desti = tmp;

			// Afegim l'informació a list.
			inputElementsInList(treeData->data, desti, listData->count, listData->total);

			// Seleccionem el seguent element.
			current = current->next;

		}
		// Alliberem la memòria de la llista extreta de la taula hash.
		deleteList(listH);

	}
	// Alliberem la taula hash, ja que em extret tota la seva informació.
	free(listHash);
}

// MENU FUNCTIONS
void opt_createTree() {
	int size;        // Tamany real llegit i per a saber si continuar dins del bucle.
	char **linesRead;    // Llista on hi ha les N línies llegides.
	List **listHash;    // Array de llistes amb el format del hash.
	// Hem fet tot el control del main inicial en una funció externa. Per fer-ho visualment més agradable.

	if (readBlockSize <= 0) {
		printf("Ha de ser un valor positiu. Heu entrat: %d\n", readBlockSize);
		exit(3);
	}

	/* Allocate memory for tree and Initialize the tree */
	tree = createTree();

	// M'entres hi hagi línies per a llegir.
	while (1) {
		// Primer apartat de l'enunciat: Lectura de N línies del fitxer.
		linesRead = readLines(readBlockSize, &size);

		// Si el tamany és zero, ni ens esforçem a continuar, sortim directament.
		if (!size)
			break;

		// Segon apartat de l'enunciat: Incerció de dades a la taula hash.
		listHash = linesIntoHashTable(linesRead, size);
		//printf ( "%s\n", read[--size]);

		// Per acabar el segon enunciat: Inserció de dades a l'abre binari.
		addListIntoTree(tree, listHash);
	}
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

	tree = ser_readTree(fp);
	fclose(fp);
}

void opt_showGraph() {
	// TODO Pipe data to GNUPlot
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
	menu_addItem(menu, "Sortir del programa.", opt_exitProgram);

	while (RUNNING)
		menu_show(menu);

	// Alliberar memoria de les estructures
	menu_delete(menu);
	if (tree != NULL) deleteTree(tree, deleteList);
}
