#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "cbuffer.h"

int main(void){
  
  printf("Unit test for CBUFFER.h\n");
  
  char* str1 = "Test String 1";
  char* str2 = "Test String 2";
  
  cbuffer_init(16);
  
  cbuffer_push(str1);
  cbuffer_push(str2);
  
  char* getstr = cbuffer_get();
  printf("%s\n", getstr);
  getstr = cbuffer_get();
  printf("%s\n", getstr);
    
  return 0;
}