FILES_O = read.o

# Exectuable to generate
TARGET = read

# Compilation options
CFLAGS = -Wall -Werror -g

# Linker options 
LFLAGS = -lm

read.o: read.c
	gcc $(CFLAGS) read.c -c

clean:
	rm $(FILES_O) -f
