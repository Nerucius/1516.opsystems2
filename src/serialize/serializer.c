/**
 *
 * Byte-Aligned Serializer. Writes flags and content in chunks of 8 bytes.
 *
 * @author German Dempere
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../rb-tree/red-black-tree.h"
#include "serializer.h"
#include "../linked-list/linked-list.h"

const char *FILE_START_FLAG = "_RBTREE_";
const char *FILE_END_FLAG = "_FILEND_";

const char *NODE_START_FLAG = "_NODSRT_";
const char *NODE_END_FLAG = "_NODEND_";

const char *LIST_START_FLAG = "_LISTAR_";
const char *LIST_CONTINUE_FLAG = "_LISCON_";
const char *LIST_END_FLAG = "_LISEND_";

/**
 * Recursive write operation, Pre-Order traversal of the tree is ideal for (de)serialization.
 *
 * @param node current node from the recursive stack
 * @param out File stream to write to
 */
void ser_writeInOrder(Node *node, int level, FILE *out) {

	// Write node start flag and key
	fwrite(NODE_START_FLAG, 1, 8, out);
	fwrite(node->data->key, 1, 8, out);
	
	// printf("\nWNode: %s", node->data->key);

	//char* buffer = malloc(sizeof(char) * );
	List *list = node->data->list;

	// If the node has a list, write it out
	if (list) {
		fwrite(LIST_START_FLAG, 1, 8, out);
		ListItem *li = list->first;

		while (li) {
			fwrite(li->data->key, 1, 8, out);
			fwrite(li->data->key_sec, 1, 8, out);
			fwrite(li->data->count, sizeof(int), 7, out);
			fwrite(li->data->total, sizeof(int), 7, out);
			li = li->next;
			if (li) fwrite(LIST_CONTINUE_FLAG, 1, 8, out);
		}

		fwrite(LIST_END_FLAG, 1, 8, out);
	}

	// End of node
	fwrite(NODE_END_FLAG, 1, 8, out);


	if (node->left->data != NULL) ser_writeInOrder(node->left, level + 1, out);
	if (node->right->data != NULL) ser_writeInOrder(node->right, level + 1, out);
}

/**
 * Writes file headers and then recursive writes an RBTree to file.
 *
 * @param tree Tree to write to file
 * @param out Output Stream
 */
void ser_writeTree(RBTree *tree, FILE *out) {

	// Write file Header
	fwrite(FILE_START_FLAG, 1, 8, out);
	ser_writeInOrder(tree->root, 0, out);
	// Write file End flag
	fwrite(FILE_END_FLAG, 1, 8, out);

}

/**
 * If a List has been detected on the tree, read every item till the END flag.
 *
 * @param list List to insert items onto
 * @param in input stream
 */
void readListItems(List *list, FILE *in) {
	char buffer[9];
	buffer[8] = '\0';

	ListData *ldata;

	int hasNext = 1;

	while (hasNext) {
		// Allocate new ListData and add to List, then read directly onto new object
		ldata = malloc(sizeof(ListData));
		ldata->key = malloc(sizeof(char) * 8);
		ldata->key_sec = malloc(sizeof(char) * 8);

		fread(ldata->key, 1, 8, in);
		fread(ldata->key_sec, 1, 8, in);
		fread(ldata->count, sizeof(int), 7, in);
		fread(ldata->total, sizeof(int), 7, in);

		// printf("\n\tListItem: %s -> %s", ldata->key_sec, ldata->key);

		list_insertData(list, ldata);

		// Read oncoming list status flag
		fread(buffer, 1, 8, in);
		// Check for continue
		if (strcmp(buffer, LIST_CONTINUE_FLAG) != 0) {
			hasNext = 0;
		}
	}
	
}

/**
 * Reads a file, deserializing a Tree
 *
 * @param in Input to read from
 * @return A full RBTree instance
 */
RBTree *ser_readTree(FILE *in) {
	size_t readBytes;
	char buffer[9];
	buffer[8] = '\0';

	RBTree *tree = tree_new();
	RBData *rbData;

	readBytes = fread(buffer, 1, 8, in);
	if (readBytes == 0 || strcmp(buffer, FILE_START_FLAG) != 0) {
		printf("\nERROR: File format not correct or empty.");
		return NULL;
	}

	while (1) {
		readBytes = fread(buffer, 1, 8, in);

		if (strcmp(buffer, NODE_START_FLAG) == 0) {
			// Detected Node Key
			fread(buffer, 1, 8, in);
			// printf("\nNODE: %s", buffer);

			// Create new tree node
			rbData = malloc(sizeof(RBData));
			rbData->key = malloc(sizeof(char) * 8);
			strcpy(rbData->key, buffer);


		} else if (strcmp(buffer, LIST_START_FLAG) == 0) {
			// Read entire list, and save as node data
			List *list = list_new();
			readListItems(list, in);
			rbData->list = list;


		} else if (strcmp(buffer, NODE_END_FLAG) == 0) {
			// Insert finished node into data
			tree_insertNode(tree, rbData);
//			printf("\nNODE_END_FLAG");

		} else if (strcmp(buffer, FILE_END_FLAG) == 0 || readBytes == 0) {
			// Detected file end, exit function
//			printf("\nFILE_END_FLAG");
			break;
		}

	}

	return tree;
}