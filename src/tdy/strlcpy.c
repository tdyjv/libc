/**
 * @file
 *
 * @author John Volpe <john.volpe@teledyne.com>
 *
 * Copyright 2015 Teledyne Webb as an unpublished work.
 * All Rights Reserved.
 *
 * The information contained herein is confidential
 * property of Teledyne Marine Systems. The use, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Teledyne Marine Systems.
 *
 * 2015-02-05 john.volpe@teledyne.com  Created from linux_glider module
 *
 */

/* ********************************* Includes ********************************* */

#include <string-extra.h>

#include "log-error.h"

/* ********************************* Defines ********************************** */

/* ****************************** Module Globals ****************************** */

/* ******************************** Local Data ******************************** */

/* *************************** Function Prototypes **************************** */

/**
 * @brief strlcpy Safe strcpy function.
 * Calling syntax :
 * @code
 *      char dst_buffer[20];
 *      desired_len = strlcpy(dst_buffer,"01247856",sizeof dst_buffer) ;
 * @endcode
 *
 * @param dst_p Pointer to destination string
 * @param src_p Pointer to source string
 * @param maxlen Maximum length of destination string including
 * null terminator
 * @return Number of characters which WOULD HAVE BEEN in destination
 * string if there was enough room.  If this is < maxlen then the source
 * string was not truncated.  If it is >= maxlen then the source string
 * was truncated and the destination string is full.
 */
size_t strlcpy(char *const dst_p, char const *const src_p, size_t const maxlen)
{
    size_t srclen;

    if ((src_p == (const char *)NULL) && (dst_p == NULL))
    {
        return 0;
    }

    if (src_p == NULL)
    {
        if ((dst_p != NULL) && (maxlen > 0))
        {
            *dst_p = '\0';
        }

        return 0;
    }

    srclen = strlen(src_p);

    if ((dst_p == NULL) || (maxlen < 1))
    {
        return srclen;
    }

    if (srclen == 0)
    {
        *dst_p = '\0';
    }
    else if (srclen < maxlen)
    {
        memcpy(dst_p, src_p, srclen);
        *(dst_p + srclen) = '\0';
    }
    else
    {
        memcpy(dst_p, src_p, maxlen - 1);
        *(dst_p + maxlen - 1) = '\0';
    }

    if (srclen > maxlen)
    {
//        log_error(true,
//                  "strlcpy overflow warning, srclen=%u, maxlen=%u\n",
//                  (unsigned)srclen,
//                  (unsigned)maxlen);
    }

    return srclen;
}
