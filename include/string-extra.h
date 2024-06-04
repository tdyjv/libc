/**
 * @file string-extra.h
 *
 * Copyright 2019 Teledyne Webb Research as an unpublished work.
 *
 * The information contained herein is the property of Teledyne Webb Research
 * and is considered proprietary. This information may not be used for
 * any other purpose, copied, transferred or disclosed to third parties,
 * reverse engineered, modified or improved without written consent
 * from Teledyne Webb Research.
 *
 */

#if !defined(STRING_EXTRA_H)
#define STRING_EXTRA_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(HOST)
char *libc_strtok(char *s, const char *delim);

char *libc_strtok_r(char *str, const char *delim, char **saveptr);

int libc_strcasecmp(char const *s1_p, char const *s2_p) ;

int libc_strncasecmp(const char *s1, const char *s2, size_t n);

#else

char *strtok_r(char *str, const char *delim, char **saveptr);

int strcasecmp(const char *s1, const char *s2);

int strncasecmp(const char *s1, const char *s2, size_t n);

#endif

/**
 * Safe copy string.  Destination string will be truncated if necessary to the
 * max length specified and will be nul terminated.
 * @param dst_p Pointer to the destination string
 * @param src_p Pointer to the source string
 * @param maxlen Maximum length of the destination string
 * @return Number of characters in the source string.  If this is > maxlen
 * then the string was truncated.
 */
size_t strlcpy(char *const dst_p,
               const char *const src_p,
               size_t const maxlen);

/**
 * Safe concatenate a string.  The source string will be appended to the
 * destination string. If the resulting string would be longer than maxlen the
 * destination string will be truncated and will be nul terminated.
 * @param dst_p Pointer to the destination string
 * @param src_p Pointer to the source string
 * @param maxlen Maximum length of the destination string
 * @return Number of characters that would have been in the dest string.  If
 * this is > maxlen then the src string was truncated.
 */
size_t strlcat(char *const dst_p,
               const char *const src_p,
               size_t const maxlen);

/**
 * Convert a string to lower case.  All alpha character in the string
 * will be converted inplace.
 * @param str_p Pointer to the string to convert
 * @return Pointer to the original string
 */
char *str_tolower(char *const str_p);

char *strlcpy_tolower(char *dst_p, const char *src_p, size_t n);

/**
 * Convert a string to upper case.  All alpha character in the string
 * will be converted inplace.
 * @param str_p Pointer to the string to convert
 * @return Pointer to the original string
 */
char *str_toupper(char *const str_p);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif
