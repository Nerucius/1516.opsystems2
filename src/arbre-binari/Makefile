# This is the makefile that generates the executable

# Files to compile
#FILES_C = main.c red-black-tree.c
FILES_C = red-black-tree.c

# Exectuable to generate
#TARGET = main

# Compilation options
CFLAGS = -Wall -Werror -g

# Linker options 
LFLAGS = -lm

# There is no need to change the instructions below this
# line. Change if you really know what you are doing.

FILES_O = $(subst .c,.o,$(FILES_C))

#$(TARGET): $(FILES_O) Makefile
#	gcc $(FILES_O) -o $(TARGET) $(LFLAGS) 

%.o: %.c Makefile
	gcc $(CFLAGS) -c $<

#all: $(TARGET) 

clean:
	rm $(FILES_O) -f
# $(TARGET) 
