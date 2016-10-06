FILES_O = read.o ../arbre-binari/red-black-tree.c

# Exectuable to generate
TARGET = read

# Compilation options
CFLAGS = -Wall -Werror -g

# Linker options 
LFLAGS = -lm


all: FILES_O
	gcc $(FILES_O) ../arbre-binari/red-black-tree.o -o $(TARGET) $(LFLAGS) 

read.o: read.c
	gcc $(CFLAGS) read.c -c

../arbre-binari/red-black-tree.o: ../arbre-binari/red-black-tree.c
	cd ../arbre-binari; make red-black-tree.o
