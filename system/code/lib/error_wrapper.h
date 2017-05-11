//
// \file error_wrapper.h
// \brief error deal wrapper function.
//

#if !defined(tlpi_error_wrapper_h__)
#define tlpi_error_wrapper_h__

#include "common.h"

begin_extern_c

void error_msg(const char *format, ...);

void error_exit(const char *format, ...) no_return;
void error_exit2(const char *format, ...) no_return;
void error_exitn(int errnum, const char *format, ...) no_return;

void fatal(const char *format, ...) no_return;
void usage_error(const char *format, ...) no_return;
void cmdline_error(const char *format, ...) no_return;

end_extern_c

#endif // tlpi_error_wrapper_h__
