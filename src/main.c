#include <stdio.h>
#include <stdlib.h>

#include "llegir-csv/read.h"
#include "llegir-csv/def.h"
#include "arbre-binari/red-black-tree.h"
#include "linked-list/linked-list.h"

int main ()
{
	int lenght;
	RBTree * tree;		// El abre que guardarem tota la informació.
	DataNode * ListNR;	// La llista on guardarem tota la informació al llegir el fitxer.

	// Llegeix tot el fitxer.
	ListNR = readCSVfile ( "llegir-csv/file.csv", &lenght );

	// Insereix tot al arbre.
	tree = inputTree ( ListNR, lenght );

/* Delete the tree */
deleteTree(tree);
return 0;
}
