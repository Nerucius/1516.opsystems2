#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../cbuffer/cbuffer.h"

// Declarant variables globals
void* (*f_getData) (void);		// return NULL end program.
void (*f_processData) (void *);

int status = 1;

// Declarant funcions, son les funcions que executaran els threads.
void* _producer(void*);
void* _consumer(void*);
void _threadCreate ( pthread_t * pt, void * (*f) (void *) );


/**
  * Permetem inicialitzar els threads.
  *
  * On obtindran la informació dels getData i procesaran la informació en processData.
  */
void tt_init(void* (*_f_getData) (void), void (*_f_processData) (void *)){
  
  // Definim les nostres funcions.
  f_getData = _f_getData;
  f_processData = _f_processData;
  
  // Validem l'estat. Per evitar cridar tt_executeTast sense haver fer l'init previament.
  status = 0;
}


/**
  * Executarà les dues funcions protegint l'obtenció d'informació i el processament.
  */
void tt_executeTast(int num_consumers, int buffer_size)
{
	int i;			// Variable usada en el for.
	pthread_t *consumitors;	// Consumidors.
	pthread_t productor;	// Productor.

	// Comrovem haver fet el tt_init previament.
	if ( status )
	{
		printf ("ERROR: no s'ha fet tt_init\n");
		exit (1);
	}

	// Inicialitzem el buffer. I reservem memoria pels consumidors.
	cbuffer_init ( buffer_size );
	consumitors = malloc ( num_consumers * sizeof (pthread_t) );

	// Comenzem amb el consumidor i continuarem inician el productor.
	_threadCreate ( &productor, _producer );
	for ( i = 0; i < num_consumers; i++ )
		_threadCreate ( consumitors +i, _consumer );

	// Esperem el productor i els consumidors.
	pthread_join ( productor, NULL );
	for ( i = 0; i < num_consumers; i++ )
		pthread_join ( consumitors[i], NULL );

	// Alliberem el buffer.
	cbuffer_free ();
}

void* _producer(void* n)
{
	void * ptr;

	while ( 1 )
	{
		// Primer obtenim informació. Aquest serà responsable de fer el seu propi malloc.
		ptr = f_getData ();

		// Comprovem que no sigui el estat final.
		if ( ptr == NULL )
		{
			cbuffer_end ();
			return NULL;
		}

		// Escribim la informació al buffer.
		cbuffer_push ( ptr );
	}
}

void* _consumer(void* n)
{
	void * ptr;

	while ( 1 )
	{
		// Obtenim la informació.
		ptr = cbuffer_get ();

		// Comprovem que no sigui el final.
		if ( ptr == NULL ) return NULL;

		// Prosesem la informació.
		f_processData ( ptr );
	}
}

void _threadCreate ( pthread_t * pt, void * (*f) (void *) )
{
	if ( (pthread_create (pt, NULL, f, NULL)) )
	{
		printf ("Error, pthread_create\n");
		exit(1);
	}
}
