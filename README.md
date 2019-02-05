# timers

## Introduction

This module defines various types of timers that may be used for measuring single time intervals or for triggering events at even time intervals. Some of the the timers are more complex - they may count forward and backward and this way to participate in simulating physical processes - par example heating and cooling of an electronic unit. Most complex are capable to produce bursts of impulses.

All of the timers depend on the system real time clock (**RTC**). The **RTC** usually uses one of the microcontroller's embedded timers which is configured to make interrupts at even intervals (2.5ms to 10ms are reasonable values).

The timers can be defined wit variaous lengths of the counters. They can measure short time intervals in and such cases they can be defined with _uint8_t_ counters. For longer intervals _uint16_t_ or even _uint_32_t_ can be used. Each timer have _DEFINE_ and _EXTERN_ macros that declare and define timer's variables. These macros accept as argument a type (_uint8_t_, _uint16_t_, _uint32_t_ etc) that is the type of the counters. All other macros that manipulate the timers do not use a time argument. Thus, it is very easy to change the type of a timer to a shorter or longer one.

The module is created and tested for usage in embedded projects with Microchip's PIC12 and PIC16 families. Without or with little adaptations, it may be extended to the other PIC families or other microcontrolers, or why not to be used in desktop applications.

## Files.

**cdefs.h** - This file defines two one-bit types - _B1_ and _U1_ and the constants **true** and **false** in the context of **Microchip XC8** compiler. It is very short and if someone needs, he/she can add another compiler dependence.

**timedefs.h** - This file defines all the timers and their manipulating macros.

Any application that uses timers should include **cdefs.h** and **timedefs.h**.

## Timers, a short description.

- Single pulse timer. This timer measures a single time interval and at its end it raises an `expired` flag.
- Continuous timer. This timer measures consecutive equal intervals and at the end of each of the intervals raises `TimerTick` flag. The interval of the timer may be changed in real time.
- Const sontinuous timer. This timer measures consecutive equal intervals and at the end of each of the intervals raises `TimerTick` flag. The interval is fixed at compile time and cannot be changed.
- Const free sontinuous timer. This timer measures consecutive equal intervals and at the end of each of the intervals raises `TimerTick` flag. This timer implements constant time interval and runs always. It cannot be stopped.
- Forward/Backward single shot timer. This timer is capable to count towards preset value (time interval) (forward) or towards zero (backward). The direction of the counting is controlled by a one bit boolean variable that is part of the timer. This direction may be set by the application. Example: A heat controlling application can turn the direction forward if the temperature is above given limit value or backward if the temperature is below that value.
- Forward/Backward variable single shot timer. This timer is capable to count towards preset value (time interval) (forward) or towards zero (backward). The direction of the counting is controlled by a one bit boolean variable that is part of the timer. This direction may be set by the application. In addition, this timer can change its counting step. An application can control the step depending on various external conditions and this way to simulate more complex physical processes.
- Asymmetric continuous timer. This is continuous timer that can produce sequence of two intervals with different lengths. The first interval is called HIGH and the second is called LOW. This timer, if combined with a hardware output can emit a sequence with different low and high times on an output pin.
- Asymmetric single pulse timer. This timer emits one period consisting of one LOW and one HIGH interval. It can be configured to produce LOW-HIGH or HIGH-LOW sequence. At the end of the second interval, the timer rises and `expired` flag.
- Burst generator. This more complex timer produces burst of given number of impulses. Each impulse have given length and there is defined interval between the adjacent impulses. A time interval is defined between the adjacent bursts too.
- Burst generator with output. This burst generator is equipped with an output pin and can direct bursts directly to hardware. Once configured and started it works alone and there is no need for care from the application.
