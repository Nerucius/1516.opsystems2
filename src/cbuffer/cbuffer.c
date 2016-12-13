#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

/* Variables globals */

// Buffer, on emmagatzenem la informació.
void ** buffer = NULL;	// Inicialitzem que és null, per fer el cbuffer_init coherent.
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
  * Nota: Necessari cridar aquesta funció si ha sigut cridat cbuffer_end (); i es vol tornar a usar el cbuffer.
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
	buffer = (void **) realloc ( buffer, buffer_size * sizeof (void *) );

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
  * Nota: Per indicar als fils que fan el get, finalitzar fent: cbuffer_end ();
  * Nota: Si vols reutilitzar el buffer, només cal fer de nou: cbuffer_init ( size );
  *
  * @param data
  * És la informació que vols enmagatzemar al buffer. És un buffer de punters.
  * Això implica que tot haurà de ser reservat fora d'aquest buffer.
  */
void cbuffer_push ( void * data )
{
	// Comprova si és el final pels cbuffer_get.
/*	if ( data == NULL )
	{
		productor_end = 1;			// Definim estat final.
		sem_post (&consumitor_semaphore);	// Despertem un.
		return;
	} else productor_end = 0;
*/
	// Comprovem que estigui en un estat lògic.
	if ( productor_end )
	{
		printf ( "ERROR: posant informació cbuffer quan ha finalitzat!\n" );
		printf ( "Fer un cbuffer_init (int size) abans de tornar a cridar cbuffer_push\n" );
		exit (1);
	}

	// Dormirem si no hi ha memòria lliure al buffer.
	sem_wait ( &productor_semaphore );

		// Escriu el punter en buffer i actualitza el punter relatiu.
		buffer [ productor_pointer ] = data;
		productor_pointer = (productor_pointer +1) % buffer_size;

	// Despertarem als consumidors.
	sem_post ( &consumitor_semaphore );
}

/**
  * Funció per recuperar la informació emmagatzemada  cbuffer_push.
  * Bloqueixarà el fil en execució si no hi ha res per llegir.
  *
  * Nota: Per acabar amb aquests fils, s'haurà de fer un: cbuffer_end ();
  *
  * @return
  * Retorna el punter emmagatzemat al cbuffer_push.
  * Retorna NULL si no ha pogut llegir res hi ha sigut cridat cbuffer_end ();
  */
void * cbuffer_get ( void )
{
	// Declarem la variable data que retornarem.
	void * data;

	// Primer espera a tenir permisos per a fer res.
	sem_wait ( &consumitor_semaphore );

		// Entrem a la zona delicada.
		pthread_mutex_lock ( &consumitor_read );

			// Comprovem si s'ha cridat la funció cbuffer_end ();
			if ( productor_end )
				if ( consumitor_pointer == productor_pointer )
				{
					pthread_mutex_unlock ( &consumitor_read );	// Desbloqueixem aquest control.
					sem_post ( &consumitor_semaphore );		// Alliberem els fils necessaris.
					return NULL;
				}

			// Recupera el punter del buffer i actualitza el punter relatiu.
			data = buffer [ consumitor_pointer ];
			consumitor_pointer = (consumitor_pointer +1) % buffer_size;

		// Acaba la zona delicada
		pthread_mutex_unlock ( &consumitor_read );

	// Podem alliverar el productor.
	sem_post ( &productor_semaphore );

	// Retornem la informació obtinguda.
	return data;
}

/**
  * Funció per alliberar en memòria el que s'ha reservat al fer cbuffer_init.
  */
void cbuffer_free ( void )
{
	// Ens assegurem que no sigui cridat quan el buffer no és res.
	if ( buffer == NULL ) return;

	// Memoria alliberada.
	free ( buffer );
}

/**
  * Nota: Per indicar als fils que fan el get, finalitzar fent: cbuffer_push ( NULL );
  */
void cbuffer_end ( void )
{
	// Canviem una variable per a saber els consumidors quan acabar.
	productor_end = 1;

	// Alliberem un fil per que aquests es desbloqueixin gradualment.
	sem_post ( &consumitor_semaphore );
}
