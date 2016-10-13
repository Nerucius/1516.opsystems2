#ifndef READ_CSV_H
#define READ_CSV_H

#include "def.h"


/**
  * Envies el punter de l'estructura, i l'omplirà si és possible.
  *
  * En cas d'exit, retornarà un 1.
  * En cas d'error, retornarà un 0, només si és de la codificació csv.
  * En cas de no haver més línies retornarà un 2.
  */
//int readLineFile (struct DataNode *);

/** Reads a CSV file and puts each line into a tree node. Returns the list of tree nodes.
 *
 * @param filename Path to the csv file to read
 * @param size Returns the total count of nodes
 */
DataNode *readCSVfile(char *filename, int *size);
#endif /* READ_CSV_H */
