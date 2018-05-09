#include "freecmd.h"

// frees the memory allocated
// for the tree structure command
void free_command(struct cmd* cmd) {

	int i;
	struct pipecmd* p;
	struct execcmd* e;
	struct backcmd* b;

	if (cmd->type == PIPE) {

		p = (struct pipecmd*)cmd;

		int i;
		for (i = 0; i < (int)sizeof(p->array_cmd); i++) {
			free_command(p->array_cmd[i]);
		}

		free(p);
		return;
	}

	if (cmd->type == BACK) {

		b = (struct backcmd*)cmd;

		free_command(b->c);
		free(b);
		return;
	}

	e = (struct execcmd*)cmd;

	for (i = 0; i < e->argc; i++)
		free(e->argv[i]);

	for (i = 0; i < e->eargc; i++)
		free(e->eargv[i]);

	free(e);
}
