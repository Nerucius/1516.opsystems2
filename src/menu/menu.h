#ifndef MENU_H
#define MENU_H

typedef struct MenuItem_ {
	char *text;
	void (*function)();
} MenuItem;

typedef struct Menu_ {
	char *title;
	int numItems;
	MenuItem *items;
} Menu;

Menu *menu_new(char *title);

void menu_addItem(Menu *menu, char *item, void (*function)());

void menu_show(Menu *menu);

void menu_delete(Menu *menu);

#endif /* MENU_H */
