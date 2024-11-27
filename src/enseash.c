#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void print(char* str) {
    write(STDOUT_FILENO, str, strlen(str));
}

int main() {
    print("Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n");

    return 0;
}