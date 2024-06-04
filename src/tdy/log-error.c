/**
 * @file log-error.c
 * @author: John Volpe <john.volpe@teledyne.com>
 * @date Created on 2019-11-25 13:02
 *
 * Copyright 2019 Teledyne Webb Research as an unpublished work.
 *
 * The information contained herein is the property of Teledyne Webb Research
 * and is considered proprietary. This information may not be used for
 * any other purpose, copied, transferred or disclosed to third parties,
 * reverse engineered, modified or improved without written consent
 * from Teledyne Webb Research.
 */

/* ********************************* Includes ********************************* */

#include "log-error.h"

/* ********************************* Defines ********************************** */

/* ****************************** Module Globals ****************************** */

/* ******************************** Local Data ******************************** */

/* *************************** Function Prototypes **************************** */

__attribute__((weak)) void log_error(const bool backtrace __attribute__((unused)),
                                     const char *format __attribute__((unused)),
                                     ...)
{}
