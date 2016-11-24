#include "hash.h"

// Seed per a fer el nostre hash.
#define SEED 131

/**
  * Funció per a extreure la clau de l'element.
  * Funció copiada exactament al exemple donat.
  */
int hashCode (char* str)
{
	int sum, seed, i, len;

	sum = 0;
	seed = SEED;
	len = 3;	// Per l'enunciat 1, només són els 3 primers caràcters.

	for(i = 0; i < len; i++)
		sum = sum * seed + (int)str[i];
	
	return sum % HASH_SIZE;
}
