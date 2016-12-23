CC = gcc
CFLAGS = -Wall -g -std=c11 -O3
LIBS = -l m -l pthread

# Sources here
SRCS = main.c util.c serialize/serializer.c rb-tree/red-black-tree.c hash/hash.c linked-list/linked-list.c read/easy-read.c menu/menu.c threaded_task/thread_task.c cbuffer/cbuffer.c
OBJS = $(SRCS:.c=.o)

# !!! Insert executable name here (.exe for win32) !!!
MAIN = main.exe

all: $(MAIN)
	@echo Compilation successful

# Main target depends on all other objects being compiled
$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

# Compile all .o from sources
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

# Cleanup, including executable
clean:
	find . -name "*.o" -type f -delete
#$(RM) *.o *~

clean-all:
	$(RM) *.o *~ $(MAIN)
