/* cdefs.h
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

#if !defined(cdefs_h_included)
#define cdefs_h_included

#include <stddef.h>
#include <stdint.h>
#include <math.h>

// --------------------------- logical true & false --------------------------------------

#if !defined(true) && !defined(false)
    #if defined(__XC)
        #define false   (B1)(1==0)
        #define true    (B1)(1==1)
    #endif  // defined(__XC)

    #if defined(_WIN32) && !defined(__cplusplus)
        #define false   (B1)(1==0)
        #define true    (B1)(1==1)
    #endif // defined(_WIN32) && !defined(__cplusplus)
    #if defined(_WIN32) && defined(__cplusplus)
        // C++ defines 'false' and 'true' constants. Nothing to do here.
    #endif // defined(_WIN32) && defined(__cplusplus)
#endif  // !defined(true) && !defined(false)

// ------------------- hardware low & high states - type U1 ------------------------------

#define lowstate    (U1)(0u)
#define highstate   (U1)(1u)

// ------------------------------- types -------------------------------------------------

#if defined(__XC8)

// boolean and one-bit definitions. we do not use _Bool, because its storage is eight bits (one byte)
    #if (__XC8_VERSION < 2000)
        typedef bit B1;                         // boolean; can receive 'true' or 'false'
        typedef bit U1;                         // unsigned int with length 1; can receive 0 and 1, lowstate and highstate respectively
    #else   // (__XC8_VERSION < 2000)
        typedef __bit B1;                       // boolean; can receive 'true' or 'false'
        typedef __bit U1;                       // unsigned int with length 1; can receive 0 and 1, lowstate and highstate respectively
    #endif  // (__XC8_VERSION < 2000)

#elif defined(_WIN32) && !defined(__GNUC__)
    typedef bool B1;                        // boolean; can receive 'true' or 'false'
    typedef bool U1;                        // unsigned int with length 1; can receive 0 and 1, lowstate and highstate respectively

#elif defined(__GNUC__)
    typedef bool B1;                        // boolean; can receive 'true' or 'false'
    typedef bool U1;                        // unsigned int with length 1; can receive 0 and 1, lowstate and highstate respectively
#endif  // defined(__GNUC__)

#endif  // !defined(cdefs_h_included)

#define EnableInterrupts()  { GIE = highstate; }
#define DisableInterrupts() { GIE = lowstate; }

// End of cdefs.h
