#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "../arbre-binari/red-black-tree.c"

#define MAXCHAR  128

char *line;
FILE *fp;

struct node
{
	char dia;	// Dia, conté valors entre 1 i 7, on 1 és el dilluns i 7 diumenge.
	int retard;	// Els minuts de retard en arribar a destinació.
	char origen[5]; // Origen del vol en IATA
	char desti[5];	// Desti del vol en IATA
};

/**
  * Retorna el punter de la columna "abansada" desitjada.
  */
char * advanceColumn ( int i )
{
	char *token = (char *) 1;
	int k = 0;

	
	while ( (k++ < i) & token != NULL )
		token = strtok ( NULL, "," );

	return token;
}

void readLineFile (struct node * nd)
{
	char *token;
	int k;

	if (fgets(line, MAXCHAR, fp) != NULL)
	{
		token = strtok ( line, "," );

		token = advanceColumn ( 3 );
		if ( token ) // Estem a la columna 4, per tenir el dia de la setmana.
			nd->dia = token[0];

		token = advanceColumn ( 11 );
		if ( token ) // Estem a la columna 15 ( 11+3+1 ), per tenir el retard del vol.
			nd->retard = atoi ( token );

		token = advanceColumn ( 2 );
		if ( token ) // Estem a la columna 17, per a tenir l'origen de l'aeroport.
			nd->origen = token;

		token = advanceColumn ( 1 );
		if ( token ) // estem a la columna 18, per a tenir el destí.
			nd->desti = token;
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


fclose(fp);
free(line);
return 0;
}
