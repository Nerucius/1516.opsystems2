#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read.h"

#define LINE_SIZE 256

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

char** splitLine(char* a_str, char a_delim){
	char** result    = 0;
	size_t count     = 0;
	char* tmp        = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp){
		if (a_delim == *tmp)
		{
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	/* Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);

	/* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
	count++;

	result = malloc(sizeof(char*) * count);

	if (result)
	{
		size_t idx  = 0;
		char* token = strtok(a_str, delim);

		while (token)
		{
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}

nodeRead* readCSVFile(char* filename, int* size){
	char* line = (char *) malloc(sizeof(char) * LINE_SIZE);
	int read, i;
	size_t len = 0;
	char** columns;
	//nodeRead tmpNode;

	FILE* fp = fopen(filename, "r");
	if(fp == NULL){
		printf("File Not Found.");
		exit(1);
	}

	while ((read = getline(&line, &len, fp)) != -1) {
		columns = splitLine(line, ',');
//		tmpNode = createNodeFromTokens(tokens);

		for(i = 0; i < 18; i++){
			printf("col: %s\n", columns[i]);
		}

		return;
	}

}
