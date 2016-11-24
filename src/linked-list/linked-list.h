#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
 *
 * Linked-list header 
 * 
 * Include this file in order to be able to call the 
 * functions available in linked-list.c. We include
 * here only those information we want to make visible
 * to other files.
 *
 * Lluis Garrido, 2016.
 *
 */

/**
 * 
 * The TYPE_LIST_KEY is used to define the type of the primary
 * key used to index data in the list. 
 *
 */

#define TYPE_LIST_KEY char*

/**
 *
 * This structure holds the information to be stored at each list item.  Change
 * this structure according to your needs.  In order to make this library work,
 * you also need to adapt the functions compEQ and freeListData. For the
 * current implementation the "key" member is used search within the list. 
 *
 */

typedef struct ListData_ {
	// The variable used to index the list has to be called "key".
	TYPE_LIST_KEY key;		// Primary key (DESTI)
	TYPE_LIST_KEY key_sec; // Secondary key (ORIGEN)

	// This is the additional information that will be stored
	// within the structure. This additional information is associated
	// to the key. You may include any field you may need useful.
	int count[7];
	int total[7];
} ListData;


/**
 * 
 * The item structure
 *
 */

typedef struct ListItem_ {
  ListData *data;
  struct ListItem_ *next;
} ListItem;

/**
 * 
 * The list structure
 *
 */

typedef struct List_ {
  int numItems;
  ListItem *first;
} List;

/**
 *
 * Function heders we want to make visible so that they
 * can be called from any other file.
 *
 */

List* list_new();
void list_insertData(List *l, ListData *data);
ListData *list_findKey(List *l, TYPE_LIST_KEY key);
ListData *list_find2Keys(List *l, TYPE_LIST_KEY key, TYPE_LIST_KEY key_sec);
void list_deleteFirst(List *l);
void list_delete(void *l);
void list_dump(List *l);


// Implementat per nosaltres.
//void inputList ( List * list, DataPoint dn ); // Afegeix un node a la llista.
#endif /* LINKED_LIST_H */
