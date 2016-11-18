#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../arbre-binari/red-black-tree.h"
#include "serializer.h"

const char *NODE_END_FLAG = "_NODEEND";

void walk_inOrder(Node *node, int level, FILE *out) {
//	if (node == NULL)
//		return;

	if (node->left->data != NULL) walk_inOrder(node->left, level + 1, out);

	// Print node
	printf("\n");
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("Node: %s", (char *) node->data->data);

	fwrite(node->data->key, 1, 8, out);
	fwrite(node->data->data, 1, 8, out);
	fwrite(NODE_END_FLAG, 1, 8, out);

	if (node->right->data != NULL) walk_inOrder(node->right, level + 1, out);
}


void ser_writeTree(RBTree *tree, FILE *out) {

	walk_inOrder(tree->root, 0, out);

//    char* text = "SampleText";
//    fwrite(text, sizeof(char), 11, out);
}

RBTree *ser_readTree(FILE *in) {
	size_t readBytes;
	char *buffer = malloc(9);
	buffer[8] = 0;

	printf("\n");
	do {
		readBytes = fread(buffer, 1, 8, in);

		if (strcmp(buffer, NODE_END_FLAG) == 0) {
			printf("\n");
		} else {
			printf(" %s", buffer);
		}

	} while (readBytes > 0);

	return NULL;

//    char text[11];
//    fread(text, sizeof(char), 11, in);
//    printf("%s\n", text);
}