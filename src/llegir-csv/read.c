#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read.h"

// Linia de columnes que te el document.
#define AIR_COLUMN 28

// Com mes proper sigui del valor real millor.
// Si el pasa, exelent, però si l'exedeix, hi ha molta informació "perduda".
#define INIT_SIZE 10000

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
DataNode * appendList ( DataNode* list, int lenght, DataNode dn )
{
	if (lenght >= size_real)
	{
		size_real = (lenght * 3)/2;
		list = realloc ( list, sizeof (DataNode) * size_real );
	}
	list[lenght] = dn;
return list;
}

/**
  * Tenim que per llegir la línia, necessitarà de line.
  * I split necessari ho fara dins de v.
  * Return 0, is correct
  * Return 1, error, no next line
  */
int readCSV ( char line[MAXCHAR], char *v[AIR_COLUMN], char sep )
{
	int i, j;
	char c;

	i = 0; j = 1;
	v[0] = line;
	if (fgets(line, MAXCHAR, fp) != NULL)
	{
		i = 0; j = 1;
		v[0] = line;
		do
		{
			c = line[i++];
			if ( c == sep )
			{
				line[i -1] = '\0';
				v[j++] = line + i;
			}
		} while ( c );
		return 0;
	}
return 1;
}

/**
  * Genera l'objecte que necessitem.
  *
  * En cas de finalitzar, escriu a o un zero.
  */
DataNode readCSVline ( int *o )
{
	DataNode dn;
	char line[MAXCHAR];
	char *columsData[AIR_COLUMN];

	if (readCSV ( line, columsData, ',' ))
	{
		*o = 0;
		return dn;
	}

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
	size_real = INIT_SIZE;
	readInitFile ( filename );

	list = ( DataNode * ) malloc ( sizeof (DataNode) * size_real );

	*size = 0;
	dn = readCSVline ( &out );
	while ( out )
	{
		list = appendList ( list, (*size)++, dn );
		dn = readCSVline ( &out );
	}

list = realloc (list, sizeof (DataNode)**size);
fclose (fp);
return list;
}
