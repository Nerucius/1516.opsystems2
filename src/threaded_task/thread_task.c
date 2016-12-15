#include <stdio.h>
#include <pthread.h>

#include "../cbuffer/cbuffer.h"

void* (*f_getData) (void);
void (*f_processData) (void *)

int status = 0;


void tt_init(void* (*_f_getData) (void), void (*_f_processData) (void *)){
  
  f_getData = _f_getData;
  f_processData = _f_processData;
  
  status = 1;

}


void tt_executeTast(int num_consumers, int buffer_size){
  
  
}

void* _producer(void*){
  
  return;
}

void* _consumer(void*){
  
  return;
}