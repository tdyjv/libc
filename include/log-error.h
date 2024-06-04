/**
 * @file log-error.h
 * @author: John Volpe <john.volpe@teledyne.com>
 * @date Created on 2019-11-25 13:05
 *
 * Copyright 2019 Teledyne Webb Research as an unpublished work.
 *
 * The information contained herein is the property of Teledyne Webb Research
 * and is considered proprietary. This information may not be used for
 * any other purpose, copied, transferred or disclosed to third parties,
 * reverse engineered, modified or improved without written consent
 * from Teledyne Webb Research.
 */

#if !defined(LOG_ERROR_H)
#define LOG_ERROR_H

/* ********************************* Includes ********************************* */

#include <stdbool.h>

/* ********************************* Defines ********************************** */

/* ****************************** Module Globals ****************************** */

/* *************************** Function Prototypes **************************** */

/**
 * Log an error to the core dump area.  Optionally include a stack trace
 * @param backtrace True = Include stack trace in log message
 * @param format printf style format for error message
 * @param ... Parameters for printf format spec
 */
void log_error(bool backtrace, const char *format, ...) __attribute__((format(printf, 2, 3)));

#endif /* LOG_ERROR_H */
