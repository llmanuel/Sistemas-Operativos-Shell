#ifndef BACKGROUNDUTILS_H
#define BACKGROUNDUTILS_H

#define _GNU_SOURCE

#include <errno.h>
#include "defs.h"
#include "types.h"
#include "printstatus.h"
#include <signal.h>
#include <sys/types.h>
#include "readline.h"
#define MAX_BACK 200

extern pid_t back_pid;
extern char array_back_scmd[MAX_BACK];
extern size_t posBack;
extern size_t posBack;

void change_sgichld_signal();

void handle(int signum, siginfo_t* info, void* context);

int set_background_variables(struct cmd* cmd, pid_t pidChild);

#endif // UTILS_H
