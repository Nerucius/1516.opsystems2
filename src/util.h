#ifndef UTIL_H
#define UTIL_H

#define CSV_COLS 28

char * copyMalloc ( char * in );
char** splitLine (char *line, char *separator[CSV_COLS], char sep);

#endif
