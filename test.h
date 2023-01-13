#ifndef TEST_H
#define TEST_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 25
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char    *get_next_line(int fd);

#endif