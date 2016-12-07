#include <stdio.h>
#include <stdlib.h>


#include <pthread.h> // M'agradaria que no estigues aqui

// De moment per aqui, en un futur, vegam si entra en una llibreria.
#include <semaphore.h>

#include "thread_prod_cons.h"

#define SIZE_M 30
#define NUM_CONSUMITORS_THREADS 5


int buffer[SIZE_M];
int count[SIZE_M];
int productor_pointer, consumitor_pointer, prod_end;
sem_t prod_sem, cons_sem;
pthread_mutex_t readBuffer;

void * productor_fun ( void * n )
{
	int i;
	int data;

	for ( i = 0; i < 70; i++ )
	{
		// Genera la informació
		data = 2*i;

		printf ("P: %5d\n", i); //Per comprobar que funciona adequadament.

		// Ara es bloqueixa, esperant a que hi hagi memoria lliure.
		sem_wait (&prod_sem);

		// Un cop tenim permis, escribim la informació.
		buffer[productor_pointer] = i;
		productor_pointer = (1+productor_pointer) % SIZE_M;

		// Ja acabat tot el que teniem que fer, alliberem el consumidor.
		sem_post (&cons_sem);
	}

	// Per alliberar els fills.
	prod_end = 1; // Ha acabat.
	printf ("P: Acabat\n");
	//sem_getvalue (&cons_sem, &NUM_CONSUMITORS_THREADS);
	sem_post (&cons_sem);
return NULL;
}

void * consumitor_fun ( void * n )
{
	int local;

	while ( 1 )
	{
		// Espera per tenir permissos.
		sem_wait (&cons_sem);

		// Zona delicada.
		pthread_mutex_lock(&readBuffer);
			// Comprobem finalitat del codi.
			if ( prod_end )
			{
				printf ("C:comprova\n");
				if ( productor_pointer == consumitor_pointer )
				{
					pthread_mutex_unlock(&readBuffer); // Alliberem segona clau
					sem_post (&cons_sem); // Alliberem per si hi ha més fils.
					printf ("C:Acabat\n");
					return NULL;
				}
			}

			// Llegeix del punter.
			local = buffer[consumitor_pointer];
			consumitor_pointer = (1+consumitor_pointer) % SIZE_M;

			printf ("C:%5d,%5d,%5d\n", local, consumitor_pointer, productor_pointer);
		pthread_mutex_unlock(&readBuffer);

		// Ja pot alliberar el productor.
		sem_post (&prod_sem);

		// Ara pot treballar amb les dades.
	}
return NULL;
}

void initBlockThread (void)
{
	// Els semafors.
	sem_init ( &prod_sem, 0, SIZE_M);
	sem_init ( &cons_sem, 0, 0);

	// Els punters per saber per on anem.
	productor_pointer = 0;
	prod_end = 0; // False.
	consumitor_pointer = 0;
}

int main (int argc, char *argv[])
{
	initBlockThread ();

	initThread (NUM_CONSUMITORS_THREADS, productor_fun, consumitor_fun);
	endThread ();
return 0;
}
