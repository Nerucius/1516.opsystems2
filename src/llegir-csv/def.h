#ifndef DEF_H
#define DEF_H

/**
  * Estructura que ens serveix per a simplificar que retorna
  * el programa read.
  */
typedef struct {
    int dia;    // Dia, conté valors entre 1 i 7, on 1 és el dilluns i 7 diumenge.
    int retard;    // Els minuts de retard en arribar a destinació.
    char *origen;    // Origen del vol en IATA
    char *desti;    // Desti del vol en IATA
} DataNode;
#endif /* DEF_H */
