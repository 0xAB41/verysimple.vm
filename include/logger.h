#ifndef VERYSIMPLE_VM_LOGGER_H
#define VERYSIMPLE_VM_LOGGER_H

#include <stdarg.h>

enum {
    VERYSIMPLE_VM_LOG_DEBUG,
    VERYSIMPLE_VM_LOG_ERROR
};

#define log_debug(...) log_msg(VERYSIMPLE_VM_LOG_DEBUG, __VA_ARGS__)
#define log_error(...) log_msg(VERYSIMPLE_VM_LOG_ERROR, __VA_ARGS__)

void log_msg(int level, const char *msg, ...);

void log_set_level(int level);

#endif
