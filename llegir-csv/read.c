#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read.h"

// Tamany maxim que mirarem.
#define LINE_SIZE 256

// Linia de columnes que te el document.
#define AIR_COLUMN 28
#define AIR_DATA 10

// Com mes proper sigui del valor real millor.
// Si el pasa, exelent.
#define INIT_SIZE 100

// Tamany maxim que llegirem per una línia.
#define MAXCHAR  128

/**
  * Variables que ens permeten que funcions externes puguin treballar
  * sense haber inicialitzat res.
  */
FILE *fp;
int size_real;


/**
  * Funció simple, per a simplificar el copiar amb malloc.
  */
char * copyMalloc ( char * in )
{
	char * out = (char *) malloc ( sizeof (char) * (strlen(in) + 1) );
	strcpy ( out, in );
return out;
}

/**
  * Funció per a simplificar la memòria dinàmica.
  */
void appendList ( DataNode* list, int lenght, DataNode dn )
{
	if (lenght == size_real)
	{
		size_real = (size_real * 3)/2;
		list = realloc ( list, sizeof (DataNode) * size_real );
	}
	list[lenght] = dn;
}

/**
  * Return 0, is correct
  * Return 1, error, no next line
  */
int readCSV ( char all[AIR_COLUMN][AIR_DATA] )
{
	int i;
	char *token;
	char line[MAXCHAR];

	if (fgets(line, MAXCHAR, fp) != NULL)
	{
		token = strtok ( line, "," );
// && token, només és un sistema de seguretat. Perque AIR_COLUMN havia posat 29 petava.
// Seguretat + arreclat el 29 per 28.
		for ( i = 0; (i < AIR_COLUMN) && token; i++ )
		{
			strcpy ( all[i], token );
			token = strtok ( NULL, "," );
		}
		return 0;
	}
return 1;
}

/**
  * Genera l'objecte que necessitem.
  *
  * En cas de finalitzar, escriu a o un zero.
  */
DataNode readCSVline ( char columsData[AIR_COLUMN][AIR_DATA], int *o )
{
	DataNode dn;

	if (readCSV ( columsData )) *o = 0;

// És un menys de la columna (ja que comença perl 0 i no pel 1)
	dn.dia		= atoi ( columsData[4 -1] );
	dn.retard	= atoi ( columsData[15 -1] );
	dn.origen	= copyMalloc ( columsData[17 -1] );
	dn.desti	= copyMalloc ( columsData[18 -1] );
return dn;
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
/**
  * Funcio que llegeix tot el fitxer,
  * llavors omple els nodes de forma correcta.
  */
DataNode *readCSVfile(char *filename, int *size)
{
	DataNode * list;
	DataNode dn;
	int out = 1;
	char columsData[AIR_COLUMN][AIR_DATA];
	size_real = INIT_SIZE;
	readInitFile ( filename );

	list = ( DataNode * ) malloc ( sizeof (DataNode) * size_real );

	*size = 0;
	dn = readCSVline ( columsData, &out );
	while ( out )
	{
		appendList ( list, (*size)++, dn );
		dn = readCSVline ( columsData, &out );
	}
return list;
}




/*******************************************!!!!!!!!!!!!!!!!!!**********************************/
/*******************************************!!!!!!!!!!!!!!!!!!**********************************/
/*******************************************!!!!!!!!!!!!!!!!!!**********************************/
/*******************************************!!!!!!!!!!!!!!!!!!**********************************/
/*******************************************!!!!!!!!!!!!!!!!!!**********************************
char** splitLine(char* a_str, char a_delim){
	char** result    = 0;
	size_t count     = 0;
	char* tmp        = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	* Count how many elements will be extracted. *
	while (*tmp){
		if (a_delim == *tmp)
		{
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	* Add space for trailing token. *
	count += last_comma < (a_str + strlen(a_str) - 1);

	* Add space for terminating null string so caller
       knows where the list of returned strings ends. *
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
*/
