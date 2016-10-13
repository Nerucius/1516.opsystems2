#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Tamany maxim que llegirem per una línia.
#define MAXCHAR  128

/**
  * Variables que ens permeten que funcions externes puguin treballar
  * sense haber inicialitzat res.
  */
FILE *fp;	// Serveix per a llegir el fitxer.



/**
  * Funció simple, per a simplificar el copiar amb malloc.
  *
  * El més 1 del malloc és per guardar el final.
  */
char * copyMalloc ( char * in )
{
	char * out = (char *) malloc ( sizeof (char) * (strlen(in) + 1) );
	strcpy ( out, in );
return out;
}


/**
  * Llegeix les línies indicades a size i ho retorna.
  * Escriu quantes línies ha copiat a out.
  */
char ** readLines ( int size, int *out )
{
	int i;
	char ** all;
	char line[MAXCHAR];

	all = ( char ** ) malloc ( size * sizeof (char *) );

	for ( i = 0; i < size; i++ )
	{
		if (fgets(line, MAXCHAR, fp) != NULL)
			all[i] = copyMalloc ( line );
		else break;
	}

	*out = i;
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
