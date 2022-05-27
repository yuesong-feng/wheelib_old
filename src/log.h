#ifndef _LOG_H_
#define _LOG_H_
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

static FILE *log_fp = NULL;

#define SET_LOG_TARGET(log_file) log_fp = fopen(log_file, "a+");

#define LOG(fmt, ...)                                                     \
  time_t curtime;                                                         \
  time(NULL);                                                             \
  fprintf(log_fp == NULL ? stdout : log_fp, "[LOG] %s", ctime(&curtime)); \
  fprintf(log_fp == NULL ? stdout : log_fp, fmt, ##__VA_ARGS__);          \
  fprintf(log_fp == NULL ? stdout : log_fp, "\n\n");

#endif