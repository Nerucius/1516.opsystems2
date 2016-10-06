#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read.h"

#define MAXCHAR  128

/**
  * Variables que ens permeten que funcions externes puguin treballar
  * sense haber inicialitzat res.
  */
char *line;
FILE *fp;


/**
  * Retorna el punter de la columna "abansada" desitjada.
  */
char * advanceColumn ( int i )
{
	char *token = (char *) 1; // Per poder entrar dins el while
	int k = 0;

	while ( (k++ < i) & (token != NULL) )
		token = strtok ( NULL, "," );

	return token;
}


/**
  * Return 0, is correct
  * Return 1, error, csv
  * Return 2, error, no next line
  */
int readLineFile (struct nodeRead * nd)
{
	char *token;

	if (fgets(line, MAXCHAR, fp) != NULL)
	{
		token = strtok ( line, "," );

		token = advanceColumn ( 3 );
		if ( token ) // Estem a la columna 4, per tenir el dia de la setmana.
			nd->dia = (char) atoi ( token );
		else return 1;

		token = advanceColumn ( 11 );
		if ( token ) // Estem a la columna 15 ( 11+3+1 ), per tenir el retard del vol.
			nd->retard = atoi ( token );
		else return 1;

		token = advanceColumn ( 2 );
		if ( token ) // Estem a la columna 17, per a tenir l'origen de l'aeroport.
		{
			nd->origen = (char *) malloc ( sizeof (char) * (strlen (token)+1) );
			strcpy (nd->origen, token);
			nd->origen[strlen (token)] = '\0';
		}
		else return 1;

		token = advanceColumn ( 1 );
		if ( token ) // estem a la columna 18, per a tenir el destí.
		{
//			nd->desti = (char *) malloc ( sizeof (char) * (strlen (token)+1) );
//			strcpy (nd->desti, token);
//			nd->desti[strlen (token)] = '\0';
		}
		else return 1;
	} else return 2;
return 0;
}

// Per testeixar el nostre codi
void mostrarNode ( struct nodeRead np )
{
	printf ( "dia:\t%c\n", np.dia );
	printf ( "retard:\t%d\n", np.retard );
}

/**
  * Serveix per a inicialitzar el read.
  */
void readInitFile ( char* name )
{
	line = (char *) malloc(sizeof(char) * MAXCHAR);

	fp = fopen ( name, "r" );
	if (!fp)
	{
		printf ("El fitxer: %s\nNo existeix, o no tenim permisos.\n", name);
		exit (1);
	}
}

/**
  * Serveix per acabar amb el read.
  */
void readEndFile ()
{
	free (line);
	fclose (fp);
}
