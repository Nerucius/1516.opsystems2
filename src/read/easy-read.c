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
  * Quan no hi ha més elements per llegir, hi haura un NULL
  *
  * @param requestedLines Numero de linies a llegir
  */
char** read_readLines(int requestedLines)
{
	int i;
	char ** all;
	char line[MAXCHAR];

	if ( !csvFile ) // Comprobar que no hem tancat el fitxer.
		return NULL;

	all = ( char ** ) malloc ( (requestedLines +1) * sizeof (char *) );

	for ( i = 0; i < requestedLines; i++ )
	{
		if (fgets(line, MAXCHAR, csvFile) != NULL)
			all[i] = copyMalloc ( line );
		else
		{ // Tanquem el fitxer.
			read_closeFile();
			break;
		}
	}

	// Proteixim el final
	all[i] = NULL;

	if (i == 0)
	{ // Alliberem si no hi ha res.
		free (all);
		all = NULL;
	}

	// Retorna el valor desitjat. Una llista d'arrays.
	return all;
}


