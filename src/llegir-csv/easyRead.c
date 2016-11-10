#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "../util.h"

// Tamany maxim que llegirem per una línia.
#define MAXCHAR  128

/**
  * Variables que ens permeten que funcions externes puguin treballar
  * sense haber inicialitzat res.
  */
FILE *fp;	// Serveix per a llegir el fitxer.

/**
  * Llegeix les línies indicades a size i ho retorna.
  * Escriu quantes línies ha copiat a out.
  */
char ** readLines ( int requestCount, int *realCount )
{
	int i;
	char ** all;
	char line[MAXCHAR];

	if ( !fp ) // Comprobar que no hemos cerrado el arxivo.
	{
		*realCount = 0;
		return NULL;
	}
	all = ( char ** ) malloc ( requestCount * sizeof (char *) );

	for ( i = 0; i < requestCount; i++ )
	{
		if (fgets(line, MAXCHAR, fp) != NULL)
			all[i] = copyMalloc ( line );
		else
		{ // Realloc molt útil, ja que suposant que realCount = 0, alliverarà automaticament el malloc.
			all = realloc ( all, i * sizeof (char *) );
			fclose (fp); // Tanquem el fitxer.
			fp = NULL; // Assignar NULL
			break;
		}
	}

	// Retornem el nombre real de línies que hi ha a la llista.
	*realCount = i;

	// Retorna el valor desitjat. Una llista d'arrays.
	return all;
}

/**
  * Serveix per a inicialitzar el read.
  */
void readInitFile ( char* name )
{
	fp = fopen ( name, "r" );
	if (!fp)
	{
		printf ("El fitxer: %s\nNo existeix, o no tenim permisos.\n", name);
		exit (1);
	}
}
