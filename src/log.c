#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static FILE *log_fp = NULL;
static enum LOG_LEVEL log_level = LOG_LEVEL_INFO;

void log_set_file(const char *file) { log_fp = fopen(file, "a+"); }

void log_set_level(enum LOG_LEVEL level) { log_level = level; }

void log_internal(enum LOG_LEVEL level, const char *level_str, const char *file, int line,
                  const char *func, const char *fmt, ...) {
  if (level < log_level) return;

  char buf[1024] = {0};
  sprintf(buf, "[%s] %s:%d %s() ", level_str, file, line, func);
  va_list ap;
  va_start(ap, fmt);
  vsprintf(buf + strlen(buf), fmt, ap);
  va_end(ap);
  fprintf(log_fp == NULL ? stderr : log_fp, "%s\n", buf);
}
