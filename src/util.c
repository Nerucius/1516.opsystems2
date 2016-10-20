#include <stdio.h>
#include <strings.h>

#define CSV_COLS 28

/**
  * Tenim que per llegir la línia, necessitarà de line.
  * I l'esplit necessari ho fara dins de v.
  *
  * returns list of pointers to each col start.
  */
char** splitLine (char *line, char sep)
{
	int i = 0, j = 0;
	char c;
	char* v[CSV_COLS];	// Vector of pointers to string start

	v[0] = line;
	do // Iterate over all line characters
	{
		c = line[i++];
		if ( c == sep ) // If we find the separator character
		{
			line[i -1] = '\0';
			v[++j] = line + i; // place next column start after separator
		}
	} while (c); // end when we reach end of "line" (\0)
	
	return v;
}
