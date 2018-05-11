#include "backgroundutils.h"

size_t posBack = 0;
pid_t array_back_pid[MAX_BACK] = {0};
char* array_back_scmd[MAX_BACK] = {0};

int execBackground(struct cmd* cmd, pid_t pidChild) {
    array_back_pid[posBack] = pidChild;
    size_t size = strlen(cmd->scmd);
    array_back_scmd[posBack] = (char*) malloc(sizeof(char) * (size+1));
    strncpy(array_back_scmd[posBack], cmd->scmd, size+1);
    posBack++;

    if (posBack >= MAX_BACK) posBack = 0;
    print_back_info(cmd);
    return true;
}

void handle(int signum, siginfo_t* info, void* context) {
    pid_t p = 1;
    char* f = "hola";
		printf("estamo en el handler\n");
    int found = false;
		int i = 0;
		while ((i < MAX_BACK) && (!found)) {
        if (info->si_pid == array_back_pid[i]) {
					p = array_back_pid[i];
					f = array_back_scmd[i];
					found = true;
					printf("lo encontre\n");
				}
				i++;
    }
		// printf("array_back_pid[0]%d\n",array_back_pid[0]);
		// printf("info->si_pid%d\n",(int)info->si_pid );
    if (!found) {
			printf ("==> terminado: PID=%d (%s)\n", p, f);
			printf("lelgue loco\n");
			array_back_pid[i - 1] = -1;
			free(array_back_scmd[i - 1]);
		}
}

void change_sgichld_signal() {
    struct sigaction act;
    act.sa_sigaction = handle;
    act.sa_flags = SA_RESTART;
    // act.sa_flags = SA_SIGINFO;
    if (sigaction(SIGCHLD, &act, NULL) == -1)
        perror("ERROR: sigaction() failed");

}
