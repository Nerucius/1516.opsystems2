#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "../serialize/serializer.h"

int running = 1;

void opt_saveTreeToFile(){
    FILE* fp = fopen("write.txt", "w");
    ser_writeTree(NULL, fp);
    fclose(fp);
}

void opt_readTreeFromFile(){
    FILE* fp = fopen("write.txt", "r");
    ser_readTree(NULL, fp);
    fclose(fp);
}

void opt_showGraph(){
}

void opt_exitProgram(){
    running = 0;
}


int main(int argc, char** args) {
    printf("Main Function entered\n");

    FILE* fp = fopen("write.txt", "w");
    ser_writeTree(NULL, fp);
    fclose(fp);


    fp = fopen("write.txt", "r");
    ser_readTree(fp);
    fclose(fp);

    
    Menu *menu = menu_new();
    menu_addItem(menu, "Crear arbre a partit de Dades.", NULL);
    menu_addItem(menu, "Emmagatzemar arbre a fitxer.", opt_saveTreeToFile);
    menu_addItem(menu, "Llegir arbre desde fitxer.", opt_readTreeFromFile);
    menu_addItem(menu, "Mostrar Grafica de retards.", opt_showGraph);
    menu_addItem(menu, "Sortir del programa.", opt_exitProgram);

    while(running)
      menu_show(menu);

    menu_delete(menu);
    
    return 0;
}


