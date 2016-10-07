#include <stdio.h>
#include <stdlib.h>

#include "../llegir-csv/read.h"
#include "../arbre-binari/red-black-tree.h"

/**
  * Afegeix correctament la informació dins la llista.
  */
void inputList ( List * list, nodeRead nr )
{
	int i;
	ListData *listData;
	char dia = nr.dia;
	char*desti = nr.desti;

	/* Search if the key is in the tree */
	listData = findList(list, a);

	if (listData)
	{ // Existeix ja l'element
		free (desti);

	} else
	{
		listData = malloc(sizeof(ListData));

		listData->key = desti;	// Clau

		for ( i = 6; i ; i-- )	// Contingut
		{
			listData->count[i] = 0;
			listData->total[i] = 0;
		}

		insertList(list, listData);
	}

	// Actualitza la informació desitjada.
	listData->count[dia]++;
	listData->total[dia] += nr.retard;
}

/**
  * Fa el necessari per afegir la informació.
  * En cas de no existir el node, el crea.
  * En cas d'existir, allivera la memòria. Tot i actualitzar la llista.
  */
void inputElementTree ( RBTree * tree, nodeRead nr )
{
	RBData * treeData;	// Node del abre, per a poder treballar comodament.
	List *list;		// Llista, el que conté l'abre

	char *origen = nr.origen;
	treeData = findNode (tree, origen);

	if ( treeData )
	{ // Ja existeix, alliverem la memoria.
		free ( origen );
	} else
	{ // Sino, el generem.
		// Clau.
		treeData = malloc (sizeof(RBData));
		treeData->key = origen;

		// Contingut.
		list = (List *) malloc(sizeof(List));
		initList(list);
		treeData->llista = list;

		insertNode (tree, treeData);
	}
	inputList ( treeData->llista, nr );
}

/**
  * A partir d'una llista de nodes,
  * crea i posa els elements dins l'arbre, on retornara el punter.
  *
  * key = origen
  *
  * Contingut = llista
  *	- key = desti
  *	- contingut = meanWeek
  */
RBTree* inputTree ( nodeRead * ListNR, int lenght )
{
	RBTree * tree;		// El abre que guardarem tota la informació.

	/* Allocate memory for tree */
	tree = (RBTree *) malloc(sizeof(RBTree));

	/* Initialize the tree */
	initTree(tree);

	while ( --lenght ) // Recorrerem tots els elements.
		inputElementTree ( tree, ListNR[lenght] );
return tree;
}


int main ()
{
	RBTree * tree;		// El abre que guardarem tota la informació.

	// Llegeix tot el fitxer.
	ListNR = readInitFile ( "../llegir-csv/file.csv", &lenght );

	// Insereix tot al arbre.
	tree = inputTree ( ListNR, lenght );

/* Delete the tree */
deleteTree(tree);
return 0;
}
