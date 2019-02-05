/* header.h
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HEADER_H
#define	HEADER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define INI_TRISA   (0b00000000u)
#define INI_LATA    (0b00000000u)
#define INI_ANSELA  (0b00000000u)
#define INI_WPUA    (0b00000000u)
#define INI_ODCONA  (0b00000000u)
#define INI_SLRCONA (0b11111111u)
#define INI_INLVLA  (0b00000010u)


// CLOCK --------------------------------------------------------------------------
#define CLOCKIN             (16000000uL)
#define CLOCKOUT            (CLOCKIN/4u)

// OSCCON -------------------------------------------------------------------------
#define INI_OSCCON1     (0b01100000u)	// HFINTOSC, NDIV = 1
#define INI_OSCCON3     (0b00100000u)   // SOSC disabled
#define INI_OSCEN       (0b01000000u)   // HFINTOSC is explicitly enabled
#define INI_OSCFRQ      (0b00000101u)   // 16MHz
#define INI_OSCTUNE     (0b00000000u)   // factory tuned

// RTCLOCK ------------------------------------------------------------------------
#define INI_T0CON0      (0b00001001u)   // disabled, 8bit, post=1:10
#define INI_T0CON1      (0b01000100u)   // Fosc/4, synchronized, pre=1:16
#define INI_TMR0H       (249u)

#define RTClockStart() { \
    T0CON0 = INI_T0CON0; \
    T0CON1 = INI_T0CON1; \
    TMR0H = INI_TMR0H; \
    TMR0L = 0u; \
    TMR0IF = false; \
    TMR0IE = true; \
    T0EN = true; \
}

#define RTC_TICK    (100u)  // 100 x 0.1ms = 10ms

// time units in rtc ticks
#define MU_0005S (50u/RTC_TICK)     // 0.005 sec
#define MU_001S (100u/RTC_TICK)     // 0.01 sec
#define MU_01S  (1000u/RTC_TICK)    // 0.1 sec
#define MU_1S   (10000u/RTC_TICK)   // 1 sec
#define MU_10S  (100000uL/RTC_TICK) // 10 sec
#define MU_1MIN (600000uL/RTC_TICK) // 1 min

// WATCHDOG -----------------------------------------------------------------------
#if !defined(TEST)
#define INI_WDTCON0     (0b00010101u)   // WDT prescaler = 1:32768; WDT on
                                        // WDT period 1024ms.
#define INI_WDTCON1     (0b00000111u)   // LFINTOSC, window 100%
#else   // !defined(TEST)
#define INI_WDTCON0     (0b00010101u)   // 1sec to allow long tests to finish
#define INI_WDTCON1     (0b00000111u)   // LFINTOSC, window 100%
#endif  // !defined(TEST)


void Initialize(void);
void InitializeHardware(void);
void __interrupt() intr(void);


#ifdef	__cplusplus
}
#endif

#endif	/* HEADER_H */

