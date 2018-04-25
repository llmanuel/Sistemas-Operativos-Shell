#include "exec.h"

// sets the "key" argument with the key part of
// the "arg" argument and null-terminates it
static void get_environ_key(char* arg, char* key) {

	int i;
	char tmp[ARGSIZE] = {0};
	for (i = 0; arg[i] != '='; i++)
		tmp[i] = arg[i];

	tmp[i] = END_STRING;
	strcpy(key,tmp);
}

// sets the "value" argument with the value part of
// the "arg" argument and null-terminates it
static void get_environ_value(char* arg, char* value, int idx) {

	int i, j;
	char tmp[ARGSIZE] = {0};
	for (i = (idx + 1), j = 0; i < strlen(arg); i++, j++)
		tmp[j] = arg[i];

	tmp[j] = END_STRING;
	strcpy(value,tmp);
}

// sets the environment variables passed
// in the command line
//
// Hints:
// - use 'block_contains()' to
// 	get the index where the '=' is
// - 'get_environ_*()' can be useful here
static void set_environ_vars(char** eargv, int eargc) {
	int i;
	for (i = 0; i < eargc; i++) {
		char key[ARGSIZE] = {0}, value[ARGSIZE] = {0};
		get_environ_key(*(eargv+i), key);
		get_environ_value(*(eargv+i), value, strlen(key));
		
		if (setenv((const char *)key, (const char *)value, 1) != 0) {
			perror("Error:");
		}
	}

}

// opens the file in which the stdin/stdout or
// stderr flow will be redirected, and returns
// the file descriptor
//
// Find out what permissions it needs.
// Does it have to be closed after the execve(2) call?
//
// Hints:
// - if O_CREAT is used, add S_IWUSR and S_IRUSR
// 	to make it a readable normal file
static int open_redir_fd(char* file) {

	// Your code here
	return -1;
}

// executes a command - does not return
//
// Hint:
// - check how the 'cmd' structs are defined
// 	in types.h
void exec_cmd(struct cmd* cmd) {

	struct execcmd* c = (struct execcmd*)cmd;
	if (c->eargc > 0) {
		set_environ_vars(c->eargv, c->eargc);
	}

	switch (cmd->type) {

		case EXEC: {
			// spawns a command
			execvp(c->argv[0], c->argv);

			printf("The command '%s' doesn't exist %s\n", c->argv[0], strerror(errno));
			_exit(0);
			break;
		}
		case BACK: {
			// runs a command in background
			//
			// Your code here
			printf("Background process are not yet implemented\n");
			_exit(-1);
			break;
		}

		case REDIR: {
			// changes the input/output/stderr flow
			//
			// Your code here
			printf("Redirections are not yet implemented\n");
			_exit(-1);
			break;
		}

		case PIPE: {
			// pipes two commands
			//
			// Your code here
			printf("Pipes are not yet implemented\n");

			// free the memory allocated
			// for the pipe tree structure
			free_command(parsed_pipe);

			break;
		}
	}
}
