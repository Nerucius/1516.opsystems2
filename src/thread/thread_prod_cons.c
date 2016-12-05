#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_t *consumitors;
pthread_t productor;
int num_thread_consumitors;

void threadCreate__ ( pthread_t * pt, void * (*f) (void *) )
{
	if ( (pthread_create (pt, NULL, f, NULL)) )
	{
		printf ("Error, pthread_create\n");
		exit(1);
	}
}

/**
  * Fara un sol productor i consumidors com siguin demanats.
  */
void initThread ( int numConsumitors, void * (*prod_fun)(void *), void * (*cons_fun)(void *) )
{
	int i;
	num_thread_consumitors = numConsumitors;

	// Preparem el consumidor.
	threadCreate__ ( &productor, prod_fun);

	// Reservem memòria.
	consumitors = malloc ( numConsumitors * sizeof (pthread_t) );

	for ( i = 0; i < numConsumitors; i++ )
		threadCreate__ ( consumitors +i, cons_fun);
}

void endThread ()
{
	int i;
	pthread_join (productor, NULL);
	for ( i = 0; i < num_thread_consumitors; i++ )
		pthread_join ( consumitors[i], NULL );
	free (consumitors);
}
