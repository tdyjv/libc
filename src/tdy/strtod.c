/**
 * @file strtod.c
 * @author: John Volpe <john.volpe@teledyne.com>
 * @date Created on 2019-08-05 11:23
 *
 * Copyright 2019 Teledyne Marine as an unpublished work.
 * All Rights Reserved.
 *
 * The information contained herein is the property of Teledyne Marine
 * and is considered proprietary. This information may not be used for
 * any other purpose, copied, transferred or disclosed to third parties,
 * reverse engineered, modified or improved without written consent
 * from Teledyne Marine.
 */

/* ********************************* Includes ********************************* */

#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define __BSD_VISIBLE       (0)
#define __XSI_VISIBLE       (0)

#include "openlibm.h"

/* ********************************* Defines ********************************** */

/* ****************************** Module Globals ****************************** */

/* ******************************** Local Data ******************************** */

/* *************************** Function Prototypes **************************** */

static const double exp_values[] = {
    1e1, 1e2, 1e4, 1e8, 1e16, 1e32, 1e64, 1e128, 1e256
};

double strtod(const char *__restrict str, char **__restrict str_end)
{
    double value = 0.0;
    double fraction = 1.0;
    double sign = 1.0;
    int exponent = 0;
    bool exp_negative = false;

    /* Skip any leading whitespace */

    while (isspace(*str))
    {
        str++;
    }

    /* Get sign of result */

    if ((*str == '-') || (*str == '+'))
    {
        sign = (*str == '-') ? -1.0 : 1.0;
        str++;
    }

    /* Get and convert the whole number portion */

    while ((*str >= '0') && (*str <= '9'))
    {
        value *= 10.0;
        value += (double)(*str - '0');
        str++;
    }

    /* Check for fractional part (has decimal point) */

    if (*str == '.')
    {
        str++;

        while ((*str >= '0') && (*str <= '9'))
        {
            fraction /= 10.0;
            value += fraction * (double)(*str - '0');
            str++;
        }
    }

    /* Now handle any exponent */

    if ((*str == 'E') || (*str == 'e'))
    {
        str++;

        if (*str == '-')
        {
            exp_negative = true;
            str++;
        }
        else if (*str == '+')
        {
            str++;
        }

        while ((*str >= '0') && (*str <= '9'))
        {
            exponent *= 10;
            exponent += (*str - '0');
            str++;
        }

        if (exponent > __DBL_MAX_10_EXP__)
        {
            return exp_negative ? -HUGE_VAL : HUGE_VAL;
        }

        /*
         * The law of exponents (x^(y+z) == x^y * x^z) allow us to shortcut
         * the exponent scaling using a table
         */

        if (exp_negative)
        {
            for (unsigned bit = 0; bit < sizeof exp_values / sizeof exp_values[0]; bit++)
            {
                if ((exponent & (1 << bit)) != 0)
                {
                    value /= exp_values[bit];
                }
            }
        }
        else
        {
            for (unsigned bit = 0; bit < sizeof exp_values / sizeof exp_values[0]; bit++)
            {
                if ((exponent & (1 << bit)) != 0)
                {
                    value *= exp_values[bit];
                }
            }
        }
    }

    /* Now set the sign of the final result */

    value *= sign;

    /* Set the pointer to the next character */

    if (str_end)
    {
        *str_end = (char *)str;
    }

    return value;
}
