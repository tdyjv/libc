/**
 * @file strcasecmp.c
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

/* ********************************* Includes ********************************* */

#include <ctype.h>
#include <string-extra.h>

/* ********************************* Defines ********************************** */

/* ****************************** Module Globals ****************************** */

/* ******************************** Local Data ******************************** */

/* *************************** Function Prototypes **************************** */

#if defined(__UNIT_TEST__)
int libc_strcasecmp(char const *s1_p, char const *s2_p)
#else
int strcasecmp(char const *s1_p, char const *s2_p)
#endif
{
    /*
     * Handle special case of passing NULL as one of the strings.  Standard libc
     * has this a undefined behavior and X86 GCC SEGV faults but we can't
     * do that so gracefully (defined behavior) handle NULL arguments by considering
     * a NULL string arguement as "less than" any other string pointer
     */

    if ((s1_p != NULL) && (s2_p == NULL))
    {
        return 1;
    }

    if ((s1_p == NULL) && (s2_p != NULL))
    {
        return -1;
    }

    /* This handles both arguments are NULL or the same as equal strings */

    if (s1_p == s2_p)
    {
        return 0;
    }

    while (*s1_p && *s2_p)
    {
        if (tolower(*s1_p) != tolower(*s2_p))
        {
            break;
        }

        s1_p++;
        s2_p++;
    }

    return tolower(*s1_p) - tolower(*s2_p);
}
