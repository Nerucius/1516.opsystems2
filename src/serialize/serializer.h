#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <stdio.h>
#include "../arbre-binari/red-black-tree.h"

void ser_writeTree(RBTree* tree, FILE* out);

RBTree* ser_readTree(FILE* in);

#endif // SERIALIZER_H