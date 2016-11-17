#include <stdio.h>
#include "../arbre-binari/red-black-tree.h"

void ser_writeTree(RBTree* tree, FILE* out){
    char* text = "SampleText";
    fwrite(text, sizeof(char), 11, out);
}

RBTree* ser_readTree(FILE* in){
    char text[11];
    fread(text, sizeof(char), 11, in);
    
    printf("%s\n", text);
    
    return NULL;
}