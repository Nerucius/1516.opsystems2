#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

int running = 1;

void exit_program(){
    running = 0;
}


int main(int argc, char** args) {

	printf("This works");

	Menu *menu = menu_new();
	menu_addItem(menu, "This is option 1", NULL);
	menu_addItem(menu, "This is option 2", NULL);
	menu_addItem(menu, "Exit", exit_program);
	//while(running){
	  menu_show(menu);
	//}
	menu_delete(menu);
    return 0;
}


