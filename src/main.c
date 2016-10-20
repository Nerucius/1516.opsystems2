#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "llegir-csv/easyRead.h"
#include "hash/hash.h"
#include "util.h"
#include "linked-list/linked-list.h"

int initMain ( int argc, char **argv )
{
	switch ( argc )
	{
	case 1:
		readInitFile ( "llegir-csv/file.csv" );
		break;
	case 2:
		if (isdigit ( argv[1][0] ) )
		{
			readInitFile ( "llegir-csv/file.csv" );
			return atoi ( argv[1] );
		}
		readInitFile ( argv[1] );
		break;
	case 3:
		readInitFile ( argv[1] );
		return atoi ( argv[2] );
	default:
		printf("Usage: [nameFile [lines]]\n");
		exit(1);
	}
	return 1000;
}

DataNode createNode ( char **elements )
{
	DataNode n;
//printf ("origen: %s\tdesti: %s\tsetmana: %s\tretard: %s\n", elements[16], elements[17], elements[3], elements[14]);
//	n.origen = 
return n;
}

List ** linesIntoHashTable (char** lines, int count)
{
	int i;
	List** hashTable;
//	int hash;
	char *splits[CSV_COLS]; // El separador CSV per columnes.
	
	
	for (i = 0; i < count; i++)
	{
		// Split the line
		splitLine(lines[i], splits, ',');
		
		createNode ( splits );

//		hash = hashCode(node.origen);
	//	hashCode(node.origen);
 		//hashTable[hash] = inputList();
		// TODO Create inputList()

		free ( lines[i] );
	}

	hashTable = calloc (HASH_SIZE, sizeof(List*));
	free ( lines );
	return hashTable;
}

void addListIntoTree ( List **listHash )
{
	/*int i = HASH_SIZE;
	while ( i-- )
		if ( listHash[i] )
			free ( listHash[i] );
	*/
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
		//hash = hashCode();

		addListIntoTree ( listHash );
	}

	//printf ( "Retorn: %d\n", size );
	//printf ( "%s\n", read[--size]);
	return 0;
}
