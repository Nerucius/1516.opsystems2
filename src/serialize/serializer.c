#include <stdio.h>
#include "../arbre-binari/red-black-tree.h"


void walk_inOrder(Node *node, int level) {
	if (node == NULL)
		return;

	if (node->left != NULL) walk_inOrder(node->left, level + 1);

	// Print node
	printf("\n");
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("Node: %s", (char *) node->data->data);

	if (node->right != NULL) walk_inOrder(node->right, level + 1);

}


void ser_writeTree(RBTree *tree, FILE *out) {

	walk_inOrder(tree->root, 0);

//    char* text = "SampleText";
//    fwrite(text, sizeof(char), 11, out);
}

RBTree *ser_readTree(FILE *in) {

	return NULL;

//    char text[11];
//    fread(text, sizeof(char), 11, in);
//    printf("%s\n", text);
}