//
// \file error_wrapper.cpp
// \brief error deal wrapper implement file
//

#include <stdarg.h>     // for stdarg
#include "error_wrapper.h"
#include "header.h"
#include "ename.c.inc"

static void terminate(bool use_exit3) no_return;
static void output_error(bool use_err, int err, bool flush_stdout, const
    char *format, va_list ap);

void error_msg(const char *format, ...) {
    va_list arg_list;
    int saved_errno;

    saved_errno = errno;
    va_start(arg_list, format);
    output_error(true, errno, true, format, arg_list);
    va_end(arg_list);

    errno = saved_errno;
}

void error_exit(const char *format, ...) {
    va_list arg_list;

    va_start(arg_list, format);
    output_error(true, errno, true, format, arg_list);
    va_end(arg_list);

    terminate(true);
}

void error_exit2(const char *format, ...) {
    va_list arg_list;

    va_start(arg_list, format);
    output_error(true, errno, false, format, arg_list);
    va_end(arg_list);

    terminate(false);
}

void error_exitn(int error_no, const char *format, ...) {
    va_list arg_list;

    va_start(arg_list, format);
    output_error(true, error_no, true, format, arg_list);
    va_end(arg_list);

    terminate(true);
}

void fatal(const char *format, ...) {
    va_list arg_list;

    va_start(arg_list, format);
    output_error(false, errno, true, format, arg_list);
    va_end(arg_list);

    terminate(true);
}

void usage_error(const char *format, ...) {
    va_list arg_list;

    fflush(stdout);

    fprintf(stderr, "Usage: ");
    va_start(arg_list, format);
    vfprintf(stderr, format, arg_list);
    va_end(arg_list);

    fflush(stderr);
    exit(EXIT_FAILURE);
}

void cmdline_error(const char *format, ...) {
    va_list arg_list;

    fflush(stdout);

    fprintf(stderr, "Command-line usage error: ");
    va_start(arg_list, format);
    vfprintf(stderr, format, arg_list);
    va_end(arg_list);

    fflush(stderr);
    exit(EXIT_FAILURE);
}

static void terminate(bool use_exit3) {
    char *s;
    s = getenv("EF_DUMPCORE");

    //
    if (s != nullptr && *s != '\0')
        abort();
    if (use_exit3)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
}

static void output_error(bool use_err, int err, bool flush_stdout, const
    char *format, va_list ap) {
#define BUF_SIZE 500
    char buf[BUF_SIZE];
    char user_msg[BUF_SIZE];
    char err_text[BUF_SIZE];

    vsnprintf(user_msg, sizeof(user_msg), format, ap);

    if (use_err)
        snprintf(err_text, sizeof(err_text), " [%s %s]",
            (err > 0 && err <= MAX_ENAME) ?
            ename[err] : "?UNKNOWN?", strerror(err));
    else
        snprintf(err_text, sizeof(err_text), ":");

    snprintf(buf, sizeof(buf), "ERROR%s %s\n", err_text, user_msg);

    if (flush_stdout)
        fflush(stdout);

    fputs(buf, stderr);
    fflush(stderr);
}
