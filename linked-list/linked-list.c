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
 *
 * Free data element. The user should adapt this function to their needs.  This
 * function is called internally by deleteList.
 *
 */

static void freeListData(ListData *data)
{
	free(data->key); // l'unic que cal alliberar.
	free(data); 
}

/**
 *
 * Dumps data contents to stdout. To be used for debugging.
 *
 */

static void dumpListData(ListData *data)
{
  printf("Key: %s\n", data->key);
}

/**
 *
 * Compares if key1 is equal to key2. Should return 1 (true) if condition
 * is satisfied, 0 (false) otherwise.
 *
 */

static int compEQ(TYPE_LIST_KEY key1, TYPE_LIST_KEY key2)
{
  int rc;

  rc = strcmp ( key1, key2 );

  if (rc == 0 )
    return 1;

  return 0;
}

/**
 * 
 * NO CANVIEU EL CODI QUE HI HA A SOTA LLEVAT QUE SAPIGUEU EL QUE ESTEU FENT.
 * PER FER LES PRACTIQUES NO CAL MODIFICAR EL CODI QUE HI HA A SOTA.
 *
 */

/**
 * 
 * Initialize an empty list
 *
 */

void initList(List *l)
{
  l->numItems = 0;
  l->first = NULL;
}

/**
 * 
 * Insert data in the list.  This function does not perform a copy of data
 * when inserting it in the list, it rather creates a list item and makes
 * this item point to the data. Thus, the contents of data should not be
 * overwritten after calling this function.
 *
 */

void insertList(List *l, ListData *data)
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

ListData *findList(List *l, TYPE_LIST_KEY key)
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

/**
 * 
 * Deletes the first item of the list. The data to which
 * the deleted item points to also is deleted.
 *
 */

void deleteFirstList(List *l)
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

void deleteList(List *l)
{
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

void dumpList(List *l)
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

/**
  * Afegeix correctament la informació dins la llista.
  */
void inputList ( List * list, DataNode dn )
{
	int i;
	ListData *listData;
	int dia = dn.dia -1; // Ja que va de 1 fins a 7
	char*desti = dn.desti;

	/* Search if the key is in the tree */
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
