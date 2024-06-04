/**
 * @file printf_config.h
 * @author: John Volpe <john.volpe@teledyne.com>
 * @date Created on 2019-08-06 20:06
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

#if !defined(PRINTF_CONFIG_H)
#define PRINTF_CONFIG_H

/* ********************************* Includes ********************************* */

/* ********************************* Defines ********************************** */

// 'ntoa' conversion buffer size, this must be big enough to hold one converted
// numeric number including padded zeros (dynamically created on stack)
// default: 32 byte
#define PRINTF_NTOA_BUFFER_SIZE    32U

// 'ftoa' conversion buffer size, this must be big enough to hold one converted
// float number including padded zeros (dynamically created on stack)
// default: 32 byte
#define PRINTF_FTOA_BUFFER_SIZE    32U

// support for the floating point type (%f)
// default: activated
#define PRINTF_SUPPORT_FLOAT

// support for exponential floating point notation (%e/%g)
// default: activated
#define PRINTF_SUPPORT_EXPONENTIAL

// define the default floating point precision
// default: 6 digits
#define PRINTF_DEFAULT_FLOAT_PRECISION  6U

// define the largest and smallest float suitable to print with %f
// default: 1e9
#define PRINTF_MAX_EXP          15
#define PRINTF_MAX_FLOAT        1e15
#define PRINTF_MIN_FLOAT        1e-15

// support for the long long types (%llu or %p)
// default: activated
#define PRINTF_SUPPORT_LONG_LONG

// support for the ptrdiff_t type (%t)
// ptrdiff_t is normally defined in <stddef.h> as long or long long type
// default: activated
#define PRINTF_SUPPORT_PTRDIFF_T

/* ****************************** Module Globals ****************************** */

/* *************************** Function Prototypes **************************** */

#endif /* PRINTF_CONFIG_H */
