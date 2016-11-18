#ifndef SERIALIZER_H
#define SERIALIZER_H

/** Write a RBTree to a file */
void ser_writeTree(RBTree* tree, FILE* out);

/** Read RBTree from a file */
RBTree* ser_readTree(FILE* in);

#endif // SERIALIZER_H