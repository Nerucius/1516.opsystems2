#include <stdio.h>
#include <stdlib.h>

#include "../llegir-csv/read.h"
#include "../arbre-binari/red-black-tree.h"

#define MAX 10000

int main ()
{
	struct nodeRead nr;	// Per poder llegir el document.
	int bucle = 1;		// Per estar dins el while.
	int outRead;		// Per saber que ha tret el readLineFile.
	int maxBucle = MAX;	// Valor, per saber quantes línies llegir.

	RBTree * tree;		// El abre que guardarem tota la informació.
	RBData * treeData;	// Node del abre, per a poder treballar comodament.

	readInitFile ( "../llegir-csv/file.csv" );


	/* Allocate memory for tree */
	tree = (RBTree *) malloc(sizeof(RBTree));

	/* Initialize the tree */
	initTree(tree);

	// Llegeix tot el fitxer
	while ( bucle && maxBucle-- )
	{
		outRead = readLineFile (&nr);
		if ( outRead == 0 )
		{
			/* Search if the key is in the tree */
			treeData = findNode(tree, nr.origen); 

			if ( treeData )
			{
				//printf ( "." );
			} else
			{ // En cas de no haber trobat a ningú.
				treeData = malloc(sizeof(RBData));
				treeData->key = nr.origen;

				insertNode(tree, treeData);
			}
		} else if ( outRead == 1 )
		{
			printf ( "Hem detectat un error dins del fitxer.\n" );
			exit (2);
		} else if ( outRead == 2 )
		{
			bucle = 0; // Sortim del bucle.
			readEndFile ();
		} else
		{
			printf ( "Estat inesperat dins del while (bucle)\n" );
			exit (3);
		}
	}

/* Delete the tree */
deleteTree(tree);
return 0;
}
