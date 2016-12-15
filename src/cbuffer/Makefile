cbuffer.o: cbuffer.c Makefile
	gcc cbuffer.c -c -Wall -g

	
test: cbuffer.o
	gcc -o test test.c cbuffer.o -lpthread && ./test