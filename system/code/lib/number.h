//
// \file number.h
// \brief number.h define string change to number(int/long) wrapper for atoi...
//

#if !defined(tlpi_number_h__)
#define tlpi_number_h__

#include "common.h"

#define none_negative       (01)
#define greater_zero        (02)

#define any_base            (0100)
#define base_oct            (0200)
#define base_hex            (0400)

begin_extern_c

long to_long(const char *arg, int flags, const char *name);
int to_int(const char *arg, int flags, const char *name);

end_extern_c

#endif // tlpi_number_h__
