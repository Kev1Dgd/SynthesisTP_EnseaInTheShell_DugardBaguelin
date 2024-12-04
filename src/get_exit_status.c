
#include "../include/get_exit_status.h"

int get_exit_status(int status) {
    if (WIFEXITED(status)) { // Normal end
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) { // End decided by a signal
        return WTERMSIG(status);
    }
}