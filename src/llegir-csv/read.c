#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read.h"

// Linia de columnes que te el document, si et passes no és gaire greu. Quedar-se curt donarà problemes.
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
FILE *fp;	// Serveix per a llegir el fitxer.
int size_real;	// Serveix per saber quan vigilar amb el INIT_SIZE.


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
  * I l'esplit necessari ho fara dins de v.
  *
  * Return 0, is correct
  * Return 1, no next line
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
  * En cas de finalitzar, escriu a 'o' un zero.
  */
DataNode readCSVline ( int *o )
{
	DataNode dn;
	char line[MAXCHAR];	// Informació sobre la línia, necessari que MAXCHAR sigui mínim el màxim de la línia.
	char *cD[AIR_COLUMN];	// Informació traduida en columnes.
	char **columsData;	// Només usat per evitar fer un -1 al columsData.
	columsData = cD -1;

	if (readCSV ( line, cD, ',' ))
	{ // Vigilar el cas que no queden més línies.
		*o = 0;
		return dn;
	}

// Guardem tota la informació al node.
	dn.dia		= atoi (	columsData[4] );
	dn.retard	= atoi (	columsData[15] );
	dn.origen	= copyMalloc (	columsData[17] );
	dn.desti	= copyMalloc (	columsData[18] );
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
  *
  * Retorna amb una llista de tots els nodes que ha llegit.
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
