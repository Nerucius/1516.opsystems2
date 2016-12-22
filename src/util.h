#ifndef UTIL_H
#define UTIL_H

#include "linked-list/linked-list.h"
#include "rb-tree/red-black-tree.h"

#define CSV_COLS 28        // Nombre de columnes que conte el fitxer CSV.

/**
  * Estructura que ens serveix per a simplificar que retorna
  * el programa read.
  *
  * Es defineix com estatic el tamany maxim de origen i desti per facilitat la localitat de memoria.
  */
typedef struct DataPoint_ {
	int dia;        // Dia, conté valors entre 1 i 7, on 1 és el dilluns i 7 diumenge.
	int retard;        // Els minuts de retard en arribar a destinació.
	char origen[8];    // Origen del vol en IATA
	char desti[8];    // Desti del vol en IATA
} DataPoint;

DataPoint *dataFromColumns(char **elements);

List *flow_inputElementInList(List *list, DataPoint *dataP);

List **flow_linesIntoHashTable(char **lines);

void flow_addHashtableToTree(RBTree *tree, List **listHash);

char *copyMalloc(char *in);

char *encadenar2strings(char *desti, char *text);

void splitLine(char *line, char *v[CSV_COLS], char sep);

#endif
