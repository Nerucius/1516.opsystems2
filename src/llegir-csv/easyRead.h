#ifndef EASY_READ_H
#define EASY_READ_H

/**
  * Declarar el nom del fitxer que és vol obrir.
  */
void readInitFile ( char* name );

/**
  * Retornarà un llistat de línies.
  * Tenir present que previament s'ha d'haver fet el "readInitFile".
  *
  * size és per a saber quantes línies desitja.
  * out escriurà el tamany real de la llista.
  */ 
char ** readLines ( int size, int *out );
#endif /* EASY_READ_H */
