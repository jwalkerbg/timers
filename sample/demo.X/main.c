/* main.h
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

#include <xc.h>
#include "cdefs.h"
#include "timedefs.h"
#include "header.h"

DEFINE_SINGLE_PULSE_TIMER(T1,uint8_t);
DEFINE_BURST_GENERATOR(G1,uint8_t);

void main(void)
{
    DisableInterrupts();
    CLRWDT();
    Initialize();

    RTClockStart();
    INTCONbits.PEIE = true;
    EnableInterrupts();

    SetSinglePulseTimer(T1,50u*MU_001S);
    do {
        CLRWDT();
        if (SinglePulseTimerExpired(T1) == true) {
            SinglePulseTimerExpired(T1) = false;
            LATAbits.LATA0 = highstate;
            SetBurstGeneratorWithOutput(G1,5u,3u*MU_001S,2u*MU_001S,5u*MU_001S,LATAbits.LATA1);
        }
        if (BurstGeneratorTick(G1) == true) {
            BurstGeneratorTick(G1) = false;
            NOP();
        }
    } while (1);
}

void Initialize(void)
{
    InitializeHardware();

    ResetSinglePulseTimer(T1);
    ResetBurstGenerator(G1);
}

void InitializeHardware(void)
{
    OSCCON1 = INI_OSCCON1;
    OSCCON3 = INI_OSCCON3;
    OSCEN = INI_OSCEN;
    OSCFRQ = INI_OSCFRQ;
    OSCTUNE = INI_OSCTUNE;

    WDTCON0 = INI_WDTCON0;
    WDTCON1 = INI_WDTCON1;

    ANSELA = INI_ANSELA;
    TRISA = INI_TRISA;
    LATA = INI_LATA;
    WPUA = INI_WPUA;
    ODCONA = INI_ODCONA;
    SLRCONA = INI_SLRCONA;
    INLVLA = INI_INLVLA;
}

void __interrupt() intr(void)
{
    if ((TMR0IE == true) && (TMR0IF == true)) {
        TMR0IF = false;

        TickSinglePulseTimer(T1);
        TickBurstGeneratorWithOutput(G1,LATAbits.LATA1);
    }
}

// End of main.c
