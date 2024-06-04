/**
 * @file str-upper-lower.c
 * @author: John Volpe <john.volpe@teledyne.com>
 * @date Created on 2019-04-12 12:56
 *
 * Copyright 2019 Teledyne Marine Systems as an unpublished work.
 * All Rights Reserved.
 *
 * The information contained herein is confidential
 * property of Teledyne Marine Systems. The use, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Teledyne Marine Systems.
 *
 */

/* ********************************* Includes ********************************* */

#include <ctype.h>
#include <string-extra.h>

/* ********************************* Defines ********************************** */

/* ****************************** Module Globals ****************************** */

/* ******************************** Local Data ******************************** */

/* *************************** Function Prototypes **************************** */

char *str_tolower(char *const str_p)
{
    char *work_p = str_p;

    if (str_p)
    {
        while (*work_p)
        {
            *work_p = (char)tolower(*work_p);
            work_p++;
        }
    }

    return str_p;
}

char *str_toupper(char *const str_p)
{
    char *work_p = str_p;

    if (str_p)
    {
        while (*work_p)
        {
            *work_p = (char)toupper(*work_p);
            work_p++;
        }
    }

    return str_p;
}

char *strlcpy_tolower(char *dst_p, const char *src_p, size_t const maxlen)
{
    strlcpy(dst_p, src_p, maxlen);

    str_tolower(dst_p);

    return dst_p;
}
