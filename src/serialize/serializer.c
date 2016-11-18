#include <stdio.h>
#include "../arbre-binari/red-black-tree.h"


void walk_inOrder(Node *node) {
	if (node == NULL)
		return;

	walk_inOrder(node->left);

	printf("%s ", (char *) node->data->data);

	walk_inOrder(node->right);

}


void ser_writeTree(RBTree *tree, FILE *out) {

	Node *walkNode = tree->root;
	walk_inOrder(walkNode);

//    char* text = "SampleText";
//    fwrite(text, sizeof(char), 11, out);
}

RBTree *ser_readTree(FILE *in) {


//    char text[11];
//    fread(text, sizeof(char), 11, in);
//    printf("%s\n", text);

	return NULL;
}