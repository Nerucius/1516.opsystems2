#include <string.h>
#include <stdlib.h>

#include "util.h"

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
  * Tenim que per llegir la línia, necessitarà de line.
  * I l'esplit necessari ho fara dins de v.
  *
  * line, és la línia on trobarem tota la informació.
  * v, és on guardarem totes les separacions.
  *
  * returns list of pointers to each col start.
  */
char** splitLine (char *line, char*v[CSV_COLS], char sep)
{
	int i = 0, j = 0;
	char c;

	v[0] = line;
	do // Iterate over all line characters
	{
		c = line[i++];
		if ( c == sep ) // If we find the separator character
		{
			line[i -1] = '\0';
			v[++j] = line + i; // place next column start after separator
		}
	} while ( c && (j < CSV_COLS)); // end when we reach end of "line" (\0)
	
	return v;
}
