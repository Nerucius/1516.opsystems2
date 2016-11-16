#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"

/**
  * Funció simple, per a simplificar el copiar amb malloc.
  *
  * El més 1 del malloc és per guardar el final.
  */
char * copyMalloc ( char * in )
{
	char * out = (char *) malloc ( sizeof (char) * (strlen(in) + 1) ); // +1, és per guardar el final del text.
	strcpy ( out, in );
return out;
}

/**
  * Funció simple, per a simplificar el concatenar text.
  *
  * Funcionalitat extra, no cal pensar en fer un free.
  * Perque pel destinatari farà un realloc ( només un free per aquest, però el esperat ).
  * I l'altre automaticament fa el free.
  */
void encadenar2strings ( char * desti, char * text )
{
	desti = malloc (desti, sizeof(char) * (strlen (desti) + strlen (text) +1)); // +1, és per guardar el final de text.
	strcat ( desti, text );
	// free (text);
return desti;
}

/**
  * Tenim que per llegir la línia, necessitarà de line.
  * I l'esplit necessari ho fara dins de v.
  *
  * line, és la línia on trobarem tota la informació.
  * v, és on guardarem totes les separacions.
  */
void splitLine (char *line, char *v[CSV_COLS], char sep)
{
	int i = 0, j = 1;
	char c = 1; // Per entrar dins del bucle.

	v[0] = line;
	while ( c && (j < CSV_COLS) ) // Iterate over all line characters
	{ // end when we reach end of "line" (\0)
		if ( c == sep ) // If we find the separator character
		{
			line[i -1] = '\0';
			v[j++] = line + i; // place next column start after separator
		}
		c = line[i++];
	}
}
