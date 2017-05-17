//
// \file malloc.h
// \brief malloc.h implement c library malloc/free use system call brk/sbrk
//

#if !defined(tlpi_malloc_h__)
#define tlpi_malloc_h__

#include <sys/types.h>  // for size_t
#include <common.h>

begin_extern_c

void *i_malloc(size_t size);
void i_free(void *ptr);

end_extern_c

#endif // tlpi_malloc_h__
