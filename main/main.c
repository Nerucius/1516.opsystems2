#include <stdio.h>
#include <stdlib.h>

#include "../llegir-csv/read.h"
#include "../llegir-csv/def.h"
#include "../arbre-binari/red-black-tree.h"
#include "../linked-list/linked-list.h"

/**
  * Afegeix correctament la informació dins la llista.
  */
/*void inputList ( List * list, DataNode dn )
{
	int i;
	ListData *listData;
	int dia = dn.dia;
	char*desti = dn.desti;

	* Search if the key is in the tree *
	listData = findList(list, desti);

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
	listData->total[dia] += dn.retard;
}
*/



int main ()
{
	int lenght;
	RBTree * tree;		// El abre que guardarem tota la informació.
	DataNode * ListNR;

	// Llegeix tot el fitxer.
	ListNR = readCSVfile ( "../llegir-csv/file.csv", &lenght );

	// Insereix tot al arbre.
	tree = inputTree ( ListNR, lenght );

/* Delete the tree */
deleteTree(tree);
return 0;
}
