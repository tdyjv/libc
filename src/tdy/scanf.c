/**
 * @file scanf-1.c
 * @author: John Volpe <john.volpe@teledyne.com>
 *
 * Copyright 2019 Teledyne Marine as an unpublished work.
 * All Rights Reserved.
 *
 * The information contained herein is the property of Teledyne Marine
 * and is considered proprietary. This information may not be used for
 * any other purpose, copied, transferred or disclosed to third parties,
 * reverse engineered, modified or improved without written consent
 * from Teledyne Marine.
 *
 */

/* ********************************* Includes ********************************* */

#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/* ********************************* Defines ********************************** */

#if defined(__UNIT_TEST__) || defined(HOST)
#define SSCANF      libc_sscanf
#define VSSCANF     libc_vsscanf

int SSCANF(const char *buf, const char *format, ...);
int VSSCANF(const char *buf, const char *s, va_list ap);

#else  /* if defined(__UNIT_TEST__) || defined(HOST) */
#define SSCANF      sscanf
#define VSSCANF     vsscanf

#endif /* if defined(__UNIT_TEST__) || defined(HOST) */

/* ****************************** Module Globals ****************************** */

/* *************************** Function Prototypes **************************** */

static void put_i(void *addr, long long int val, size_t int_size)
{
    if (int_size == sizeof(char))
    {
        *(char *)addr = (char)val;
    }
    else if (int_size == sizeof(short))
    {
        *(short *)addr = (short)val;
    }
    else if (int_size == sizeof(int))
    {
        *(int *)addr = (int)val;
    }
    else if (int_size == sizeof(long long int))
    {
        *(long long int *)addr = val;
    }
}

/*
 * Get a limited length field from the input string to use for conversions.
 * If there is not enough characters in the input string, then use the rest of the
 * string, otherwise use up to the less of width (requested field width)
 * and maxlen-1 (sizeof field buffer).
 * width should be the actual field width requested, not including the nul terminator.
 */
static int get_field(char *field_p, char *buffer_p, size_t width, size_t maxlen)
{
    int length = 0;

    if (!width || !maxlen)
    {
        return 0;
    }

    /* Make room for nul */

    maxlen--;

    for (; maxlen && width && *buffer_p; maxlen--, width--, length++)
    {
        *field_p++ = *buffer_p++;
    }

    *field_p = '\0';

    return length;
}

int SSCANF(const char *buf, const char *format, ...)
{
    int count;
    va_list ap;

    va_start(ap, format);
    count = VSSCANF(buf, format, ap);
    va_end(ap);
    return (count);
}

