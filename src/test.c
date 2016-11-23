#include <stdio.h>
#include <stdlib.h>

#include "linked-list/linked-list.h"

int main(int argc, char **argv) {

	printf("Test Program\n");

	List *list = list_new();

	ListData* ld = malloc(sizeof(ListData));
	ld->key = "Key001";

	list_insertData(list, ld);

	printf("Key item: %s ", list_findKey(list, "Key001")->key);

}