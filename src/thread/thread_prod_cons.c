#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include <semaphore.h>

// Fils
pthread_t *consumitors;
pthread_t productor;

// Semafors + controladors pel buffer.
sem_t prod_sem, cons_sem;
int productor_pointer, consumitor_pointer, prod_end;

// Buffer
char **buffer;
int buffer_size;

// Nombre de consumidors.
int num_thread_consumitors;

// Funcio pel productor:
char * (*productor_extract_data) (void);
int (*productor_continue) (void);

// Funció pel productor i clau;
pthread_mutex_t readBuffer;
void (*consumitor_work) ( char * );


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

	// Preparem el productor
	threadCreate__ ( &productor, prod_fun);

	// Reservem memòria.
	consumitors = malloc ( numConsumitors * sizeof (pthread_t) );
	if ( consumitors == NULL )
	{
		printf ("Error, malloc for thread\n");
		exit (1);
	}

	// Preparem el consumidor
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

/*****************************/

void * productor_function ( void * n)
{
	char * pointer;

	while ( 1 )
	{
		// Genera la informació
		pointer = productor_extract_data ();

		// Necessitem saber quan acabar.
		if ( productor_continue () )
		{
			// Per alliberar els fills.
			prod_end = 1; // Ha acabat.
			sem_post (&cons_sem);
			return NULL;
		}

		// Ara es bloqueixa, esperant a que hi hagi memoria lliure.
		sem_wait (&prod_sem);

		// Un cop tenim permis, escribim la informació.
		buffer[productor_pointer] = pointer;
		productor_pointer = (1+productor_pointer) % buffer_size;

		// Ja acabat tot el que teniem que fer, alliberem el consumidor.
		sem_post (&cons_sem);
	}
	//sem_getvalue (&cons_sem, &NUM_CONSUMITORS_THREADS); ???????????????? semafor pot fer un brodcast?
return NULL;
}

void * consumitor_function ( void * n )
{
	char * pointer;

	while ( 1 )
	{
		// Espera per tenir permissos.
		sem_wait (&cons_sem);

		// Zona delicada.
		pthread_mutex_lock(&readBuffer);
			// Comprobem finalitat del codi.
			if ( prod_end )
			{
				if ( productor_pointer == consumitor_pointer )
				{
					pthread_mutex_unlock(&readBuffer); // Alliberem segona clau
					sem_post (&cons_sem); // Alliberem per si hi ha més fils.
					return NULL;
				}
			}

			// Llegeix del punter.
			pointer = buffer[consumitor_pointer];
			consumitor_pointer = (1+consumitor_pointer) % buffer_size;

		pthread_mutex_unlock(&readBuffer);

		// Ja pot alliberar el productor.
		sem_post (&prod_sem);

		// Ara pot treballar amb les dades.
		consumitor_work (pointer);
	}
return NULL;
}

void init_thread ( int sizeBuffer, char * (*ped) (void), int (*pc) (void), void (*cw) (char *) )
{
	// Definim el tamany del buffer.
	buffer_size = sizeBuffer;

	// Definim les funcions:
	productor_extract_data = ped;
	productor_continue = pc;
	consumitor_work = cw;

	// Els semafors.
	sem_init ( &prod_sem, 0, sizeBuffer);
	sem_init ( &cons_sem, 0, 0);

	// Els punters per saber per on anem.
	productor_pointer = 0;
	prod_end = 0; // False.
	consumitor_pointer = 0;
}
