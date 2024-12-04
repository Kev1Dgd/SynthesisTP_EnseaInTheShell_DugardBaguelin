
#include "../include/display_exit_status.h"

void display_exit_status(int status, char *prompt) {
    if (WIFEXITED(status)) { // Normal end
        int exit_code = WEXITSTATUS(status);
        sprintf(prompt, "enseash [exit:%d] %% ", exit_code);
    } else if (WIFSIGNALED(status)) { // End decided by a signal
        int signal_number = WTERMSIG(status);
        sprintf(prompt, "enseash [sign:%d] %% ", signal_number);
    }
}