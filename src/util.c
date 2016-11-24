#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "hash/hash.h"

/**
  * A partir d'una llista de strings, extreiem les columnes que ens interessen.
  * @return Punter a un nou DataPoint amb la informacio
  */
DataPoint *dataFromColumns(char **elements) {
	DataPoint *dp = calloc(1, sizeof(DataPoint));
	char **p = elements - 1; // Apunta a la posició -1 de la llista per usar els numeros de columna naturals

	dp->dia = atoi(p[4]);                // Afegeix la informació del dia.
	dp->retard = atoi(p[15]);            // Afegeix la informació del retard.
	strcpy(dp->origen, p[17]);
	strcpy(dp->desti, p[18]);
//	dp.origen = copyMalloc(p[17]);		// Diu d'on surt l'avio.
//	dp.desti = copyMalloc(p[18]);		// Diu on arriva l'avio.
	//printf ("or: %s\tde: %s\tdi: %d\tre: %d\n", n.origen, n.desti, n.dia, n.retard);
	return dp;
}

/**
  * Funció especialitzada en afegir un element dins una llista enllaçada.
  * Fa servir dos claus per la llista, Desti i Origen com secundaria, ja que hi pot haver hash-collisions.
  *
  * @param list llista linkada a on buscar i inserir
  * @param dataP Nova informació a inserir
  *
  * @return pointer to List
  */
List *flow_inputElementInList(List *list, DataPoint *dataP) {
	ListData *ldata;

	// En cas que no existeixi la llista.
	if (!list) list = list_new();

	// Buscar si la clau ja existeix a la llista
	ldata = list_find2Keys(list, dataP->desti, dataP->origen);

	if (!ldata) {
		// Si no existeix, creem un nou ListData
		// Toca generar un ListData.
		ldata = (ListData *) malloc(sizeof(ListData));

		// Definim les dos claus
		ldata->key = calloc(sizeof(char), 8);
		strcpy(ldata->key, dataP->desti);

		ldata->key_sec = calloc(sizeof(char), 8);
		strcpy(ldata->key_sec, dataP->origen);

		// Inicialitzem els arrays a 0
		memset(ldata->count, 0, sizeof(int) * 7);
		memset(ldata->total, 0, sizeof(int) * 7);

		// Afegim la data dins de la llista.
		list_insertData(list, ldata);
	}

	// Actualitzem la informació.
	ldata->count[dataP->dia - 1]++;
	ldata->total[dataP->dia - 1] += dataP->retard;

	return list;
}

/**
  * 2n apartat de l'enunciat de la pràctica 2.
  * Fet tot això en una sola funció per l'enunciat de la pràctica 2.
  *
  * Encarregat de: - traduir el text - fer un hash - omplir la taula amb llistes -
  *
  * Retorna una llista de List.
  */
List **flow_linesIntoHashTable(char **lines, int count) {
	int i;                    // Pel loop.
	List **hashTable;        // La llista a retornar.
	int hash;                // La clau hash.
	char *splits[CSV_COLS];    // El separador CSV per columnes.
	DataPoint *dataP;        // Node on enmagatzem la informació necessaria.

	// Ens assegurem que tot està a zero, per evitar confucions d'interpretar llistes que no existeixen.
	hashTable = calloc(HASH_SIZE, sizeof(List *));

	// Recorrem totes les línies entrades.
	for (i = 0; i < count; i++) {

		// Parteix linea en columnes i despres extreu les dades que ens preocupen
		splitLine(lines[i], splits, ',');
		dataP = dataFromColumns(splits);

		// Un cop copiades les dades, alliberem la linea
		free(lines[i]);

		// Si origen es diferent de 3, ignorem la entrada.
		if (strlen(dataP->origen) != 3) {
			free(dataP);
			continue;
		}

		// Fem anar la funció hash.
		hash = hashCode(dataP->origen);

		// Afegim element per element a la llista on ha caigut el Hash
		hashTable[hash] = flow_inputElementInList(hashTable[hash], dataP);
		free(dataP);
	}

	free(lines); // Alliberem el punter a la llista de Strings
	return hashTable;
}

