//
// \file common.h
//

#if !defined(tlpi_common_h__)
#define tlpi_common_h__

#if defined(__GNUC__)
// for forbidden gcc complain.
# define no_return __attribute__ ((__noreturn__))
#else
# define no_return
#endif


#ifdef __cplusplus
# define extern_c extern "C"
# define begin_extern_c extern "C" {
# define end_extern_c }
#else
# define extern_c
# define begin_extern_c
# define end_extern_c
#endif

#endif // tlpi_common_h__
