#include <stdio.h>
#include <string.h> 
#include "hash.h"

int hashCode(char* str){
	len = strlen(str); 
	sum = 0;
	seed = 131;
	for(i = 0; i < len; i++)
	sum = sum * seed + (int)cadena[i];
	
	return sum % HASH_SIZE;
}