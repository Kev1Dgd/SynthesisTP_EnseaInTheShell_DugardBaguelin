
#include "../include/display_exit_status.h"

void display_exit_status(int status, char *prompt) {
    if (WIFEXITED(status)) { // fin normal
        int exit_code = WEXITSTATUS(status);
        sprintf(prompt, "enseash [exit:%d] %% ", exit_code);
    } else if (WIFSIGNALED(status)) { // fin décidée par un signal
        int signal_number = WTERMSIG(status);
        sprintf(prompt, "enseash [sign:%d] %% ", signal_number);
    }
}