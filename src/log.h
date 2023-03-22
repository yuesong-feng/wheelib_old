#ifndef _LOG_H_
#define _LOG_H_

enum LOG_LEVEL {
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR
};

#ifdef __GNUC__
#define CHECK_FMT(a, b) __attribute__((format(printf, a, b)))
#else
#define CHECK_FMT(a, b)
#endif

void log_set_file(const char *file);
void log_set_level(int level);
void log_internal(int level, const char *level_str, const char *file, int line, const char *func, const char *fmt, ...) CHECK_FMT(6, 7);

#define LOG_SET_FILE(file) log_set_file(file);
#define LOG_SET_LEVEL(level) log_set_level(level);

#define LOG_DEBUG(fmt, ...) log_internal(LOG_LEVEL_DEBUG, "DEBUG", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) log_internal(LOG_LEVEL_INFO, "INFO", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) log_internal(LOG_LEVEL_WARN, "WARN", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) log_internal(LOG_LEVEL_ERROR, "ERROR", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#endif
