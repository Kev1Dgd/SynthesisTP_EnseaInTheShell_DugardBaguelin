#include "../include/get_exit_status.h"

int calculate_duration(struct timespec timer_finish, struct timespec timer_start) {
    long seconds = timer_finish.tv_sec - timer_start.tv_sec;
    long nanoseconds = timer_finish.tv_nsec - timer_start.tv_nsec;
    return (int)((seconds + nanoseconds * 1e-9) * 1000);
}