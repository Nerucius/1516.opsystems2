#ifndef EASY_READ_H
#define EASY_READ_H

void read_initFile(char *name);

void read_closeFile();

char** read_readLines(int requestedLines, int *realCount);

#endif /* EASY_READ_H */
