#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCHAR  100

char *line;
FILE *fp;

struct node
{
	char dia;	// Dia, conté valors entre 1 i 7, on 1 és el dilluns i 7 diumenge.
	int retard;	// Els minuts de retard en arribar a destinació.
	char origen[4]; // Origen del vol en IATA
	char desti[4];	// Desti del vol en IATA
};

void readLineFile (struct node * nd)
{
	char *token;
	int k;

	if (fgets(line, MAXCHAR, fp) != NULL)
	{
		token = strtok ( line, "," );

k = 1;

		while ( (k < 4) & token != NULL )
		{ token = strtok ( NULL, "," ); k++; }

		if ( token != NULL )
		{ // 1 - 7, llavors agafem només el primer valor
			nd->dia = token[0];

			while ( (k < 15) & token != NULL )
			{ token = strtok ( NULL, "," ); k++; }

			if ( token != NULL )
			{ // Valor de retard del vol, només ens interesa el valor. Llavors ho convertim directament a int.
				nd->retard = atoi ( token );
printf ("token: %s\n", token );
			}
		}
	}
}

void mostrarNode ( struct node np )
{
	printf ( "dia:\t%c\n", np.dia );
	printf ( "retard:\t%d\n", np.retard );
}

int main ( int argc, char **argv )
{
	struct node np;
	line = (char *) malloc(sizeof(char) * MAXCHAR);

	fp = fopen ( "file.csv", "r" );
	if (!fp)
	{
		printf("Could not open file\n" );
		exit(1);
	}

	readLineFile ( &np );
	mostrarNode ( np );
return 0;
}
