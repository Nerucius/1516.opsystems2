#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

/* Variables globals */

// Buffer, on emmagatzenem la informació.
void * buffer = NULL;	// Inicialitzem que és null, per fer el cbuffer_init coherent.
int buffer_size = 0;	// Inicialitzem a zero.

// Semafors productor i consumidor.
sem_t productor_semaphore, consumitor_semaphore;

// Moment crític, lectura del punter del buffer.
pthread_mutex_t consumitor_read;

// Punters relatius al buffer.
int productor_pointer, consumitor_pointer;

// Condició final per saber si els cbuffer_get han de finalitzar o no.
int productor_end;


/* Funcions publiques */


/**
  * Funció per inicialitzar el buffer.
  * Pots canviar el tamany del buffer tornant a cridar la funció.
  *
  * Funció important per a definir les variables globals.
  *
  * Nota: Vigilar que pedreu la informació que hi hagi al cridar aquesta funció si n'hi havia.
  * Nota: Per alliberar la memòria reservada al cridar aquesta funció, fer cbuffer_free ();
  *
  * @param size
  * És el tamany del buffer que vols reservar.
  */
void cbuffer_init ( int size )
{
	// Proteixim de casos sense sentit.
	if ( size < 0 ) return;

	// Definim el tamany del buffer.
	buffer_size = size;

	// En cas de tenir un buffer, s'encanregarà de ser coherent. Tot i que pedrem la informació.
	buffer = realloc ( buffer, buffer_size * sizeof (void *) );

	// Assegurem que tot hagi funcionat correctament.
	if ( buffer == NULL )
	{
		printf ("ERROR: malloc cbuffer\n");
		exit (1);
	}

	// Els semafors.
	sem_init ( &productor_semaphore, 0, buffer_size );
	sem_init ( &consumitor_semaphore, 0, 0 );

	// Punters relatius;
	productor_pointer = 0;
	consumitor_pointer = 0;

	// Condició final per saber si els cbuffer_get han de finalitzar o no.
	productor_end = 0;
}

/**
  * Funció per poder afegir elements al buffer.
  * Bloqueixarà el fil en execució si no queda memòria al buffer lliure.
  *
  * Nota: Per indicar als fils que fan el get, finalitzar fent: cbuffer_push ( NULL );
  * Nota: Si vols reutilitzar el buffer, només cal fer de nou: cbuffer_push ( data );
  *
  * @param data
  * És la informació que vols enmagatzemar al buffer. És un buffer de punters.
  * Això implica que tot haurà de ser reservat fora d'aquest buffer.
  */
void cbuffer_push ( void * data )
{
	// Comprova si és el final pels cbuffer_get.
	if ( data == NULL )
	{
		productor_end = 1;			// Definim estat final.
		sem_post (&consumitor_semaphore);	// Despertem un.
		return;
	} else productor_end = 0;
}
