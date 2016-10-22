#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "llegir-csv/easyRead.h"
#include "hash/hash.h"
#include "util.h"
#include "linked-list/linked-list.h"

/**
  * Funció per simplificar el codi del main, tot i donar-li tota la funcionalitat.
  */
int initMain ( int argc, char **argv )
{
	switch ( argc )
	{
	case 1: // Quan no indica res, per defecte.
		readInitFile ( "../llegir-csv/file.csv" );
		break;
	case 2: // Si posa una entrada,
		if (isdigit ( argv[1][0] ) )
		{ // i es digit, llegira en base el dígit.
			argc = atoi ( argv[1] );
			if ( !argc )
			{
				printf ("S'ha de llegir un nombre de línies.\n");
				printf ("Ha entrat: %d\n", argc);
				exit (7);
			}
			// Posem el read al final, per evitar problemes. Ja que si entres un zero donaria un alloc.
			readInitFile ( "../llegir-csv/file.csv" );
			return argc;
		} // Sino, llegira el fitxer indicat.
		readInitFile ( argv[1] );
		break;
	case 3: // Cas de posar 2 entrades, la primera sera per llegir, el segon les línies.
		readInitFile ( argv[1] );
		return atoi ( argv[2] );
	default: // Altres casos (+2) enviara un missatge d'error.
		printf("Usage: [nameFile [lines]]\n");
		exit(1);
	}
	return 1000;
}

/**
  * A partir d'una llista d'estrings, extreiem les columnes que ens interessen.
  */
DataNode createNode ( char **elements )
{
	DataNode n;
	char **p = elements -1;

	n.dia		= atoi	( p[4]  );	// Afegeix la informació del dia.
	n.retard	= atoi	( p[15] );	// Afegeix la informació del retard.
	n.origen	= copyMalloc ( p[17] );	// Diu d'on surt l'avio.
	n.desti		= copyMalloc ( p[18] ); // Diu on arriva l'avio.
//printf ("or: %s\tde: %s\tdi: %d\tre: %d\n", n.origen, n.desti, n.dia, n.retard);
return n;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/**
  * Funció especialitzada en afegir un element dins la llista.
  *
  * FUNCIO CREC JO DE NOMÉS LLISTA !!!!!!!!!!!!!!!!!
  */
List * inputElementInList( List * list, char *key, int dia, int retard)
{
	ListData * ld;

	// En cas que no existeixi la llista.
	if ( !list )
	{
		list = (List *) malloc ( sizeof (List) );
		initList ( list );
	}

	/* Search if the key is in the list */
	ld = findList (list, key);

	// Toca alliverar la memòria exedent.
	if ( ld )
	{
		free (key);
	} else
	{ // Toca generar un ListData.
		ld = (ListData *) malloc ( sizeof (ListData) );

		// Definim la clau.
		ld->key = key;

		// Ens assegurem inicialitzar els valors a zero (calloc).
		ld->count = (int *) calloc ( 7, sizeof (int) ); // Contador de vegades.
		ld->total = (int *) calloc ( 7, sizeof (int) ); // Total del retard.

		// Afegim la data dins de la llista.
		insertList (list, ld);
	}

	// Actualitzem la informació.
	ld->count[dia -1]++;
	ld->total[dia -1] += retard;
return list;
}


/**
  * 2n apartat de l'enunciat de la pràctica 2.
  * Fet tot això en una sola funció per l'enunciat de la pràctica 2.
  *
  * Encarregat de: - traduir el text - fer un hash - omplir la taula amb llistes -
  *
  * Retorna una llista de List.
  */
List ** linesIntoHashTable (char** lines, int count)
{
	int i;			// Pel loop.
	List** hashTable;	// La llista a retornar.
//	List* list;		// Per simplificar al treballar amb llistes.
	int hash;		// La clau hash.
	char *splits[CSV_COLS];	// El separador CSV per columnes.
	char *keyList;		// La clau que farem anar per la llista.
	DataNode node;		// Node on enmagatzem la informació necessaria.
	// Ens assegurem que tot està a zero, per evitar confucions d'interpretar llistes que no existeixen.
	hashTable = calloc (HASH_SIZE, sizeof(List*));
//printf ("Has: %p\t", hashTable );

	// Recorrem totes les línies entrades.
	for (i = 0; i < count; i++)
	{
		// Split the line
		splitLine(lines[i], splits, ',');

		// Generem la informació un cop fet l'esplit.
		node = createNode ( splits );
		free ( lines[i] );	// Alliberem l'estring usat. No ho podem fer abans, ja que fem anar splits.

		keyList = node.origen; // Definim la nova clau per operar.

		// Ens assegurem que origen no és diferent de 3. (enunciat pràctica 1)
		if ( strlen (keyList) != 3 )
		{ // Ens toca alliberar la memòria.
			free ( node.origen );
			free ( node.desti );
			continue;
		}

		// Fem anar la funció hash.
		hash = hashCode(keyList);

		// Redefinim keyList, ja que el canviarem de tamany. +4 = 3 origen + 1 del zero final.
		keyList = encadenar2strings ( keyList, node.desti );

		// Afegim un element a la llista.
 		hashTable[hash] = inputElementInList( hashTable[hash], keyList, node.dia, node.retard);
	}

	free ( lines ); // Alliberem la llista d'estrings.
	return hashTable;
}

void addListIntoTree ( List **listHash )
{
	int i = HASH_SIZE;
	while ( i-- )
		if ( listHash[i] )
			deleteList ( listHash[i] );
//printf ("free: %p\n", listHash );
	free ( listHash );
}

/**
  * Programa comprovat amb diferents estats el valgrind.
  * Per exemple "./main 0", "./main -5", "./main 30000" i fins i tot "./main 1"
  *
  * Procesa moltes dades estil CSV d'un màmim de 28 columnes.
  * Primer només llegeix el fitxer.
  * Tot seguit els posa en un array de llistes per una funció hash.
  * I finalment afegeix els elements en un abre valansejat.
  *
  * Esperem amb la continuació del problema aprendre a programar amb multifils (threads).
  */
int main(int argc, char **argv)
{
	int lecture;		// Nombre de línies en que llegirà el fitxer. (primer apartat de la pràctica 2).
	int size, loop = 1;	// Tamany real llegit i per a saber si continuar dins del bucle.
	char** linesRead;	// Llista on hi ha les N línies llegides.
	List ** listHash;	// Array de llistes amb el format del hash.

	// Hem fet tot el control del main inicial en una funció externa. Per fer-ho visualment més agradable.
	lecture = initMain ( argc, argv );

	// M'entres hi hagi línies per a llegir.
	while(loop)
	{
		// Primer apartat de l'enunciat: Lectura de N línies del fitxer.
		linesRead = readLines (lecture, &size, &loop);

		// Si el tamany és zero, ni ens esforçem a continuar, sortim directament.
		if( !size ) break;

		// Segon apartat de l'enunciat: Incerció de dades a la taula hash.
		listHash = linesIntoHashTable (linesRead, size);
		//printf ( "%s\n", read[--size]);

//printf ("Entrant al 3er apartat\n");
		// Per acabar el segon enunciat: Inserció de dades a l'abre binari.
		addListIntoTree ( listHash );
	}

	return 0;
}
