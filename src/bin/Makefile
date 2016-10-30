# Genera els executables i el main per a que pugui ser executat.
# Millorar 54,852 allocs per defecte !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

# Dependencies del main.
LIBS_MAIN =	../util.h ../hash/hash.h ../llegir-csv/easyRead.h ../linked-list/linked-list.h \
		../arbre-binari/red-black-tree.h \
		../def.h

# Quan unim tots els fitxers.
FILES_O_IN = util.o hash.o easyRead.o linked-list.o red-black-tree.o main.o

# Compilation options
CFLAGS = -Wall -Werror -g

# Linker options 
LFLAGS =	-l m

# Exectuable to generate
TARGET = main

# main
main: $(FILES_O_IN) Makefile
	gcc $(FILES_O_IN) -o $(TARGET) $(LFLAGS)

main.o: $(LIBS_MAIN) ../main.c Makefile
	gcc $(CFLAGS) -c ../main.c

# Llibreries
%.o: %.c Makefile
	gcc $(CFLAGS) -c $<
easyRead.o: ../llegir-csv/easyRead.c ../llegir-csv/easyRead.h Makefile
	gcc $(CFLAGS) -c ../llegir-csv/easyRead.c
hash.o: ../hash/hash.c ../hash/hash.h Makefile
	gcc $(CFLAGS) -c ../hash/hash.c
util.o: ../util.c ../util.h Makefile
	gcc $(CFLAGS) -c ../util.c
linked-list.o: ../linked-list/linked-list.c ../linked-list/linked-list.h Makefile
	gcc $(CFLAGS) -c ../linked-list/linked-list.c
red-black-tree.o: ../arbre-binari/red-black-tree.c ../arbre-binari/red-black-tree.h Makefile
	gcc $(CFLAGS) -c ../arbre-binari/red-black-tree.c

# Elimina tot el generat
clean:
	rm $(FILES_O_IN) $(TARGET) -f
