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
			readInitFile ( "../llegir-csv/file.csv" );
			return atoi ( argv[1] );
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
		if ( strlen (keyList) != 3 ) continue;

		// Fem anar la funció hash.
		hash = hashCode(keyList);

		// Redefinim keyList, ja que el canviarem de tamany. +4 = 3 origen + 1 del zero final.
		keyList = encadenar2strings ( keyList, node.desti );
		free (keyList); //!!!!!!!!!!!!!!!!!!! Només pel valgrid.
		hashTable[hash] = 0; // Perque el compilador no se queixi.
 		//hashTable[hash] = inputList( hashTable[hash], )
		// TODO Create inputList()
	}

	free ( lines ); // Alliberem la llista d'estrings.
	return hashTable;
}

void addListIntoTree ( List **listHash )
{
	/*int i = HASH_SIZE;
	while ( i-- )
		if ( listHash[i] )
			free ( listHash[i] );
	*/
//printf ("free: %p\n", listHash );
	free ( listHash );
}

int main(int argc, char **argv)
{
	int lecture;
	int size, cont = 1;
	char** linesRead;
	List ** listHash;
		
	lecture = initMain ( argc, argv );
	

	while(cont)
	{
		linesRead = readLines (lecture, &size, &cont);
		
		if( !size ) break;

		listHash = linesIntoHashTable (linesRead, size);
		//printf ( "%s\n", read[--size]);

//printf ("Entrant al 3er apartat\n");
		addListIntoTree ( listHash );
	}

	//printf ( "Retorn: %d\n", size );
	//printf ( "%s\n", read[--size]);
	return 0;
}
