#if !defined(LIBDEF_H)
#define LIBDEF_H

#include <stdint.h>

/*
 * Start and End of CRC area in FLASH or RAM.  These are defined
 * in the linker script to define the area over which we have to
 * calculate the CRC32 value to validate the code is not corrupt.
 * Calculate the application CRC value using:
 *     uint32_t crc = crc32a_block(&_scrc, &_ecrc - &_scrc, 0xffffffff) ^ 0xffffffff;
 * then if (crc == g_app_crc) we are good
 */

extern uint8_t _scrc;       /* Start of CRC calculation area */
extern uint8_t _ecrc;       /* End of CRC calculation area */
extern uint32_t g_app_crc;  /* CRC of application calculated at build time */

/*
 * Macros to selectively disable certain GCC warnings for sections of code
 *
 * Can be used as follows :
 *
 * Form 1 for short assignment type of statements :
 *
 *     NOWARN(test1 = -1, "-Wsign-conversion");
 *
 * The sign-conversion warning will be disabled for the "test1 = -1" statement.
 *
 * Form 2 for sections of code :
 *
 * WARNPUSH("-Wsign-conversion")
 * WARNPUSH("-Wtype-limits")
 *         if ((starting_argv_index + test1 < 0) || (starting_argv_index >= *argc))
 * WARNPOP
 * WARNPOP
 *     {
 *         Some code......
 *     }
 *
 * The sign-conversion and type-limits warning will be disabled for the if statement.
 * Note that there must be a WARNPOP for each WARNPUSH otherwise some warnings
 * will be left disabled.
 *
 */
#define STRING(x)       #x

#define WARNPUSH(w)     _Pragma("GCC diagnostic push") _Pragma(STRING(GCC diagnostic ignored w))

#define WARNPOP()       _Pragma("GCC diagnostic pop")

#define NOWARN(x, w)    WARNPUSH(w) x; WARNPOP()

#if !defined(_UNUSED)
#define _UNUSED(x)       ((void)x)
#endif

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x)       (sizeof x / sizeof x[0])
#endif

/*
 * Set of static asserts to be used for structure size and field offset validation
 *
 * These are used in header files to ensure that a structure
 * is the correct size and that the fields of the structure are at the correct
 * offset.  This allows us to verify that a structure does not change
 * shape inadvertently.
 */

#ifdef __cplusplus
#ifndef _Static_assert
#define _Static_assert static_assert
#endif
#endif

#define STATIC_ASSERT(x)            _Static_assert((x), "(" #x ") failed")

#define OFFSETOF_ASSERT(s, f, o)    STATIC_ASSERT(__builtin_offsetof(s, f) == o)

#define SIZEOF_ASSERT(s, o)         STATIC_ASSERT(sizeof(s) == o)

/*
 * Somewhat safe (safer?) double to signed integer conversion
 * Converts double to signed integer by using an epsilon value.  The final
 * result of the conversion is a round away from zero at the epsilon value.
 *
 * Example:
 * for epsilon value e = 0.01
 * for d < 0.0 : if d < -i.99 then result = i-1 else result = i
 * for d >= 0.0 : if d > i.99 then result = i+1 else result = i
 *
 * We should really be checking the result against LONG_MAX and LONG_MIN
 *
 */
#define DBL2INT(d, e)       ((d) < 0.0 ? (-(int)(-(d) + (e))) : ((int)((d) + (e))))

/*
 * Somewhat safe (safer?) double to unsigned integer conversion
 * Converts double to unsigned integer by using an epsilon value.  The final
 * result of the conversion is a round away from zero at the epsilon value.
 *
 * Example:
 * for epsilon value e = 0.01
 * for d < 0.0 : result = 0
 * for d >= 0.0 : if d > i.99 then result = i+1 else result = i
 */
#define DBL2UINT(d, e)       ((d) < 0.0 ? 0 : ((unsigned)((d) + (e))))

/**
 * Convert a double to unsigned (32b) safely.
 * @param value Double value to convert to unsigned
 * @retval 0 if value < 0.0
 * @retval UINT_MAX if value > UINT_MAX
 * @retval 0-UINT_MAX for all values in the domain of a 32b unsigned
 */
unsigned dbl2uint(double value) ;

/**
 * Convert a double to int (32b) safely.
 * @param value Double value to convert to integer
 * @retval INT_MIN if value < INT_MIN
 * @retval INT_MAX if value > INT_MAX
 * @retval INT_MIN-INT_MAX for all values in the domain of a 32b integer
 */
int dbl2int(double value) ;

/*
 * Convert signed integer to unsigned integer, a negative input value will result
 * in a 0 returned value for safety.  This is USUALLY what we want especially when
 * dealing with timeout values as a negative integer would convert to a potentially
 * VERY large unsigned value (essentially an infinite timeout)
 */
#define INT2UINT(i)         ((i) < 0 ? 0 : (unsigned)(i))

#define STRINGIFY(d,e)        [d]=#d e

#define __STATIC_INLINE__ static __attribute__((always_inline)) inline

#endif // LIBDEF_H
