#ifndef EXEC_H
#define EXEC_H

#include "defs.h"
#include "types.h"
#include "utils.h"
#include "freecmd.h"

extern struct cmd* parsed_pipe;

void get_environ_key(char* arg, char* key);
void get_environ_value(char* arg, char* value, int idx);
void exec_cmd(struct cmd* c);

#endif // EXEC_H
