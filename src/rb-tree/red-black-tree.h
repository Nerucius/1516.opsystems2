#ifndef RED_BLACK_H
#define RED_BLACK_H

#define TYPE_RBTREE_KEY char*		// Type of the Key

/**
 *
 * This structure holds the information to be stored at each node. Change this
 * structure according to your needs.  In order to make this library work, you
 * also need to adapt the functions compLT, compEQ and freeRBData. For the
 * current implementation the "key" member is used to index data within the
 * tree. 
 *
 */
typedef struct RBData_
{
  // The variable used to index the tree has to be called "key".
  // The type may be any you want (float, char *, etc)
  TYPE_RBTREE_KEY key;     

  // This is the additional information that will be stored
  // within the structure. You may adapt it to your needs:
  // add or remove fields as you need.
  void* data;	// Pointer to a Linked-List
} RBData;

/**
 *
 * The node structure 
 *
 */
typedef enum { BLACK, RED } nodeColor;

typedef struct Node_ {
	/* For internal use of the structure. Do not change. */
	struct Node_ *left;         /* left child */
	struct Node_ *right;        /* right child */
	struct Node_ *parent;       /* parent */
	nodeColor color;            /* node color (BLACK, RED) */

	/* Data to be stored at each node */
	RBData *data;
} Node;

/**
 *
 * The tree structure. It just contains the root node, from
 * which we may go through all the nodes of the binary tree.
 * Add any field you may find useful.
 *
 */

typedef struct RBTree_ {
  Node *root;                   /* root of Red-Black tree */
} RBTree;

/*
 * Function headers. Note that not all the functions of
 * red-black-tree.c have been included here.
 */
RBTree * tree_new();
void tree_insertNode(RBTree *tree, RBData *data);
RBData *tree_findNode(RBTree *tree, TYPE_RBTREE_KEY key);
void tree_delete(RBTree *tree, void (*delayData)(void *data));
void tree_dump(RBTree *tree);


/*
 * per nosaltres
 */
//RBTree* inputTree ( DataPoint * ListNR, int lenght ); // A partir d'una llista, afegeix a l'abre els elements.

#endif /* RED_BLACK_H */
