#ifndef BACKGROUNDUTILS_H
#define BACKGROUNDUTILS_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "defs.h"
#include "types.h"
#include "printstatus.h"
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAX_BACK 200

extern pid_t array_back_pid[MAX_BACK];
extern char* array_back_scmd[MAX_BACK];
extern size_t posBack;
extern size_t posBack;

void change_sgichld_signal();

void handle(int signum, siginfo_t* info, void* context);

int execBackground(struct cmd* cmd, pid_t pidChild);

#endif // UTILS_H