void flow_addHashtableToTree(RBTree *tree, List **listHash) {
	ListItem *hashListItem;
	List *linkedList;            // Lista linkada dins de RBData
	ListData *hashListData;    // Data dins de la lista
	ListData *treeListData;        // Data dins del node del arbre
	RBData *tdata;

	int i = HASH_SIZE;            // Comptador, per a recorre tota la llista hash.

	while (i--) {
		linkedList = listHash[i];
		// Si no ha caigut cap hash aqui, saltem
		if (!linkedList) continue;

		// Recorrem tots els elements de la llista.
		hashListItem = linkedList->first;
		while (hashListItem) {
			hashListData = hashListItem->data;

			// Trobar el node al arbe amb el mateix origen
			tdata = tree_findNode(tree, hashListData->key_sec);

			if (!tdata) {
				// Si no existeix l'entrada a l'arbre per aquest ORIGEN, crearla
				tdata = (RBData *) malloc(sizeof(RBData));

				// La clau de l'Arbre es l'ORIGEN
				tdata->key = calloc(8, sizeof(char));
				strcpy(tdata->key, hashListData->key_sec);

				// Nova llista amb DESTI com clau
				tdata->list = list_new();

				// Afegim el node al abre.
				tree_insertNode(tree, tdata);
			}

			// Afegim l'informació a la entrada de l'Arbre
			treeListData = list_findKey(tdata->list, hashListData->key);

			if (!treeListData) {
				// Si no te aquesta clau, en creem una de nova i copiem totes les dades
				treeListData = malloc(sizeof(ListData));
				treeListData->key = calloc(8, sizeof(char));
				treeListData->key_sec = calloc(8, sizeof(char));

				strcpy(treeListData->key, hashListData->key);
				strcpy(treeListData->key_sec, hashListData->key_sec);
				memcpy(treeListData->count, hashListData->count, sizeof(int) * 7);
				memcpy(treeListData->total, hashListData->total, sizeof(int) * 7);

				list_insertData(tdata->list, treeListData);

			} else {
				// Sino, fusionar les dades
				for (int j = 0; j < 7; j++) {
					treeListData->count[j] += hashListData->count[j];
					treeListData->total[j] += hashListData->total[j];
				}
			}
			// Seleccionem el seguent element.
			hashListItem = hashListItem->next;
		}
	}

	return;
}


/**
  * Funció simple, per a simplificar el copiar amb malloc.
  *
  * El més 1 del malloc és per guardar el final.
  */
char *copyMalloc(char *in) {
	char *out = (char *) malloc(sizeof(char) * (strlen(in) + 1)); // +1, és per guardar el final del text.
	strcpy(out, in);
	return out;
}

/**
  * Funció simple, per a simplificar el concatenar text.
  *
  * Funcionalitat extra, no cal pensar en fer un free.
  * Perque pel destinatari farà un realloc ( només un free per aquest, però el esperat ).
  * I l'altre automaticament fa el free.
  */
char *encadenar2strings(char *desti, char *text) {
	char *out = malloc(sizeof(char) * (strlen(desti) + strlen(text) + 1)); // +1, és per guardar el final de text.
	strcpy(out, desti);
	strcat(out, text);
	return out;
}

/**
  * Tenim que per llegir la línia, necessitarà de line.
  * I l'esplit necessari ho fara dins de v.
  *
  * line, és la línia on trobarem tota la informació.
  * v, és on guardarem totes les separacions.
  */
void splitLine(char *line, char *v[CSV_COLS], char sep) {
	int i = 0, j = 1;
	char c = 1; // Per entrar dins del bucle.

	v[0] = line;
	while (c && (j < CSV_COLS)) // Iterate over all line characters
	{ // end when we reach end of "line" (\0)
		if (c == sep) // If we find the separator character
		{
			line[i - 1] = '\0';
			v[j++] = line + i; // place next column start after separator
		}
		c = line[i++];
	}
}
