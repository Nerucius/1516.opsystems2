#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

int main(int argc, char** args) {

    printf("This works");

    Menu *menu = menu_new();
	menu_addItem("This is option 1", NULL);
	menu_addItem("This is option 2", NULL);
    menu_show(menu);

    return 0;
}


