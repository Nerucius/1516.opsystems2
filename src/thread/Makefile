LIBS = -l pthread -g
LIBS_MAIN = thread_prod_cons.h
FILES_O_IN = thread_prod_cons.o
all: $(FILES_O_IN) main

main: main.o $(FILES_O_IN)
	gcc $(FILES_O_IN) main.o -o main $(LIBS) -Wall

main.o: main.c
	gcc main.c -c -Wall

thread_prod_cons.o: thread_prod_cons.c thread_prod_cons.h
	gcc thread_prod_cons.c -c -Wall

clean:
	rm main main.o $(FILES_O_IN) -f
