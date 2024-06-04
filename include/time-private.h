/*
 * (C)2012 Michael Duane Rice All rights reserved.
 *
 * With Modifications for Teledyne Marine by John Volpe <john.volpe@teledyne.com>
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer. Redistributions in binary
 * form must reproduce the above copyright notice, this list of conditions
 * and the following disclaimer in the documentation and/or other materials
 * provided with the distribution. Neither the name of the copyright holders
 * nor the names of contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TIME_PRIVATE_H
#define TIME_PRIVATE_H

#ifdef __cplusplus
extern          "C" {
#endif

#include <time.h>
#include <stdbool.h>

/**
 *   Enumerated labels for the days of the week.
 */
enum _WEEK_DAYS_
{
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

/**
 *   Enumerated labels for the months.
 */
enum _MONTHS_
{
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

/**
 *  Return 1 if year is a leap year, zero if it is not.
 */

bool is_leap_year(int year);

/**
 *  Structure which represents a date as a year, week number of that year, and day of week.
 *  See http://en.wikipedia.org/wiki/ISO_week_date for more information.
 */
struct week_date
{
	int year; /**< year number (Gregorian calendar) */
	int week; /**< week number (#1 is where first Thursday is in) */
	int day; /**< day within week */
};

unsigned week_of_year(const struct tm *timestruct, unsigned base);

void iso_week_date_r(int y, int yday, struct week_date *iso);

/** One hour, expressed in seconds */
#define ONE_HOUR 3600

/** One day, expressed in seconds */
#define ONE_DAY 86400

// This library uses 1/1/2000 as epoch, we want Unix compatible 1/1/1970
static const time_t epoch_shift = 946684800LL;

/* @} */
#ifdef __cplusplus
}
#endif

#endif              /* TIME_H  */
