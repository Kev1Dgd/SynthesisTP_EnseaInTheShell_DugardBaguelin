#include "../include/repl.h"
#include "../include/detect_exit.h"
#include "../include/display_exit_status.h"

#include <time.h>

void repl() {
    struct timespec timer_start, timer_finish;    
    char command[CMD_BUFFER_SIZE];
    ssize_t bytes_read;
    int status;
    size_t command_length = 0; // Pour suivre la longueur de la commande lue
    char prompt[64] = "enseash % ";

    while (1) {
        print(prompt);
        command_length = 0; // Réinitialiser la longueur de la commande

        // Lecture de la commande
        while ((bytes_read = read(STDIN_FILENO, command + command_length, 1)) > 0) {
            // Vérifier la fin de la commande avec '\n'
            if (command[command_length] == '\n') {
                command[command_length] = '\0'; // Terminer la chaîne
                break;
            }
            command_length++;
            // Limiter la commande à CMD_BUFFER_SIZE
            if (command_length >= CMD_BUFFER_SIZE - 1) {
                command[CMD_BUFFER_SIZE - 1] = '\0';
                break;
            }
        }

        if (detect_exit(bytes_read, command) == 1) {
            break;
        }

        clock_gettime(CLOCK_REALTIME, &timer_start);
        pid_t pid = fork();
        
        // char a[30];
        // sprintf(a, "pid : %d\n", pid);
        // print(a);

        if (pid < 0) {
            print("Fork failed\n");
            continue;
        }

        if (pid == 0) {
            // Processus enfant : exécuter la commande
            if (strcmp(command, "") == 0) {
                execl("/bin/sh", "sh", "-c", "date", (char *)NULL);
            } else {
                execl("/bin/sh", "sh", "-c", command, (char *)NULL);
            }
            exit(0);
        } else {
            // Processus parent : attendre la fin de la commande
            wait(&status);
            clock_gettime(CLOCK_REALTIME, &timer_finish);
            display_exit_status(status, prompt);
        }

        long seconds = timer_finish.tv_sec - timer_start.tv_sec;
        long nanoseconds = timer_finish.tv_nsec - timer_start.tv_nsec;
        int elapsed_ms = (int)((seconds + nanoseconds * 1e-9) * 1000);
        
        sprintf(prompt, "enseash [exit:%d|%dms] %% ", status, elapsed_ms);
    }
}