#include "builtin.h"

// returns true if the 'exit' call
// should be performed
int exit_shell(char* cmd) {
	int idx = 0;

	char* tok = get_token(cmd, idx);

	if (strcmp("exit",tok) == 0)
		return 1;

	return 0;
}

// returns true if "chdir" was performed
// this means that if 'cmd' contains:
// 	$ cd directory (change to 'directory')
// 	$ cd (change to HOME)
// it has to be executed and then return true
int cd(char* cmd) {
	int idx = 0;

	char* tok = get_token(cmd, idx);

	if (strcmp("cd",tok) != 0) {
		return 0;
	} else {
		struct execcmd* p_cmd  = (struct execcmd*)parse_line(cmd);
		if (chdir (p_cmd->argv[1]) != 0) {
			perror("Error:");
		}
		char * dir = get_current_dir_name();
		if (dir == NULL)
			perror("Error:");

		strcpy(promt,dir);
	}

	return 1;
}

// returns true if 'pwd' was invoked
// in the command line
int pwd(char* cmd) {
	int idx = 0;

	char* tok = get_token(cmd, idx);

	if (strcmp("pwd",tok) != 0) {
		return 0;
	} else {
		char * dir = get_current_dir_name();
		if (dir == NULL)
			perror("Error:");

		printf("%s\n", dir);
	}

	return 1;
}
