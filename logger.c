#include "logger.h"
#include <stdarg.h>
#include <stdio.h>

void log(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
}