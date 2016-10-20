# Genera els executables i el main per a que pugui ser executat.

# Fitxers externs a compilar
FILES_O_OUT = llegir-csv/easyRead.o hash/hash.o
#linked-list/

# Compilation options
CFLAGS = -Wall -Werror -g

# Linker options 
LFLAGS = -lm

# Exectuable to generate
TARGET = main

# main
main: $(FILES_O_OUT) main.o
	gcc $(FILES_O_OUT) main.o -o $(TARGET) $(LFLAGS)

main.o: main.c
	gcc $(CFLAGS) main.c -c



# Llibreries
llegir-csv/easyRead.o: llegir-csv/easyRead.c
	cd llegir-csv; make clean; make easyRead.o
hash/hash.o: hash/hash.c
	cd hash; make clean; make hash/hash.o


clean:
	cd arbre-binari; make clean
	cd llegir-csv; make clean
	rm main.o main -f
