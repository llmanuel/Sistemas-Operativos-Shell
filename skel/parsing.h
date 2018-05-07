#ifndef PARSING_H
#define PARSING_H

#include "defs.h"
#include "types.h"
#include "createcmd.h"
#include "utils.h"

extern int status;

struct cmd* parse_line(char* b);

char* get_token(char* buf, int idx);

#endif // PARSING_H
