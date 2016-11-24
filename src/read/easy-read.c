#include <stdlib.h>
#include <stdio.h>

#include "../util.h"

// Tamany maxim que llegirem per una línia.
#define MAXCHAR  128

/**
 * Inicialitza un fitxer per poderlo llegir despres.
 */
FILE *csvFile;	// Serveix per a llegir el fitxer.

/**
  * Serveix per a inicialitzar el read.
  */
void read_initFile(char *name)
{
	csvFile = fopen(name, "r");
	if (!csvFile) {
		printf("El fitxer: %s\nNo existeix, o no tenim permisos.\n", name);
		exit(EXIT_FAILURE);
	}
}

/**
  * Finalitza la lectura del fitxer. Cridat automaticament si s'arriba al final del fitxer.
  */
void read_closeFile()
{
	if (csvFile) {
		fclose(csvFile);
		csvFile = NULL;
	}
}

/**
  * Llegeix el numero de linies del fitxer csv indicades i retorna un llistat de linies.
  *
  * @param requestedLines Numero de linies a llegir
  * @param realCount numero de linies llegides realment
  */
char** read_readLines(int requestedLines, int *realCount)
{
	int i;
	char ** all;
	char line[MAXCHAR];

	if ( !csvFile ) // Comprobar que no hem tancat el fitxer.
	{
		*realCount = 0;
		return NULL;
	}
	all = ( char ** ) malloc ( requestedLines * sizeof (char *) );

	for ( i = 0; i < requestedLines; i++ )
	{
		if (fgets(line, MAXCHAR, csvFile) != NULL)
			all[i] = copyMalloc ( line );
		else
		{ // Realloc molt útil, ja que suposant que realCount = 0, alliverarà automaticament el malloc.
			all = realloc ( all, i * sizeof (char *) );
			read_closeFile();
			break;
		}
	}

	// Retornem el nombre real de línies que hi ha a la llista.
	*realCount = i;

	// Retorna el valor desitjat. Una llista d'arrays.
	return all;
}


