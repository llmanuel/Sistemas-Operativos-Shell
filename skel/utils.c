#include "utils.h"

// counts how many times the caracter token appears in the string str
// returning the value in count
	void count_character(const char *str, char token, size_t count) {
	count = 0;
  while(*str != END_STRING)
		if (*str++ == token) ++count;
}

// splits a string line in two
// acording to the splitter character
char* split_line(char* buf, char splitter) {

	int i = 0;

	while (buf[i] != splitter &&
		buf[i] != END_STRING)
		i++;

	buf[i++] = END_STRING;

	while (buf[i] == SPACE)
		i++;

	return &buf[i];
}

// looks in a block for the 'c' character
// and returns the index in which it is, or -1
// in other case
int block_contains(char* buf, char c) {

	for (int i = 0; i < strlen(buf); i++)
		if (buf[i] == c)
			return i;

	return -1;
}
