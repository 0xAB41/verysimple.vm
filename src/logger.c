#include "../include/logger.h"
#include <stdio.h>

static int log_level = VERYSIMPLE_VM_LOG_DEBUG;

void log_set_level(int level) {
    log_level = level;
}

void log_msg(int level, const char *msg, ...) {
    if (log_level <= level) {
        va_list args;
        va_start(args, msg);
        vfprintf(stderr, msg, args);
        va_end(args);
    }
}