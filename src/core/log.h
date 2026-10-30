#ifndef RACER_LOG_H
#define RACER_LOG_H
#include <stdbool.h>

typedef enum {
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,
    LOG_LEVEL_COUNT
} LogLevel;

#if defined(__GNUC__)
#define LOG_PRINTF_FORMAT(fmt_idx, args_idx) __attribute__((format(printf, fmt_idx, args_idx)))
#else
#define LOG_PRINTF_FORMAT(fmt_idx, args_idx)
#endif

void log_set_level(LogLevel level);
LogLevel log_get_level(void);
void log_set_color(bool enabled);
void log_write(LogLevel level, const char *file, int line, const char *fmt, ...) LOG_PRINTF_FORMAT(4, 5);

#define LOG_TRACE(...) log_write(LOG_LEVEL_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) log_write(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) log_write(LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) log_write(LOG_LEVEL_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_write(LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_write(LOG_LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__)


#endif //RACER_LOG_H
