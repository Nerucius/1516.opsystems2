#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

/** Creates a new menu with a given title */
Menu *menu_new(char *title) {
	Menu *m = malloc(sizeof(Menu));
	m->title = title;
	m->numItems = 0;
	m->items = malloc(sizeof(MenuItem));    // Initialize an array of one empty item by default

	return m;
}

/** Add a new Item to the menu with a callable function */
void menu_addItem(Menu *menu, char *item, void (*function)()) {
	MenuItem mItem;

	mItem.text = item;
	mItem.function = function;

	// Resize items array to fit new entry
	menu->items = (MenuItem *) realloc(menu->items, sizeof(MenuItem) * (menu->numItems + 1));
	menu->items[menu->numItems] = mItem;
	menu->numItems++;
}

/** Choose an option from the menu
 * @return True if option is a valid option, otherwise false
 */
int menu_chooseOption(Menu *menu, int opt) {
	if (opt < 1 || opt > menu->numItems) {
		return 0;
	}

	menu->items[opt - 1].function();
	return 1;
}


/** Shows the menu, with a list of options and a prompt */
void menu_show(Menu *menu) {
	int i;

	printf("\n--------------------------------");
	printf("\n%s", menu->title);

	// Imprimir llistat d'opcions
	for (i = 0; i < menu->numItems; i++) {
		MenuItem mi = menu->items[i];
		printf("\n  %3d : %s", i + 1, mi.text);
	}

	printf("\n--------------------------------");
	printf("\n");

	// Preguntar opcio al usuari
	int opt = -1;
	while (!menu_chooseOption(menu, opt)) {
		printf("Opcio: ");
		char in[8];
		fgets(in, 8, stdin);
		opt = atoi(in);
	}
}

/** Free memory used by Menu */
void menu_delete(Menu *menu) {
	free(menu->items);
	free(menu);
}
