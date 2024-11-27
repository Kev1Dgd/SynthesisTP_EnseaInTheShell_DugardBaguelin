#ifndef REPL_H
#define REPL_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "utils.h"

#define CMD_BUFFER_SIZE 256


void repl();

#endif