int VSSCANF(char const *const input_p, const char *format_p, va_list ap)
{
    unsigned width;
    void *result_p;
    // float *result_fp_p ;
    bool suppress_assignment;
    bool have_width;
    size_t int_size;                /* Size of int/unsigned value */
    size_t float_size;              /* Size of float/double value */
    char *buffer_p = (char *)input_p;
    double d_value;
    int num_conversions = 0;
    char field[32];

    /* Use union to eliminate any compiler complaints */

    union
    {
        int i;
        unsigned u;
        long long int lli;
        long long unsigned llu;
    } value;

    while (*format_p)
    {
        /* Match non format specifiers */

        while (*format_p && (*format_p != '%'))
        {
            /* Any whitespace in format matches any amount of whitespace in input */

            if (isspace(*format_p))
            {
                while (isspace(*format_p))
                {
                    format_p++;
                }

                while (isspace(*buffer_p))
                {
                    buffer_p++;
                }
            }
            else if (*format_p++ != *buffer_p++)
            {
                goto func_exit;
            }
        }

        /* Advance past '%' */

        if (*format_p == '%')
        {
            format_p++;
        }

        /* Check for pre-mature end or all whitespace at end of format spec */

        if (!*format_p)
        {
            break;
        }

        suppress_assignment = false;
        have_width = false;
        value.llu = 0;
        d_value = 0.0;
        int_size = sizeof(int);
        float_size = sizeof(float);

        /* We get here when we had a '%' and format_p points at conversion specifier */

        /* Check for assignment suppression flag */

        if (*format_p == '*')
        {
            format_p++;
            suppress_assignment = true;
        }

        width = ~0;     /* Default width is max unsigned value */

        if (isdigit(*format_p))
        {
            width = strtoul(format_p, (char **)&format_p, 10);
            have_width = true;

            /* If width is specified, must > 0 */
            if (!width)
            {
                goto func_exit;
            }
        }

        /* Handle the valid type modifiers: 'h', 'hh', 'l' or 'll' */

        switch (*format_p)
        {
        case 'h':
            format_p++;

            if (*format_p == 'h')
            {
                format_p++;
                int_size = sizeof(char);
            }
            else
            {
                int_size = sizeof(short);
            }

            break;

        case 'l':
            format_p++;

            if (*format_p == 'l')
            {
                format_p++;
                int_size = sizeof(long long int);
                float_size = sizeof(double);            /* We don't support long doubles */
            }
            else
            {
                int_size = sizeof(long int);
                float_size = sizeof(double);
            }

            break;

        default:
            break;
        }     /* switch */

        /* If at the end of format or no valid conversion specifier - Exit */

        if (!*format_p || !strchr("cdinopsuxXefgEFG", *format_p))
        {
            goto func_exit;
        }

        /* Get address of conversion result from arguments */

        result_p = (suppress_assignment) ? NULL : va_arg(ap, void *);

        /* Store number of characters already process from input */

        if (*format_p == 'n')
        {
            format_p++;

            if (result_p)
            {
                put_i(result_p, (long long int)(buffer_p - input_p), int_size);
            }

            goto next_conversion;
        }

        /* Handle %c conversion specifier */

        if (*format_p == 'c')
        {
            format_p++;

            if (!have_width)
            {
                width = 1;
            }

            do
            {
                if (!*buffer_p)
                {
                    goto func_exit;
                }

                if (result_p)
                {
                    *(char *)result_p = *buffer_p;
                    result_p = ((char *)result_p + 1);
                }

                buffer_p++;
            } while (--width);

            goto next_conversion;
        }

        /* Skip any leading white space in input for numeric and string conversions */

        while (isspace(*buffer_p))
        {
            buffer_p++;
        }

        /*
         * If there is no more input to process then exit the function - not an error
         * we just converted a fewer number of items than was requested.
         */

        if (!*buffer_p)
        {
            goto func_exit;
        }

        switch (*format_p++)
        {
        case 's':

            do
            {
                if (isspace(*buffer_p))
                {
                    break;
                }

                if (result_p)
                {
                    *(char *)result_p = *buffer_p;
                    result_p = ((char *)result_p + 1);
                }

                buffer_p++;
            } while (--width && *buffer_p && !isspace(*buffer_p));

            if (result_p)
            {
                *(char *)result_p = '\0';
            }

            break;

        case 'p':
        case 'x':
        case 'X':
            value.i = strtol(buffer_p, &buffer_p, 16);

            if (result_p)
            {
                put_i(result_p, value.i, int_size);
            }

            break;

        case 'd':

            if (!isdigit(*buffer_p) && (*buffer_p != '-') && (*buffer_p != '+'))
            {
                goto func_exit;
            }

            if (have_width)
            {
                char *end_field_p;
                buffer_p += get_field(field, buffer_p, width, sizeof field);
                value.i = strtol(field, &end_field_p, 10);

                if (*end_field_p != '\0')
                {
                    goto func_exit;
                }
            }
            else
            {
                value.i = strtol(buffer_p, &buffer_p, 10);
            }

            if (result_p)
            {
                put_i(result_p, value.i, int_size);
            }

            break;

        case 'u':

            if (!isdigit(*buffer_p) && (*buffer_p != '+'))
            {
                goto func_exit;
            }

            if (have_width)
            {
                char *end_field_p;
                buffer_p += get_field(field, buffer_p, width, sizeof field);
                value.u = strtoul(field, &end_field_p, 10);

                if (*end_field_p != '\0')
                {
                    goto func_exit;
                }
            }
            else
            {
                value.u = strtoul(buffer_p, &buffer_p, 10);
            }

            if (result_p)
            {
                put_i(result_p, value.i, int_size);
            }

            break;

        case 'o':

            if (!isdigit(*buffer_p) && (*buffer_p != '+'))
            {
                goto func_exit;
            }

            if (have_width)
            {
                char *end_field_p;
                buffer_p += get_field(field, buffer_p, width, sizeof field);
                value.u = strtoul(field, &end_field_p, 8);

                if (*end_field_p != '\0')
                {
                    goto func_exit;
                }
            }
            else
            {
                value.u = strtoul(buffer_p, &buffer_p, 8);
            }

            if (result_p)
            {
                put_i(result_p, value.i, int_size);
            }

            break;

        case 'i':

            if ((*buffer_p == '0') && ((*buffer_p == 'x') || (*buffer_p == 'X')))
            {
                if (have_width)
                {
                    char *end_field_p;
                    buffer_p += get_field(field, buffer_p, width, sizeof field);
                    value.u = strtoul(field, &end_field_p, 16);

                    if (*end_field_p != '\0')
                    {
                        goto func_exit;
                    }
                }
                else
                {
                    value.u = strtoul(buffer_p, &buffer_p, 16);
                }
            }
            else if (*buffer_p == '0')
            {
                if (have_width)
                {
                    char *end_field_p;
                    buffer_p += get_field(field, buffer_p, width, sizeof field);
                    value.u = strtoul(field, &end_field_p, 8);

                    if (*end_field_p != '\0')
                    {
                        goto func_exit;
                    }
                }
                else
                {
                    value.u = strtoul(buffer_p, &buffer_p, 8);
                }
            }
            else if (!isdigit(*buffer_p) && (*buffer_p != '-') && (*buffer_p != '+'))
            {
                if (have_width)
                {
                    char *end_field_p;
                    buffer_p += get_field(field, buffer_p, width, sizeof field);
                    value.i = strtol(field, &end_field_p, 10);

                    if (*end_field_p != '\0')
                    {
                        goto func_exit;
                    }
                }
                else
                {
                    value.i = strtol(buffer_p, &buffer_p, 10);
                }
            }
            else
            {
                goto func_exit;
            }

            if (result_p)
            {
                put_i(result_p, value.i, int_size);
            }

            break;

        /* Default case used for floating point conversions */

        default:

            if (!isdigit(*buffer_p)
                && (*buffer_p != '-')
                && (*buffer_p != '+')
                && (*buffer_p != '.'))
            {
                goto func_exit;
            }

            if (have_width)
            {
                char *end_field_p;
                buffer_p += get_field(field, buffer_p, width, sizeof field);
                d_value = strtod(field, &end_field_p);

                if (*end_field_p != '\0')
                {
                    goto func_exit;
                }
            }
            else
            {
                d_value = strtod(buffer_p, &buffer_p);
            }

            if (result_p)
            {
                if (float_size == sizeof(float))
                {
                    *(float *)result_p = (float)d_value;
                }
                else if (float_size == sizeof(double))
                {
                    *(double *)result_p = d_value;
                }
            }

            break;
        } /* switch */

next_conversion:

        if (!suppress_assignment)
        {
            num_conversions++;
        }
    } /* while */

func_exit:
    return num_conversions;
}
