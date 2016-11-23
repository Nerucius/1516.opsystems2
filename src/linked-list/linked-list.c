/**
 *
 * Linked-list implementation. 
 * 
 * This is an implementation of a simple linked-list. A minimal
 * set of necessary functions have been included.
 *
 * Lluis Garrido, 2016.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * We include the linked-list.h header. Note the double
 * quotes.
 */

#include "linked-list.h"

/**
 * Free data element. The user should adapt this function to their needs.  This
 * function is called internally by deleteList.
 */
static void freeListData(ListData *data)
{
	free (data->key);
	if(data->key_sec) free (data->key_sec);
	free (data);
}

/**
 * Dumps data contents to stdout. To be used for debugging.
 */
static void dumpListData(ListData *data)
{
	printf("\tKey: %s->%s\n", data->key_sec, data->key);
	for(int i = 0; i < 7; i++){
		printf("\t\tDay: %d: %.2f\n", i+1, (float)data->total[i]/data->count[i]);
	}
	printf("");
}

/**
 * Compares if key1 is equal to key2. Should return 1 (true) if condition
 * is satisfied, 0 (false) otherwise.
 */

static int compEQ(TYPE_LIST_KEY key1, TYPE_LIST_KEY key2)
{
	if (strcmp ( key1, key2 ))
		return 0;
	return 1;
}

/**
 * 
 * NO CANVIEU EL CODI QUE HI HA A SOTA LLEVAT QUE SAPIGUEU EL QUE ESTEU FENT.
 * PER FER LES PRACTIQUES NO CAL MODIFICAR EL CODI QUE HI HA A SOTA.
 *
 */

/**
 * Initialize an empty list
 */
void initList(List *l)
{
  l->numItems = 0;
  l->first = NULL;
}

/**
 * Create an empty, initialized list.
 * @return List pointer to new list
 */
List* list_new()
{
  List *l;
  // Allocar memoria, error si no es pot
  l = (List *) malloc ( sizeof (List) );
  if ( !l )
  {
	  printf ("ERROR memory, 'list_new'\n");
	  exit (1);
  }
  initList(l);
  return l;
}




/**
 * 
 * Insert data in the list.  This function does not perform a copy of data
 * when inserting it in the list, it rather creates a list item and makes
 * this item point to the data. Thus, the contents of data should not be
 * overwritten after calling this function.
 *
 */

void list_insertData(List *l, ListData *data)
{
  ListItem *tmp, *x;

  x = malloc(sizeof(ListItem));

  if (x == 0) {
    printf("insufficient memory (insertItem)\n");
    exit(1);
  }

  /* Insert item at first position */

  tmp = l->first;
  l->first = x;
  x->next = tmp;

  /* Link data to inserted item */
  x->data = data;
}

/**
 * 
 * Find item containing the specified key. Returns the data
 * that it points to (not the item itself).
 *
 */

ListData *list_findKey(List *l, TYPE_LIST_KEY key)
{
  ListItem *current;

  current = l->first;

  while (current != NULL)
  {
    if (compEQ(current->data->key, key))
      return (current->data);

    current = current->next;
  }

  return (NULL);
}

ListData *list_find2Keys(List *l, TYPE_LIST_KEY key, TYPE_LIST_KEY key_sec)
{
	ListItem *current;

	current = l->first;

	while (current != NULL) {
		// Check for BOTH matches
		if (compEQ(current->data->key, key) && compEQ(current->data->key_sec, key_sec))
			return (current->data);

		current = current->next;
	}

	return (NULL);
}

/**
 * 
 * Deletes the first item of the list. The data to which
 * the deleted item points to also is deleted.
 *
 */

void list_deleteFirst(List *l)
{
  ListItem *tmp;

  tmp = l->first;

  if (tmp)
  {
    l->first = tmp->next;
    freeListData(tmp->data);
    free(tmp);
    l->numItems--;
  }
}

/**
 * 
 * Deletes a list including the data to which their 
 * items point to.
 *
 */

void list_delete(void *list)
{
  List *l = (List *) list;
  ListItem *current, *next;

  current = l->first;

  while (current != NULL)
  {
    next = current->next;
    freeListData(current->data);
    free(current);
    current = next;
  }

  free (l);
}

/**
 * 
 * Dumps the contents of the list. Internally this function
 * called dumpListData which is user defined.
 *
 */
void list_dump(List *l)
{
  ListItem *current;

  current = l->first;

  while (current != NULL)
  {
    dumpListData(current->data);
    current = current->next;
  }

  printf("Total number of items: %d\n", l->numItems);
}
