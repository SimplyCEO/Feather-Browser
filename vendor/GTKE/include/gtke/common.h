#if !defined(__GTKE_COMMON_H__)
# define __GTKE_COMMON_H__

# if (__STDC_VERSION__ < 199901L) && !defined(__cplusplus)
typedef unsigned char  bool;
typedef signed   char  int8_t;
typedef signed   short int16_t;
typedef signed   int   int32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
#   define false 0
#   define true 1
# else
#   include <stdbool.h>
#   include <stdint.h>
# endif

#endif

