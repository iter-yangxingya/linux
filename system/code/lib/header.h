//
// \file header.h for The linux programming interface header file.
//

#if !defined(tlpi_header_h__)
#define tlpi_header_h__

#include <sys/types.h>  // for types declare.
#include <stdio.h>      // for stardand io
#include <stdlib.h>     // ...

#include <unistd.h>     // for linux api declare.
#include <errno.h>      // for all error define constrant.
#include <string.h>     // string deal function.

#include "number.h"
#include "error_wrapper.h" // for error deal wrapper function.

typedef enum {FALSE, TRUE} Boolean;

#define min(x, y) ((x) > (y) ? (y) : (x))
#define max(x, y) ((x) > (y) ? (x) : (y))

#endif // tlpi_header_h__
