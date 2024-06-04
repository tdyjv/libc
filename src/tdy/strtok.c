/*-
 * Copyright (c) 1998 Softweyr LLC.  All rights reserved.
 *
 * strtok_r, from Berkeley strtok
 * Oct 13, 1998 by Wes Peters <wes@softweyr.com>
 *
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notices, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notices, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY SOFTWEYR LLC, THE REGENTS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL SOFTWEYR LLC, THE
 * REGENTS, OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <libdef.h>
#include <string-extra.h>

#if defined(__UNIT_TEST__)
#define STRTOK      libc_strtok
#define STRTOK_R    libc_strtok_r

#else

#define STRTOK      strtok
#define STRTOK_R    strtok_r
#endif

char *STRTOK_R(char *s, const char *delim, char **last)
{
    char *spanp, *tok;
    int c, sc;

    if ((s == NULL) && ((s = *last) == NULL))
    {
        return (NULL);
    }

/*
 * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
 */
cont:
    c = *s++;

    for (spanp = (char *)(uintptr_t)delim; (sc = *spanp++) != 0;)
    {
        if (c == sc)
        {
            goto cont;
        }
    }

    if (c == 0)
    { /* no non-delimiter characters */
        *last = NULL;
        return (NULL);
    }

    tok = s - 1;

    /*
     * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
     * Note that delim must have one NUL; we stop if we see that, too.
     */
    for (;;)
    {
        c = *s++;
        spanp = (char *)(uintptr_t)delim;

        do
        {
            sc = *spanp++;
            if (sc == c)
            {
                if (c == 0)
                {
                    s = NULL;
                }
                else
                {
                    s[-1] = '\0';
                }

                *last = s;
                return (tok);
            }
        } while (sc != 0);
    }

    /* NOTREACHED */
}

char *STRTOK(char *s, const char *delim)
{
    static char *last;

    return (STRTOK_R(s, delim, &last));
}