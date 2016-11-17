#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

Menu *menu_new() {
	Menu *m = malloc(sizeof(Menu));
	m->numItems = 0;
	// Initialize an array of one empty item by default
	m->items = malloc(sizeof(MenuItem *));

	return m;
}

/** Add a new Item to the menu with a callable function */
void menu_addItem(Menu *menu, char *item, void *function) {
	MenuItem *mItem = malloc(sizeof(MenuItem));

	mItem->text = item;
	mItem->function = function;

	// Resize items array to fit new entry
	menu->items = (MenuItem*) realloc(menu->items, sizeof(MenuItem *) * menu->numItems + 1);
	menu->items[menu->numItems] = mItem;
	menu->numItems++;
}

/** Shows the menu, with a list of options and a prompt */
void menu_show(Menu *menu) {
//	int i;

	printf("\n--------------------");
	printf("\nThis is a Menu");

//	for (i = 0; i < menu->numItems; i++) {
//		MenuItem *mi = (MenuItem*) menu->items[i];
//		printf("\n%3d : %s", i + 1, mi->text);
//	}

	printf("\n--------------------");
}

/** Choose an option from the menu
 * @return True if option is a valid option, otherwise false
 */
int menu_chooseOption(Menu *menu, int opt) {

	return 1;
}


void menu_delete(Menu *menu) {

}