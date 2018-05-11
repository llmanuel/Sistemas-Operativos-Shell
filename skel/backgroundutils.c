#include "backgroundutils.h"

size_t posBack = 0;
pid_t back_pid = {0};
char array_back_scmd[MAX_BACK] = {0};

int set_background_variables(struct cmd* cmd, pid_t pidChild) {
    back_pid = pidChild;
    // size_t size = strlen(cmd->scmd);
    // array_back_scmd[posBack] = (char*) malloc(sizeof(char) * (size+1));
    strcpy(array_back_scmd, cmd->scmd);
    posBack++;

    if (posBack >= MAX_BACK) posBack = 0;
    print_back_info(cmd);
    return true;
}

void handle(int signum, siginfo_t* info, void* context) {

			printf ("==> terminado: PID=%d (%s)\n", back_pid, array_back_scmd);
			// free(array_back_scmd[0]);

}

void change_sgichld_signal() {
    struct sigaction act;
    act.sa_sigaction = handle;
    act.sa_flags = SA_SIGINFO | SA_RESTART;
    // act.sa_flags = SA_SIGINFO;
    if (sigaction(SIGCHLD, &act, NULL) == -1)
        perror("ERROR: sigaction() failed");

}
