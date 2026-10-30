#include "log.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


static LogLevel g_level = LOG_LEVEL_INFO;
static bool g_color = true;

static const char *const level_names[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};
_Static_assert(sizeof level_names / sizeof level_names[0] == LOG_LEVEL_COUNT,
               "level_names does not match LogLevel");

static const char *const level_colors[] = {
    "\x1b[90m",  /* TRACE: grey */
    "\x1b[36m",  /* DEBUG: cyan */
    "\x1b[32m",  /* INFO:  green */
    "\x1b[33m",  /* WARN:  yellow */
    "\x1b[31m",  /* ERROR: red */
    "\x1b[1;31m" /* FATAL: bold red */
};
_Static_assert(sizeof level_colors / sizeof level_colors[0] == LOG_LEVEL_COUNT,
               "level_colors does not match LogLevel");

static const char *const color_reset = "\x1b[0m";


void log_set_level(const LogLevel level) {
    g_level = level;
}

LogLevel log_get_level(void) {
    return g_level;
}

void log_set_color(const bool enabled) {
    g_color = enabled;
}

static void log_vwrite(const LogLevel level, const char *file, const int line, const char *fmt, va_list args) {
    char buf_prefix[1024];

    const int len_prefix = snprintf(buf_prefix, sizeof buf_prefix, "%s[%-5s]%s %s:%d: ", g_color ? level_colors[level] : "", level_names[level], g_color ? color_reset: "",
                       file, line);
    if (len_prefix < 0) {
        return;
    }
    if (len_prefix >= (int)sizeof buf_prefix) {
        return;
    }

    va_list args1;
    va_copy(args1, args);

    const int len_format = vsnprintf(NULL, 0, fmt, args1);
    va_end(args1);
    if (len_format < 0) {
        return;
    }
    char *buf_result = malloc((size_t)len_prefix + (size_t)len_format + 2);
    if (buf_result == NULL) {
        return;
    }
    memcpy(buf_result, buf_prefix, (size_t)len_prefix);

    const int len_formatted = vsnprintf(buf_result+ len_prefix, (size_t)len_format + 1, fmt, args);
    if (len_formatted < 0 || len_formatted != len_format) {
        free(buf_result);
        buf_result = NULL;
        return;
    }

    buf_result[len_prefix + len_format] = '\n';
    buf_result[len_prefix + len_format + 1] = '\0';


    fputs(buf_result, stderr);

    free(buf_result);
    buf_result = NULL;
}

void log_write(const LogLevel level, const char *file, const int line, const char *fmt, ...) {
    if ((unsigned)level >= LOG_LEVEL_COUNT) {
        return;
    }
    if (level < g_level && level != LOG_LEVEL_FATAL) {
        return;
    }
    va_list args;
    va_start(args, fmt);
    log_vwrite(level, file, line, fmt,args);
    va_end(args);
    if (level == LOG_LEVEL_FATAL) {
        fflush(stderr);
        abort();
    }

}