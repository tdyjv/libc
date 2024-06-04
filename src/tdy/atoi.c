#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#if defined(__UNIT_TEST__)
int libc_atoi(const char *str);

int libc_atoi(const char *str)
#else
int atoi(const char *str)
#endif
{
    bool neg = false;
    int val = 0;

    /* Skip leading white space */

    while (isspace(*str))
    {
        str++;
    }

    switch (*str)
    {
    case '-':
        neg = true;

    /* fall through */         // intentional fallthrough to advance str
    case '+':
        str++;

    default:
        break;     // proceed without action
    } /* switch */

    while (isdigit(*str))
    {
        val = (10 * val) + (*str++ - '0');
    }

    return (neg ? -val : val);
}
