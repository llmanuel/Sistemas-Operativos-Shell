#include "createcmd.h"

// creates an execcmd struct to store
// the args and environ vars of the command
struct cmd* exec_cmd_create(char* buf_cmd) {

	struct execcmd* e;

	e = (struct execcmd*)calloc(sizeof(*e), sizeof(*e));

	e->type = EXEC;
	strcpy(e->scmd, buf_cmd);

	return (struct cmd*)e;
}

// creates a backcmd struct to store the
// background command to be executed
struct cmd* back_cmd_create(struct cmd* c) {

	struct backcmd* b;

	b = (struct backcmd*)calloc(sizeof(*b), sizeof(*b));

	b->type = BACK;
	strcpy(b->scmd, c->scmd);
	b->c = c;

	return (struct cmd*)b;
}

// encapsulates two commands into one pipe struct
struct cmd* pipe_cmd_create(struct cmd** array_cmd) {
	printf("sizeof(array_cmd): %ld\n", (sizeof(array_cmd)/sizeof(struct cmd)));
	printf("command %s\n", array_cmd[0]->scmd);
	printf("type EXEC 1 | BACK 2| REDIR 3|PIPE 4: %d\n", array_cmd[0]->type);

	if ((sizeof(array_cmd)/sizeof(struct cmd)) == 1) {
		struct cmd* c = array_cmd[0];
		free(array_cmd);
		return c;
	}

	struct pipecmd* p;

	p = (struct pipecmd*)calloc(sizeof(*p), sizeof(*p));

	p->type = PIPE;
	p->array_cmd = array_cmd;

	return (struct cmd*)p;
}
