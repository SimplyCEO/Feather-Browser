#ifndef COMMON_HEADER
#define COMMON_HEADER

#ifndef SELF
#define SELF NULL
#endif

#ifdef __STDC__
# ifdef __STDC_VERSION__
#  if (__STDC_VERSION__ >= 199409L)
#   define PREDEF_STANDARD_C_1994
#  endif
#  if (__STDC_VERSION__ >= 199901L)
#   define PREDEF_STANDARD_C_1999
#  endif
#  if (__STDC_VERSION__ >= 201112L)
#    define PREDEF_STANDARD_C_2011
#  endif
#  if (__STDC_VERSION__ >= 201710L)
#   define PREDEF_STANDARD_C_2018
#  endif
# endif
#endif

#ifdef PREDEF_STANDARD_C_1989
# ifndef bool
#  define bool unsigned char
# endif
# ifndef true
#  define true  1
# endif
# ifndef false
#  define false 0
# endif
# ifndef int8_t
#  define int8_t signed char
# endif
# ifndef int16_t
#  define int16_t signed short
# endif
# ifndef int32_t
#  define int32_t signed int
# endif
# ifndef uint8_t
#  define uint8_t unsigned char
# endif
# ifndef uint16_t
#  define uint16_t unsigned short
# endif
# ifndef uint32_t
#  define uint32_t unsigned int
# endif
#else
# include <stdbool.h>
#endif

#endif

