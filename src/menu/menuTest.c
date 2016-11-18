#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "menu.h"
#include "../serialize/serializer.h"

int RUNNING = 1; // Global variable to terminate program

RBTree *testTree;

void opt_createTree() {
	// TODO Create RBTree here.
}

void opt_saveTreeToFile() {
	FILE *fp = fopen("write.txt", "w");
	ser_writeTree(NULL, fp);
	fclose(fp);
}

void opt_readTreeFromFile() {
	FILE *fp = fopen("write.txt", "r");
	ser_readTree(fp);
	fclose(fp);
}

void opt_showGraph() {
}

void opt_exitProgram() {
	RUNNING = 0;
}


int main(int argc, char **args) {


	// Crear el menu i els seus items.
	Menu *menu = menu_new("Menu de l'Aplicacio");
	menu_addItem(menu, "Crear arbre a partit de Dades.", opt_createTree);
	menu_addItem(menu, "Emmagatzemar arbre a fitxer.", opt_saveTreeToFile);
	menu_addItem(menu, "Llegir arbre desde fitxer.", opt_readTreeFromFile);
	menu_addItem(menu, "Mostrar Grafica de retards.", opt_showGraph);
	menu_addItem(menu, "Sortir del programa.", opt_exitProgram);

	while (RUNNING)
		menu_show(menu);

	menu_delete(menu);

	return 0;
}


