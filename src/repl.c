#include "../include/repl.h"
#include "../include/detect_exit.h"
#include "../include/get_exit_status.h"
#include "../include/calculate_duration.h"


void repl() {
    struct timespec timer_start, timer_finish;  
    int status_code;  
    char command[CMD_BUFFER_SIZE];
    ssize_t bytes_read;
    int status;
    size_t command_length = 0; // To track the length of the command read
    char prompt[64] = "enseash % ";

    while (1) {
        print(prompt);
        command_length = 0; // Reset order length

        // Reading the order
        while ((bytes_read = read(STDIN_FILENO, command + command_length, 1)) > 0) {
            // Check end of command with '\n'.
            if (command[command_length] == '\n') {
                command[command_length] = '\0'; // End chain
                break;
            }
            command_length++;
            // Limit command to CMD_BUFFER_SIZE
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
            // Child process: execute command
            if (strcmp(command, "") == 0) {
                execl("/bin/sh", "sh", "-c", "date", (char *)NULL);
            } else {
                execl("/bin/sh", "sh", "-c", command, (char *)NULL);
            }
            exit(0);
        } else {
            // Parent process: wait for command to complete
            wait(&status);
            clock_gettime(CLOCK_REALTIME, &timer_finish);
            status_code = get_exit_status(status);
        }

        int elapsed_ms = calculate_duration(timer_finish, timer_start); 
        sprintf(prompt, "enseash [exit:%d|%dms] %% ", status_code, elapsed_ms);
    }
}