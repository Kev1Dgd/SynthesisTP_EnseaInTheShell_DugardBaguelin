#include "../include/repl.h"
#include "../include/detect_exit.h"
#include "../include/get_exit_status.h"
#include "../include/calculate_duration.h"

#define MAX_BG_PROCESSES 128

typedef struct {
    pid_t pid;
    char command[CMD_BUFFER_SIZE];
    struct timespec start_time;
    int active;
} BackgroundProcess;

void repl() {
    struct timespec timer_start, timer_finish;  
    char exit_status[30];  
    char command[CMD_BUFFER_SIZE];
    ssize_t bytes_read;
    int status;
    size_t command_length = 0; // To track the length of the command read
    char prompt[512] = "enseash % ";

    int bg_count = 0;
    BackgroundProcess bg_processes[MAX_BG_PROCESSES];

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

        if (pid < 0) {
            print("Fork failed\n");
            continue;
        }

        if (pid == 0) {
            // Child process: execute command
            if (strcmp(command, "") == 0) {
                // execl("/bin/sh", "sh", "-c", "date", (char *)NULL);
            } else {
                execl("/bin/sh", "sh", "-c", command, (char *)NULL);
            }
            exit(0);
        } else if (command_length > 0 && command[command_length - 1] == '&') {
            // Parent process starting new process
            bg_processes[bg_count].pid = pid;
            strcpy(bg_processes[bg_count].command, command);
            bg_processes[bg_count].start_time = timer_start;
            bg_processes[bg_count].active = 1;
            bg_count++;
            sprintf(prompt, "enseash [%d&] %% ", pid);
        } else { 
            // Parent process
            waitpid(pid, &status, 0);
            clock_gettime(CLOCK_REALTIME, &timer_finish);
            get_exit_status(status, exit_status);
            int elapsed_ms = calculate_duration(timer_finish, timer_start);
            sprintf(prompt, "enseash [%s|%dms] %% ", exit_status, elapsed_ms);
        }

        for (int i = 0; i < bg_count; i++) { 
            if (bg_processes[i].active) {
                int bg_status; 
                char bg_exit_status[30];
                struct timespec bg_finish;
                
    
                pid_t result = wait4(bg_processes[i].pid, &bg_status, WNOHANG, NULL); // non blocking

                if (result > 0) { 
                    bg_processes[i].active = 0; 
                    clock_gettime(CLOCK_REALTIME, &bg_finish);
                    
                    int elapsed_ms = calculate_duration(bg_finish, bg_processes[i].start_time);
                    get_exit_status(bg_status, bg_exit_status);
                    char process_priority = i == bg_count - 1 ? '+' : (i == bg_count - 2 ? '-' : ' ');
                    
                    sprintf(prompt, "[%d]%c Ended: %s\nenseash [%s|%dms] %% ", 
                        i + 1, // process number 
                        process_priority, // priority indicator + or - or nothing
                        bg_processes[i].command, // the command that was executed
                        bg_exit_status, // the process exit status
                        elapsed_ms // execution time
                    );
                }
            }
        }
    }
}