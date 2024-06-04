/**
 * @file debugger.h
 *
 * Copyright 2020 Teledyne Webb Research as an unpublished work.
 *
 * The information contained herein is the property of Teledyne Webb Research
 * and is considered proprietary. This information may not be used for
 * any other purpose, copied, transferred or disclosed to third parties,
 * reverse engineered, modified or improved without written consent
 * from Teledyne Webb Research.
 *
 */

#if !defined(DEBUGGER_H)
#define DEBUGGER_H

/* ********************************* Includes ********************************* */

#if defined(STM32L4R5xx)
#include "stm32l4xx.h"
#elif defined(__ATSAMC21__) || defined(__SAMC21__)
#include <system.h>
#endif

/* ********************************* Defines ********************************** */

/* ****************************** Module Globals ****************************** */

/* *************************** Function Prototypes **************************** */

/**
 * Return whether the debugger is physically attached and we are debugging
 * @retval true if debugger is attached and enabled
 * @retval false if no debugger attached
 */
static inline bool debugger_attached(void)
{
#if defined(STM32L4R5xx)
    return ((CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) == CoreDebug_DHCSR_C_DEBUGEN_Msk);
#elif defined(__ATSAMC21__) || defined(__SAMC21__)
    return system_is_debugger_present();
#endif
}

static inline void debugger_breakpoint(void)
{
    if (debugger_attached())
    {
        __BKPT(0);
    }
}

#endif /* DEBUGGER_H */
