/** @file strlcat.c
 *
 * @author John Volpe <john.volpe@teledyne.com>
 *
 * @copyright Copyright 2015 Teledyne Webb as an unpublished work. All Rights Reserved.
 *
 * The information contained herein is confidential
 * property of Teledyne Marine Systems. The use, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Teledyne Marine Systems.
 *
 * @verbatim
 * 2015-02-05 john.volpe@teledyne.com  Created from linux_glider module
 * @endverbatim
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
 * @brief strlcat Safe strcat function.
 * Calling syntax :
 * @code
 *      char dst_buffer[20] ="asdfkljhasf" ;
 *      desired_len = strlcat(dst_buffer,"adfkjhasflkja",sizeof(dst_buffer)) ;
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
size_t strlcat(char *const dst_p, const char *const src_p, size_t const maxlen)
{
    size_t dstlen;
    size_t srclen;

    if ((src_p == (const char *)NULL) && (dst_p == NULL))
    {
        return 0;
    }

    if (src_p == (const char *)NULL)
    {
        return strlen(dst_p);
    }

    srclen = strlen(src_p);

    if ((dst_p == NULL) || (maxlen < 1))
    {
        return strlen(src_p);
    }

    dstlen = strlen(dst_p);

    if (srclen > 0)
    {
        if (dstlen + srclen < maxlen)
        {
            memcpy(dst_p + dstlen, src_p, srclen);
            *(dst_p + dstlen + srclen) = '\0';
        }
        else if (dstlen < maxlen)
        {
            memcpy(dst_p + dstlen, src_p, maxlen - dstlen - 1);
            *(dst_p + maxlen - 1) = '\0';
        }

        if (dstlen + srclen > maxlen)
        {
//            log_error(true,
//                      "strlcat overflow warning, srclen=%u, dstlen=%u, maxlen=%u\n",
//                      (unsigned)srclen,
//                      (unsigned)dstlen,
//                      (unsigned)maxlen);
        }
    }

    return dstlen + srclen;
}
