#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "llegir-csv/easyRead.h"
#include "hash/hash.h"
#include "util.h"

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

List** linesIntoHashTable (char** lines, int count){
	int i;
	List** hashTable;
	
	hashTable = calloc(HASH_SIZE, sizeof(List*));
	
	for (i = 0; i < count; i++){
		// Split the line
		char** splits = splitLine(lines[i], ',');
		
		DataNode node = createNode ( splits );
		hash = hashCode(node.origen);
 		hashTable[hash] = inputList();
		// TODO Create inputList()
		
	}
	
	return hashTable;
}

int main(int argc, char **argv)
{
	int lecture;
	int size, cont = 1;
	char** linesRead;
	

	
		
	lecture = initMain ( argc, argv );
	
	while(cont)
	{
		linesRead = readLines (lecture, &size, &cont);
		
		if(size){
			linesIntoHashTable(linesRead, size)
			//printf ( "%s\n", read[--size]);
			//hash = hashCode();
		}
		break;
	}

	//printf ( "Retorn: %d\n", size );
	//printf ( "%s\n", read[--size]);
	return 0;
}
