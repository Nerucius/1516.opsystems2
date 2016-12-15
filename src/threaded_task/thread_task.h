#ifndef THREADED_TASK_H
#define THREADED_TASK_H

/**
 * Defineix una nova tasca parapel.litzable amb dos funcions, una que obte dades, i un altra que
 * processa aquestes dades.
 */
void tt_init(void* (*f_getData) (void), void (*f_processData) (void *));

/**
 * Ejecuta la tasca parapel.litzable fent servir un productor i el numero de consumidors indicats.
 * Crea i destrueix els threads segons sigui convenient. El proces no depen dels tipus que tractin
 * les funcions definides al tt_init().
 */
void tt_executeTast(int num_consumers, int buffer_size);


#endif /* THREADED_TASK_H */