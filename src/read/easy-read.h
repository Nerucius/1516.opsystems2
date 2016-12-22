#ifndef EASY_READ_H
#define EASY_READ_H

void read_initFile(char *name);

/**
  * Llegeix el numero de linies del fitxer csv indicades i retorna un llistat de linies.
  * Quan no hi ha més elements per llegir, hi haura un NULL
  *
  * @param requestedLines Numero de linies a llegir
  */
char** read_readLines(int requestedLines);

#endif /* EASY_READ_H */
