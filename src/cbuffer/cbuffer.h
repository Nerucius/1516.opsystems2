/**
  * Funció per inicialitzar el buffer.
  * Pots canviar el tamany del buffer tornant a cridar la funció.
  *
  * Nota: Vigilar que pedreu la informació que hi hagi al cridar aquesta funció si n'hi havia.
  * Nota: Per alliberar la memòria reservada al cridar aquesta funció, fer cbuffer_free ();
  * Nota: Necessari cridar aquesta funció si ha sigut cridat cbuffer_end (); i es vol tornar a usar el cbuffer.
  *
  * @param size
  * És el tamany del buffer que vols reservar.
  * Si aquest és menor o igual a zero, farà un exit 1.
  */
void cbuffer_init ( int size );

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
void cbuffer_push ( void * data );

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
void * cbuffer_get ( void );

/**
  * Funció per alliberar en memòria el que s'ha reservat al fer cbuffer_init.
  */
void cbuffer_free ( void );

/**
  * Nota: Per indicar als fils que fan el get, finalitzar fent: cbuffer_push ( NULL );
  */
void cbuffer_end ( void );
