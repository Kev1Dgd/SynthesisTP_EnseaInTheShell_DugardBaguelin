#include "../include/utils.h"

void print(char* str) {
    write(STDOUT_FILENO, str, strlen(str));
}
