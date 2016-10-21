#ifndef UTIL_H
#define UTIL_H

// Nombre de columnes que conte el fitxer CSV.
#define CSV_COLS 28

/**
  * Sense efectuar cap canvi a in, el copia fent un malloc.
  */
char * copyMalloc ( char * in );

/**
  * Copia el text desti i text, alliverant en memoria els dos.
  * Retornant una cadena amb les dues cadenes.
  * I allivera la segona automaticament.
  */
char * encadenar2strings ( char * desti, char * text );

/**
  * Modifica la variable line,
  * tal que v pot apuntar al inici dels strings
  * separats per sep.
  */
void splitLine (char *line, char *v[CSV_COLS], char sep);

#endif
