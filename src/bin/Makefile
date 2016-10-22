# Genera els executables i el main per a que pugui ser executat.

# Fitxers externs a compilar per separat.
FILES_O_OUT = ../llegir-csv/easyRead.o ../hash/hash.o ../util.o ../main.o

# Quan unim tots els fitxers.
FILES_O_IN  = easyRead.o hash.o util.o main.o linked-list.o

# Compilation options
CFLAGS = -Wall -Werror -g

# Linker options 
LFLAGS = -lm

# Exectuable to generate
TARGET = main

# main
main: $(FILES_O_IN) Makefile
	gcc $(FILES_O_IN) -o $(TARGET) $(LFLAGS)

main.o: ../main.c Makefile
	gcc $(CFLAGS) -c ../main.c

# Llibreries
%.o: %.c Makefile
	gcc $(CFLAGS) -c $<
easyRead.o: ../llegir-csv/easyRead.c Makefile
	gcc $(CFLAGS) -c ../llegir-csv/easyRead.c
hash.o: ../hash/hash.c Makefile
	gcc $(CFLAGS) -c ../hash/hash.c
util.o: ../util.c Makefile
	gcc $(CFLAGS) -c ../util.c
linked-list.o: ../linked-list/linked-list.c Makefile
	gcc $(CFLAGS) -c ../linked-list/linked-list.c


# Elimina tot el generat
clean:
	rm $(FILES_O_IN) $(TARGET) -f
