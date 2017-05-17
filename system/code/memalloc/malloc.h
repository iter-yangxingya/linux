//
// \file malloc.h
// \brief malloc.h implement c library malloc/free use system call brk/sbrk
//

#if !defined(tlpi_malloc_h__)
#define tlpi_malloc_h__

#include <common.h>

begin_extern_c

void *malloc(size_t size);
void free(void *ptr);

end_extern_c

#endif // tlpi_malloc_h__
