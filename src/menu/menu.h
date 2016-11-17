#ifndef MENU_H
#define MENU_H

typedef struct {
	char *text;
	void (*function)();
} MenuItem;

typedef struct {
	int numItems;
	MenuItem *items;
} Menu;

Menu *menu_new();

void menu_addItem(Menu *menu, char *item, void (*function)());

void menu_show(Menu *menu);

void menu_delete(Menu *menu);

#endif /* MENU_H */
