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

	return open(file, O_CREAT | O_APPEND | O_WRONLY, 0664);
}

static int there_is_another_cmd(int cant_cmd, int count) {
	if ((cant_cmd - count) > 0)
		return 1;

	return 0;
}

static void write_pipe_and_close(int* pipefd) {

	if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1) {
		perror("Error: ");
	}
	close(pipefd[WRITE_END]);
	close(pipefd[READ_END]);
}

static void read_pipe_and_close(int* pipefd) {

	if (dup2(pipefd[READ_END], STDIN_FILENO) == -1) {
		perror("Error: ");
	}
	close(pipefd[READ_END]);
	close(pipefd[WRITE_END]);

}

static void process_middle_pipes(int* pipefd_in, int* out) {

}


// executes a command - does not return
//
// Hint:
// - check how the 'cmd' structs are defined
// 	in types.h
void exec_cmd(struct cmd* cmd) {

	struct execcmd* c = (struct execcmd*)cmd;
	if (c->type != PIPE && c->eargc > 0) {
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
			struct backcmd* cmd_b = (struct backcmd*)cmd;
			exec_cmd(cmd_b->c);
			_exit(0);
			break;
		}

		case REDIR: {
			// changes the input/output/stderr flow

			int fd = -1;
			int new_fd = -1;
			if (strlen(c->out_file) > 0) {
				fd = open_redir_fd(c->out_file);
				new_fd = dup2(fd, 1);
				close(fd);
			}
			if (strlen(c->in_file) > 0) {
				fd = open(c->in_file, O_RDWR);
				new_fd = dup2(fd, 0);
				close(fd);
			}
			if (strlen(c->err_file) > 0) {
				if (block_contains(c->err_file, '&') >= 0) {
					new_fd = dup2(STDOUT_FILENO, 2);
				} else {
					fd = open_redir_fd(c->err_file);
					new_fd = dup2(fd, 2);
					close(fd);
				}
			}

			if (new_fd == -1)
				perror("Error: ");

			c->type = EXEC;
			exec_cmd((struct cmd*)c);
			_exit(-1);
			break;
		}

		case PIPE: {
			// pipes two commands
			struct pipecmd* cmd_p = (struct pipecmd*)cmd;

			int * pipefd = (int*)calloc((cmd_p->cant_cmd-1)*2,sizeof(int));
			if (pipe(pipefd) == -1) {
				perror("Error creation of first pipe: ");
			}

			pid_t first;
			if ((first=fork()) == 0) {
				write_pipe_and_close(pipefd );

				exec_cmd(cmd_p->array_cmd[0]);
			}
			waitpid(first, 0, 0);

			int i = 1;
			if (cmd_p->cant_cmd > 2) {
				printf("paso\n");
				// loop middle pipes
				for (i = 1; i < cmd_p->cant_cmd - 1; i++) {
					pid_t next;
					if (pipe(pipefd + (2*i)) == -1) {
						perror("Error creation of first pipe: ");
					}
					if ((next=fork()) == 0) {
						read_pipe_and_close(pipefd + (2*(i-1)));


						write_pipe_and_close(pipefd + (2*i));
						exec_cmd(cmd_p->array_cmd[i]);
					}
					close(pipefd[(2*(i-1)) + READ_END]);
					close(pipefd[(2*(i-1)) + WRITE_END]);
					waitpid(next, 0, 0);
				}
			}

			// last
			pid_t last;
			if ((last=fork()) == 0) {
				read_pipe_and_close(pipefd + (2*(i-1)));

				exec_cmd(cmd_p->array_cmd[i]);
			}
			close(pipefd[(2*(i-1)) + READ_END]);
			close(pipefd[(2*(i-1)) + WRITE_END]);
			waitpid(last, 0, 0);

			// // free the memory allocated
			// // for the pipe tree structure
				free_command(parsed_pipe);

			break;
		}
	}
}
