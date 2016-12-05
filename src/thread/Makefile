LIBS = -l pthread
LIBS_MAIN = thread_prod_cons.h
FILES_O_IN = thread_prod_cons.o
all: $(FILES_O_IN) main

main: main.o $(FILES_O_IN)
	gcc $(FILES_O_IN) main.o -o main $(LIBS)

main.o: main.c
	gcc main.c -c

thread_prod_cons.o: thread_prod_cons.c thread_prod_cons.h
	gcc thread_prod_cons.c -c

clean:
	rm main main.o $(FILES_O_IN) -f
