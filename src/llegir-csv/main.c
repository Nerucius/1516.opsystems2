/**
 *
 * Main file 
 * 
 * Lluis Garrido, 2016.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define MAXCHAR  128

/**
 *
 * This file reads and outputs the lines of a CSV file. 
 *
 */

void readCSV(char *filename)
{
  FILE *fp;
  char *line;

  char c;

  int i, j;
  char *v[40];

  line = (char *) malloc(sizeof(char) * MAXCHAR);

  fp = fopen(filename, "r");
  if (!fp) {
    printf("Could not open file '%s'\n", filename);
    exit(1);
  }

  while (fgets(line, MAXCHAR, fp) != NULL)
  {
  	i = 0; j = 1;
	v[0] = line;
	do
	{
		c = line[i++];
		if ( c == ',' )
		{
			line[i -1] = '\0';
			v[j++] = line + i;
		}
	} while ( c );

/*	for ( i = 0; i < j; i++ )
		printf ( "|%s", v[i] );
		//printf ( ">%d-%s",i, v[i] );
	printf ("--%d\n", j);*/
	printf ( "4: %d\t15: %d\t17: %s\t18: %s\n", atoi(v[3]), atoi(v[14]), v[16], v[17] );
  }
  
  fclose(fp);

  free(line);
}

/**
 *
 * Main function. 
 *
 */

int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("Usage: %s <fitxer.txt>\n", argv[0]);
    exit(1);
  }

  readCSV(argv[1]);

  return 0;
}

