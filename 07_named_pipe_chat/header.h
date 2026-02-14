#ifndef HEADER_H

#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

#define MAX 1024
#define TRUE    1

extern char in_line[];
extern char out_line[];
extern int infd,outfd;
extern ssize_t n;

#endif