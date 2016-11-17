CC = gcc
CFLAGS = -Wall -Werror -g
LIBS = -lm

# Sources here
SRCS = menuTest.c menu.c ../serialize/serializer.c ../arbre-binari/red-black-tree.c
OBJS = $(SRCS:.c=.o)

# !!! Insert executable name here (.exe for win64) !!!
MAIN = menuTest.exe

all: $(MAIN)
	@echo Compilation successful
	# make clean

# Main target depends on all other objects being compiled
$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

# Compile all .o from sources
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

# Cleanup, including executable
clean:
	$(RM) *.o *~

clean-all:
	$(RM) *.o *~ $(MAIN)
