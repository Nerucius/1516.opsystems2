# Genera els executables i el main per a que pugui ser executat.

# Fitxers externs a compilar per separat.
FILES_O_OUT = ../llegir-csv/easyRead.o ../hash/hash.o ../util.o ../main.o

# Quan unim tots els fitxers.
FILES_O_IN  =               easyRead.o         hash.o    util.o    main.o

# Compilation options
CFLAGS = -Wall -Werror -g

# Linker options 
LFLAGS = -lm

# Exectuable to generate
TARGET = main

# main
main: $(FILES_O_OUT) Makefile
	gcc $(FILES_O_IN) -o $(TARGET) $(LFLAGS)

# Llibreries
%.o: %.c Makefile
	gcc $(CFLAGS) -c $<

# Elimina tot el generat
clean:
	rm $(FILES_O_IN) $(TARGET) -f
