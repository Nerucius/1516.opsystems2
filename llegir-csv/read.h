#ifndef READ_CSV_H
#define READ_CSV_H

/**
  * Estructura que ens serveix per a simplificar que retorna
  * el programa read.
  */
struct nodeRead
{
	char dia;	// Dia, conté valors entre 1 i 7, on 1 és el dilluns i 7 diumenge.
	int retard;	// Els minuts de retard en arribar a destinació.
	char* origen;	// Origen del vol en IATA
	char* desti;	// Desti del vol en IATA
};

typedef struct {
    char dia;    // Dia, conté valors entre 1 i 7, on 1 és el dilluns i 7 diumenge.
    int retard;    // Els minuts de retard en arribar a destinació.
    char *origen;    // Origen del vol en IATA
    char *desti;    // Desti del vol en IATA
} DataNode;

/**
  * Per inicialitzar el servell de la llibreria. Indicar el nom.
  *
  * En cas de no existir, enviarà un exit (1) amb un missatge.
  */
void readInitFile ( char* name );

/**
  * Per acabar amb el servell de la llibreria.
  */
void readEndFile ();

/**
  * Envies el punter de l'estructura, i l'omplirà si és possible.
  *
  * En cas d'exit, retornarà un 1.
  * En cas d'error, retornarà un 0, només si és de la codificació csv.
  * En cas de no haver més línies retornarà un 2.
  */
int readLineFile (struct nodeRead *);

/** Reads a CSV file and puts each line into a tree node. Returns the list of tree nodes.
 *
 * @param filename Path to the csv file to read
 * @param size Returns the total count of nodes
 */
struct nodeRead *readCSVFile(char *filename, int *size);

#endif /* READ_CSV_H */