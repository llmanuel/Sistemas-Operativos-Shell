#ifndef UTILS_H
#define UTILS_H

#include "defs.h"

void count_character(const char *str, char token, size_t count);

char* split_line(char* buf, char splitter);

int block_contains(char* buf, char c);

#endif // UTILS_H
