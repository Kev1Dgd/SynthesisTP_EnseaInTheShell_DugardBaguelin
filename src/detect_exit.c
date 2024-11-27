#include "../include/detect_exit.h"

int detect_exit(ssize_t bytes_read, char *command) {
    // Détection d'un CTRL+D
    if (bytes_read == 0) {
        print("\nBye bye...\n");
        return 1;
    }

    if (strcmp(command, "exit") == 0) {
        print("Bye bye...\n");
        return 1;
    }

    return 0;
}