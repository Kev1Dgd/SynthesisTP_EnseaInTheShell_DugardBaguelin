#include "../include/repl.h"
#include "../include/detect_exit.h"

void repl() {
    char command[CMD_BUFFER_SIZE];
    ssize_t bytes_read;
    int status;
    size_t command_length = 0; // Pour suivre la longueur de la commande lue

    while (1) {
        print("enseash % ");
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

        pid_t pid = fork();

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
        }
    }
}