#ifndef EXEC_H
#define EXEC_H

#include "defs.h"
#include "types.h"
#include "utils.h"
#include "freecmd.h"
#include "parsing.h"

#define READ_END 0
#define WRITE_END 1
#define STDIN_FILENO 0
#define STDOUT_FILENO 1

extern struct cmd* parsed_pipe;

void exec_cmd(struct cmd* c);

#endif // EXEC_H
