# Genera els executables i el main per a que pugui ser executat.

# Fitxers externs a compilar
FILES_O_OUT = llegir-csv/read.o arbre-binari/red-black-tree.o linked-list/linked-list.o
#linked-list/

# Compilation options
CFLAGS = -Wall -Werror -g

# Linker options 
LFLAGS = -lm

# Exectuable to generate
TARGET = main

main: $(FILES_O_OUT) main.o
	gcc $(FILES_O_OUT) main.o -o $(TARGET) $(LFLAGS)

llegir-csv/read.o: llegir-csv/read.c
	cd llegir-csv; make clean; make read.o
linked-list/linked-list.o: linked-list/linked-list.c
	cd linked-list; make clean; make linked-list.o

clean:
	cd arbre-binari; make clean
	cd llegir-csv; make clean
	rm main.o main -f
