#include <stdio.h>
#include <string.h> 
#include "hash.h"

// Seed per a fer el nostre hash.
#define SEED 131

int hashCode (char* str)
{
	int sum, seed, i, len;

	sum = 0;
	seed = SEED;
	len = strlen ( str );

	for(i = 0; i < len; i++)
		sum = sum * seed + (int)str[i];
	
	return sum % HASH_SIZE;
}
