
#include "../include/get_exit_status.h"

void get_exit_status(int status, char* buffer) {
    if (WIFEXITED(status)) { // Normal end
        sprintf(buffer, "exit:%d", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) { // End decided by a signal
        sprintf(buffer, "sign:%d", WTERMSIG(status));
    }
}