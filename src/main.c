#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <pthread.h>

#include "util.h"							// Serveix per a fer funcionalitats generals. Dedicat a treballar amb strings.
#include "read/easy-read.h"
#include "menu/menu.h"
#include "serialize/serializer.h"
#include "hash/hash.h"
#include "threaded_task/thread_task.h"

int RUNNING = 1;        // Flag per continuar el menu

// Globals
RBTree *tree = NULL;    // Estructura del abre binari.
pthread_mutex_t treeLock;

#define ARG_PERFTEST "-p"
#define ARG_THREADC "-c"
#define ARG_BUFFSIZE "-b"
#define ARG_NUMLINES "-n"
#define ARG_FILE "-f"

int performanceTestMode;
int consumerThreadsCount;
int cBufferSize;
int numLinesRead;

/**
  * Funció per simplificar el codi del main, tot i donar-li tota la funcionalitat.
  * @return Numero de linies que llegir cada vegada
  */
void parseArguments(int argc, char **argv) {
	int ai;

	// Default params
	performanceTestMode = 0;
	consumerThreadsCount = 2;
	cBufferSize = 1000;
	numLinesRead = 1000;
	char* filename = "file.csv";

	// Process all arguments, some with parameters
	for (ai = 1; ai < argc; ai++){
		char* arg = argv[ai];

		if(strcmp(arg, ARG_PERFTEST) == 0){
			performanceTestMode = 1;
			continue;
		}

		if(strcmp(arg, ARG_THREADC) == 0){
			consumerThreadsCount = atoi(argv[ai+1]);
			ai++;
			continue;
		}

		if(strcmp(arg, ARG_BUFFSIZE) == 0){
			cBufferSize = atoi(argv[ai+1]);
			ai++;
			continue;
		}

		if(strcmp(arg, ARG_NUMLINES) == 0){
			numLinesRead = atoi(argv[ai+1]);
			ai++;
			continue;
		}

		if(strcmp(arg, ARG_FILE) == 0){
			filename = argv[ai+1];
			ai++;
			continue;
		}
	}
	// Initialized file for reading
	read_initFile(filename);
}

/******************
 * MENU FUNCTIONS *
 ******************/

void * tt_readLinesProducer () {
 	return read_readLines (numLinesRead);
}

void tt_processLinesConsumer ( void * ptr ){
	char** lines = ptr;

	List** listHashTable = flow_linesIntoHashTable(lines);

	// Insercio a l'arbre binari
	pthread_mutex_lock(&treeLock);
	flow_addHashtableToTree(tree, listHashTable);
	pthread_mutex_unlock(&treeLock);

	// Free memory
	for (int i = 0; i < HASH_SIZE; i++)
		if (listHashTable[i])
			list_delete(listHashTable[i]);
	free(listHashTable);

	return;
}

/** Opcio del menu per llegit el arbre desde un fitxer binari. */
void opt_createTree() {

	if (numLinesRead <= 0) {
		printf("Ha de ser un valor positiu. Heu entrat: %d\n", numLinesRead);
		exit(EXIT_FAILURE);
	}

	// Crear l'arbre de nou
	if (tree) {
		printf("L'arbre ja existeix, es procedirá a destruir-lo\n");
		tree_delete(tree, list_delete);
	}
	tree = tree_new();
	
	// Nou codi
	tt_init(tt_readLinesProducer, tt_processLinesConsumer);
	tt_executeTast( consumerThreadsCount, cBufferSize );
	
	if(tree && !performanceTestMode){
		printf("Arbre creat correctament.\n");
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
	fgets(fileName, 128, stdin);
	fileName[strlen(fileName) - 1] = 0;

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
	fgets(fileName, 128, stdin);
	fileName[strlen(fileName) - 1] = 0;

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
	char *days[] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};

	if (!tree) {
		printf("Crea l'arbre primer.\n");
		return;
	}

	// Llegir origen i desti de Consola
	printf("Aeroport Origen: ");
	fgets(origAir, 16, stdin);
	origAir[strlen(origAir) - 1] = 0;

	printf("Aeroport Desti: ");
	fgets(destAir, 16, stdin);
	destAir[strlen(destAir) - 1] = 0;

	RBData *treeData = tree_findNode(tree, origAir);
	if (!treeData) {
		printf("Origen no trobat.\n");
		return;
	}

	ListData *listData = list_findKey(treeData->list, destAir);
	if (!listData) {
		printf("Destinacio no trobada.\n");
		return;
	}

	printf("Retard Mitg:\n\t%s -> %s\n", origAir, destAir);
	for (int i = 0; i < 7; i++) {
		printf("\t%s: %.2f\n", days[i], (float) listData->total[i] / listData->count[i]);
	}

	// Crear el fitxer temporal i la canonada a GNUPlot
	FILE *temp = fopen("data.tmp", "w");
	FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

	// Escriure les dades, processant nans com a data que no tenim
	for (int i = 0; i < 7; i++) {
		float mean = (float) listData->total[i] / listData->count[i];
		mean = isnan(mean) ? 0 : mean;
		fprintf(temp, "%s %f \n", days[i], mean);
	}
	fclose(temp);

	// Executant les comandes de GNUPlot
	fprintf(gnuplotPipe, "set title \"Retard Mitg entre %s i %s\" \n", origAir, destAir);
	fprintf(gnuplotPipe, "%s \n", "set style data histogram");
	fprintf(gnuplotPipe, "%s \n", "set style fill solid");
	fprintf(gnuplotPipe, "%s \n", "plot \"data.tmp\" using 2:xticlabels(1)");

	pclose(gnuplotPipe);

}

void opt_dumpTree() {
	if (tree) {
		tree_dump(tree);
	}
}

/** Opcio del menu per terminar l'execucio del programa. */
void opt_exitProgram() {
	RUNNING = 0;
}

int main(int argc, char **argv) {
	parseArguments(argc, argv);

	if(performanceTestMode){
		opt_createTree();
		tree_delete(tree, list_delete);
		return EXIT_SUCCESS;
	}

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
//	read_closeFile(); !!!!!!!!!!! és necessari??

	return EXIT_SUCCESS;
}
