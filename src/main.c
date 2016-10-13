#include <stdio.h>
#include <stdlib.h>

#include "llegir-csv/easyRead.h"

int initMain ( int argc, char **argv )
{
	switch ( argc )
	{
	case 1:
		readInitFile ( "llegir-csv/file.csv" );
		break;
	case 2:
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

int main(int argc, char **argv)
{
	int lecture;
	int size;
	char ** read;

	lecture = initMain ( argc, argv );
	read = readLines ( lecture, &size );

printf ( "Retorn: %d\n", size );
printf ( "%s\n", read[lecture]);
return 0;
}
