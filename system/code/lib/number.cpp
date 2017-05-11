
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "number.h"

static void failure(
    const char *fname, const char *msg, const char *arg, const char *name) {

    fprintf(stderr, "%s error", fname);

    if (name != nullptr)
        fprintf(stderr, " (in %s)", name);

    fprintf(stderr, ": %s\n", msg);

    if (arg != nullptr && *arg != '\0')
        fprintf(stderr, "   offending text: %s\n", arg);

    exit(EXIT_FAILURE);
}

static long to_number(
    const char *fname, const char *arg, int flags, const char *name) {

    if (arg == nullptr && *arg == '\0')
        failure(fname, "null or empty string", arg, name);

    int base = (flags & any_base) ? 0 :
        (flags & base_oct) ? 8 : (flags & base_hex) ? 16 : 10;

    errno = 0;
    char *endptr;
    long res = strtol(arg, &endptr, base);
    if (errno != 0)
        failure(fname, "strtol() failed", arg, name);

    if (*endptr != '\0')
        failure(fname, "non-numeric characters", arg, name);

    if ((flags & none_negative) && res < 0)
        failure(fname, "negative value not allowed", arg, name);

    if ((flags & greater_zero) && res <= 0)
        failure(fname, "value must be greater than zero", arg, name);

    return res;
}

long to_long(const char *arg, int flags, const char *name) {
    return to_number("to_long", arg, flags, name);
}

int to_int(const char *arg, int flags, const char *name) {
    long res;

    res = to_number("to_int", arg, flags, name);
    if (res > INT_MAX || res < INT_MIN)
        failure("to_int", "integer out of range", arg, name);

    return (int)res;
}
