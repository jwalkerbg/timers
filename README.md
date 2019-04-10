# timers

## Introduction

This module defines various types of timers that may be used for measuring single time intervals or for triggering events at even time intervals. Some of the timers are more complex - they can count forward and backward and this way to participate in simulating physical processes - par example heating and cooling of an electronic unit. Most complex timers are capable to produce bursts of impulses.

All of the timers depend on the system real-time clock (**RTC**). The **RTC** usually uses one of the microcontroller's embedded timers which is configured to make interrupts at even intervals (2.5ms to 10ms are reasonable values). The interval **RTC** ticks (the interrupts of embedded timer happen) is named **RTC_TICK**.

The timers can be defined with various lengths of the counters. They can measure short time intervals and in such cases, they can be defined with `uint8_t` counters. For longer intervals, `uint16_t` or even `uint32_t` can be used. Each timer has `DEFINE` and `EXTERN` macros that declare and define timer's variables. These macros accept as an argument an integral `unsigned` type (`uint8_t`, `uint16_t`, `uint24_t` (in **XC8**), `uint32_t` etc) that is the type of the counters. All other macros that manipulate the timers do not use a time argument. Thus, it is very easy to change the type of timer to a shorter or longer one if needed.

The module is created and tested for use in embedded projects with Microchip's **PIC12** and **PIC16** families. Without or with little adaptations, it may be extended to the other **PIC** families or other microcontrollers, or why not to be used in desktop applications.

## Files.

**cdefs.h** - This file defines two one-bit types - `B1` and `U1` and the constants `true` and `false` in the context of **Microchip XC8** compiler. It is very short and if someone needs, he/she can add another compiler dependence.

**timedefs.h** - This file defines all the timers and their manipulating macros.

Any application that uses timers should include **cdefs.h** and **timedefs.h**.

## Timers, a short description.

- Single pulse timer. This timer measures a single time interval and at its end, it raises an `expired` flag.
- Continuous timer. This timer measures consecutive equal intervals and at the end of each of the intervals raises `TimerTick` flag. The interval of the timer may be changed in real time.
- Const continuous timer. This timer measures consecutive equal intervals and at the end of each of the intervals raises `TimerTick` flag. The interval is fixed at the compile time and cannot be changed.
- Const free continuous timer. This timer measures consecutive equal intervals and at the end of each of the intervals raises `TimerTick` flag. This timer implements a constant time interval and runs always. It cannot be stopped.
- Forward/Backward single shot timer. This timer is capable to count towards a preset value (time interval) (forward) or towards zero (backward). The direction of the counting is controlled by a one-bit boolean variable that is a part of the timer. This direction may be set by the application. Example: A heat controlling application can turn the direction forward if the temperature is above the given limit value or backward if the temperature is below that value.
- Forward/Backward variable single shot timer. This timer is capable to count towards preset value (time interval) (forward) or towards zero (backward). The direction of the counting is controlled by a one-bit boolean variable that is a part of the timer. This direction may be set by the application. In addition, this timer can change its counting step. An application can control the step depending on various external conditions and this way to simulate more complex physical processes.
- Asymmetric continuous timer. This is a continuous timer that can produce a sequence of two intervals with different lengths. The first interval is called HIGH and the second is called LOW. This timer, if combined with a hardware output can emit a sequence with different low and high times on an output pin.
- Asymmetric single pulse timer. This timer emits one period consisting of one LOW and one HIGH interval. It can be configured to produce LOW-HIGH or HIGH-LOW sequence. At the end of the second interval, the timer rises and `expired` flag.
- Burst generator. This more complex timer produces bursts of a given number of impulses. Each impulse has given length and there is a defined interval between the adjacent impulses. A time interval is defined between the adjacent bursts too. Once configured and started it works alone and there is no need for care from the application.
- Burst generator with an output. This burst generator is equipped with an output pin and can direct bursts directly to hardware.

## Real Time Clock.

The Real Time Clock is an application specific device (hardware and/or software). So it must be implemented in the application. It has to have defined a procedure that is called at **RTC_TICK** intervals. This procedure is usually an interrupt responding procedure for the Real Time Clock. This procedure makes the timers \'tick\' by calling their `Tick` macros. Each tick makes timer's counter to increment by one (however forward/backward variable timers may count with different steps).

Intervals that are measured by the timers are multiples of **RTC_TICK**. The accuracy of the intervals is **1/2 RTC_TICK**. It is convenient to define several time units and this is usually done in the application header file. The example **header.h** contains such definition, assuming that **RTC_TICK** is 10ms:

```c
#define RTC_TICK    (100u)          // 100 x 0.1ms = 10ms

// time units in rtc ticks
#define MU_001S (100u/RTC_TICK)     // 0.01 sec
#define MU_01S  (1000u/RTC_TICK)    // 0.1 sec
#define MU_1S   (10000u/RTC_TICK)   // 1 sec
#define MU_10S  (100000uL/RTC_TICK) // 10 sec
#define MU_1MIN (600000uL/RTC_TICK) // 1 min
```

Then setting an interval of 500ms may looks looks like `(50u*MU_001S)` or `(5u*MU_01S)` and for even easier life the time intervals may be defined:

```c
#define T_RUN_TIME  (5u*MU_01S)     // 500ms
#define T_IDLE_TIME (20u*MU_01S)    // 2sec
```

## Common definitions.

**Tag**. Each timer has a tag, used to refer that timer in the application. The tag is a short alphanumeric string, preferably 1 to 3 symbols. The tag is always the first argument of the all macros associated with that kind of timer. For a given type of timer, a given tag may be associated with a single timer instance. However, two or more timers of a different kind may share identical tags. This is possible but not preferable because may lead to poor readability of the application.

**ttype**. This is the type of a timer. It must be an integral unsigned integer type with 8, 16, 24, 32 or 64 length. So in practice, valid types are `uint8_t`, `uint16_t`, `uint24_t`, `uint32_t`, `uint64_t`.

**Macros**. Each timer consists of a set of C preprocessor macros. These macros are divided in several groups:
- Declaration macros: `DEFINE` used in **.c** files and `EXTERN` used in **.h** files.
- Variable definition macros: These macros define the proprietary variables assigned to a timer.
- Manipulation macros: These macros are used to manipulate timers: Reset, Start, Stop, Tick etc.

The macros are described in the following sections.

## Single Pulse Timer.

This timer measures a single interval and at its end it raises an `expired` flag.

### Declaration.

| Macro | Description |
| --- | --- |
| `DEFINE_SINGLE_PULSE_TIMER(tag,ttype)` | Declare a single pulse timer in **.c** file by declaring its variables. `tag` is the tag of the timer, and `ttype` is its type. |
| `EXTERN_SINGLE_PULSE_TIMER(x,ttype)` | Define external definitions in **.h** file. `tag` is the tag of the timer, and `ttype` is its type. |

### Variables.

| Variable | Description |
| --- | --- |
| `ShortElapsingTimerCounter(tag)` | Counter of type `ttype`. Can be used as `lvalue`. Direct access to this variable is not recomended. |
| `SinglePulseTimerFlag(tag)` | When `true`, the flag indicates active, working timer and that the time interval has not expired. When `false`, the flag indicates that the timer is not started or the time interval has expired. Can be used as `lvalue`. |
| `SinglePulseTimerExpired(tag)` | When `true`, the flag indicates that the time interval has expired. When `false` the flag indicates that the time interval is not expired or the timer is not started at all. Can be used as `lvalue`. |

### Manipulation macros.

| Macro | Description |
| --- | --- |
| `SetSinglePulseTimer(tag,per)` | This macro activates a timer with tag `tag`, for an interval `per`. `per` must be an expression of the same type that was used in `DEFINE` and `EXTERN` macros. `ShortElapsingTimerCounter(tag)` is set to `per`, `SinglePulseTimerFlag(tag)` is set to `true` and `SinglePulseTimerExpired(tag)` is set to `false`. The macro disables the interrupts at the beginning and enables them at the end. |
| `SetSinglePulseTimerI(tag,per)` | This macro activates a timer with tag `tag`, for an interval `per`. `per` must be an expression of the same type that was used in `DEFINE` and `EXTERN` macros. `ShortElapsingTimerCounter(tag)` is set to `per`, `SinglePulseTimerFlag(tag)` is set to `true` and `SinglePulseTimerExpired(tag)` is set to `false`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. |
| `StopSinglePulseTimer(tag)` | This macro stops a timer with tag `tag`. It simply clears both flags `SinglePulseTimerFlag(tag)` and `SinglePulseTimerExpired(tag)`.  The macro disables the interrupts at the beginning and enables them at the end of the macro execution. |
| `ResetSinglePulseTimer(tag)` | This macro stops a timer with tag `tag`. It simply clears both flags `SinglePulseTimerFlag(tag)` and `SinglePulseTimerExpired(tag)`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. |
| `ClearSinglrPulseTimer(tag)` | This macro clears all the varibales associated with a timer with taga `tag`.  The macro does not touch the interrupts. |
| `SuspendSinglePulseTimer(tag)` | This macro suspends a timer with tag `tag` but keeps its counter no altered. The application may interrupt counting for a while. This macro is rarely used. |
| `ResumeSinglePulseTimer(tag)` | This macro resumes a previously suspended timer. Potentially dangerous macro if called with not a started timer and with zeroed variables. This macro is rarely used. |
| `ClearSinglePulseTimerExpired(tag)` | This macro clears `SinglePulseTimerExpired(tag)`. It is used by the application when it sees risen `SinglePulseTimerExpired(tag)` before performing some actions upon the end of the interval `per`. |
| `TickSinglePulseTimer(tag)` | This macro decrements by one `ShortElapsingTimerCounter(tag)`. If the counter becomes zero, the macro clears `SinglePulseTimerFlag(tag)` and rises `SinglePulseTimerExpired(tag)`. This way the macro indicates the end of the interval `per`. The macro does not touch stopped and suspended timers because they have `SinglePulseTimerFlag(tag)` cleared. |

## Continuous Timer.

This timer measures consecutive equal intervals and at the end of each of the intervals raises `TimerTick` flag. So it is capable to trigger periodic events in an embedded system. If needed the application can change the longness of the interval.

### Declaration.

| Macro | Description |
| --- | --- |
| DEFINE_CONTINUOUS_TIMER(tag,ttype) | Declare a continuous timer in **.c** file by declaring its variables. `tag` is the tag of the timer, and `ttype` is its type. |
| EXTERN_CONTINUOUS_TIMER(tag,ttype) | Define external definitions in **.h** file. `tag` is the tag of the timer, and `ttype` is its type. |

### Variables.

| Variable | Description |
| --- | --- |
| ContinuousTimerCounter(tag) | Counter of type `ttype`. Can be used as `lvalue`. Direct access to this variable is not recommended. |
| ContinuousTimerSetting(tag) | Period of the timer.  Can be used as `lvalue`. It is used to load ContinuousTimerCounter(x) at the end of the current interval. |
| ContinuousTimerFlag(tag) | When `true`, this flag indicates active, working timer. When `false` the flag indicates a stopped timer. |
| ContinuousTimerTick(tag) | This flag, when `true` indicates that an interval with period of `ContinuousTimerSetting(tag)` has expired. When an application sees this flag risen, it should clear it by calling `ClearContinuousTimerTick(tag)` and eventually execute some periodic actions. |

### Manipulation macros.

| Macro | Description |
| --- | --- |
| `SetContinuousTimer(tag,per)` | This macro activates a timer with tag `tag` to measure intervals `per`. `per` must be an expression of the same type that was used in `DEFINE` and `EXTERN` macros. `ContinuousTimerFlag(tag)` is set to `true`, `ContinuousTimerTick(tag)` is set to `false`. `ContinuousTimerSetting(tag)` and `ContinuousTimerCounter(tag)` to `per`. The macro disables the interrupts at the beginning and enables them at the end. |
| `SetContinuousTimerI(tag,per)` | This macro activates a timer with tag `tag` to measure intervals `per`. `per` must be an expression of the same type that was used in `DEFINE` and `EXTERN` macros. `ContinuousTimerFlag(tag)` is set to `true`, `ContinuousTimerTick(tag)` is set to `false`. `ContinuousTimerSetting(tag)` and `ContinuousTimerCounter(tag)` to `per`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. |
| `StopContinuousTimer(tag)` | This macro stops a timer with tag `tag`. It simply clears both `ContinuousTimerFlag(tag)` and `ContinuousTimerTick(tag)`. The macro disables the interrupts at the beginning and enables them at the end of the macro execution. |
| `ResetContinuousTimer(tag)` | This macro stops a timer with tag `tag`. It simply clears both `ContinuousTimerFlag(tag)` and `ContinuousTimerTick(tag)`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. |
| `ClearContinuousTimer(tag)` | This macro clears all variables associated with a timer with tag `tag`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. Note: Normally, this macro is not much useful. It exists for history purposes. |
| `SuspendContinuousTimer(tag)` | This macros suspends a timer with tag `tag` while keeping the values of the counter and the setting. |
| `ResumeContinuousTimer(tag)` | This macro resumes a timer that was previously suspended. |
| `TickContinuousTimer(tag)` | This macro decrements by one `ContinuousTimerCounter(tag)`. If the counter becomes zero, the macro raises `ContinuousTimerTick(tag)` and sets `ContinuousTimerCounter(tag)` to `ContinuousTimerSetting(tag)`. |

## Const Continuous Timer.

This timer measures consecutive equal intervals and at the end of each of the intervals raises `TimerTick` flag. So it is capable to trigger periodic events in an embedded system. This timer cannot change its interval (easily).

### Declaration.

| Macro | Description |
| --- | --- |
| `DEFINE_CONST_CONTINUOUS_TIMER(tag,ttype)` | Declare a constant continuous timer in **.c** file by declaring its variables. `tag` is the tag of the timer, and `ttype` is its type. |
| `EXTERN_CONST_CONTINUOUS_TIMER(x,ttype)` | Define external definitions in **.h** file. `tag` is the tag of the timer, and `ttype` is its type. |

### Variables.


| Variable | Description |
| --- | --- |
| `ConstContinuousCounter(tag)` | Counter of type `ttype`. Can be used as `lvalue`. Direct access to this variable is not recommended. |
| `ConstContinuousTimerFlag(tag)` | When `true`, this flag indicates active, working timer. When `false` the flag indicates a stopped timer. |
| `ConstContinuousTimerTick(tag)` | This flag, when `true` indicates that an interval has expired. When an application sees this flag risen, it should clear it by calling `ClearConstContinuousTick(tag)` and eventually execute some periodic actions. |

As we can see this timer does not have `Setting` variable, because it is constant timer. See `TickConstContinuousTimer(tag,per)` about initializing next interval.

| Macro | Description |
| --- | --- |
| `SetConstContinuousTimer(tag,per)` | This macro activates a timer with tag `tag` to measure intervals `per`. `per` must be an expression of the same type that was used in `DEFINE` and `EXTERN` macros. `ConstContinuousTimerFlag(tag)` is set to `true`, `ConstContinuousTimerTick(tag)` is set to `false`. `ConstContinuousCounter(tag)` is set to `per`. The macro disables the interrupts at the beginning and enables them at the end. |
| `SetConstFreeContinuousTimerI(tag,per)` | This macro activates a timer with tag `tag` to measure intervals `per`. `per` must be an expression of the same type that was used in `DEFINE` and `EXTERN` macros. `ConstContinuousTimerFlag(tag)` is set to `true`, `ConstContinuousTimerTick(tag)` is set to `false`. `ConstContinuousCounter(tag)` is set to `per`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. |
| `StopConstContinuosTimer(tag)` | This macro stops a timer with tag `tag`. It simply clears both `ConstContinuousTimerFlag(tag)` and `ConstContinuousTimerTick(tag)`. The macro disables the interrupts at the beginning and enables them at the end of the macro execution. |
| `ResetConstContinuousTimer(tag)` | This macro stops a timer with tag `tag`. It simply clears both `ConstContinuousTimerFlag(tag)` and `ConstContinuousTimerTick(tag)`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. |
| `ClearConstContinuousTimer(tag)` | This macro clears all variables associated with a timer with tag `tag`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. Note: Normally, this macro is not much useful. It exists for history purposes. |
| `SuspendConstContinuousTimer(tag)` | This macros suspends a timer with tag `tag` while keeping the value of the counter. |
| `ResumeConstContinuousTimer(tag)` |  This macro resumes a timer that was previously suspended. |
| `TickConstContinuousTimer(tag,per)` | This macro decrements by one `ConstContinuousCounter(tag)`. If the counter becomes zero, the macro raises `ConstContinuousTimerTick(tag)` and sets `ContinuousTimerCounter(tag)` to `per`. It is common `per` to be a constant expression. However, if `per` is a variable, then this timer is converted to a normal continuous timer. |

## Const Free Continuous Timer.

This timer measures consecutive equal intervals and at the end of each of the intervals raises `TimerTick` flag. So it is capable to trigger periodic events in an embedded system. This timer cannot change its interval (easily) and cannot be stopped.

### Declaration.

| Macro | Description |
| --- | --- |
| `DEFINE_CONST_FREE_CONTINUOUS_TIMER(tag,ttype)` | Declare a constant free continuous timer in **.c** file by declaring its variables. `tag` is the tag of the timer, and `ttype` is its type. |
| `EXTERN_CONST_FREE_CONTINUOUS_TIMER(x,ttype)` | Define external definitions in **.h** file. `tag` is the tag of the timer, and `ttype` is its type. |

### Variables.

| Variable | Description |
| --- | --- |
| `ConstFreeContinuousTimerCounter(tag)` | Counter of type `ttype`. Can be used as `lvalue`. Direct access to this variable is not recommended. |
| `ConstFreeContinuousTimerTick(x)` | This flag, when `true` indicates that an interval has expired. When an application sees this flag risen, it should clear it by calling `ClearConstFreeContinuousTick(tag)` and eventually execute some periodic actions. |

As we can see this timer does not have `Setting` variable, because it is a constant timer. See `TickConstContinuousTimer(tag,per)` about initializing next interval. Also, it has not `Flag` because it runs always and cannot be stopped.

### Manipulation macros.

| Macro | Description |
| --- | --- |
| `SetConstFreeContinuousTimer(tag,per)` | This macro initialize a timer with tag `tag` with a full period `per`. Currently measured period is precluded. `per` must be an expression of the same type that was used in `DEFINE` and `EXTERN` macros. `ConstFreeContinuousTimerTick(tag)` is set to `false`. must be an expression of the same type that was used in `DEFINE` and `EXTERN` macros. `ConstContinuousTimerFlag(tag)` is set to `true`, `ConstContinuousTimerTick(tag)` is set to `false`. `ConstFreeContinuousCounter(tag)` is set to `per`. The macro disables the interrupts at the beginning and enables them at the end. |
| `SetConstFreeContinuousTimerI(tag,per)` | This macro initialize a timer with tag `tag` with a full period `per`. Currently measured period is precluded. `per` must be an expression of the same type that was used in `DEFINE` and `EXTERN` macros. `ConstFreeContinuousTimerTick(tag)` is set to `false`. must be an expression of the same type that was used in `DEFINE` and `EXTERN` macros. `ConstContinuousTimerFlag(tag)` is set to `true`, `ConstContinuousTimerTick(tag)` is set to `false`. `ConstFreeContinuousCounter(tag)` is set to `per`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. |
| `ResetConstFreeContinuousTimer(tag,per)` | This macro currently is synonim of `SetConstFreeContinuousTimerI(tag,per)` |
| `ClearConstFreeContinuousTimer(tag,per)` | This macro currently is synonim of `SetConstFreeContinuousTimerI(tag,per)` |
| `TickConstFreeContinuousTimer(tag,per)` | his macro decrements by one `ConstFreeContinuousCounter(tag)`. If the counter becomes zero, the macro raises `ConstContinuousTimerTick(tag)` and sets `ContinuousTimerCounter(tag)` to `per`. It is common `per` to be a constant expression. However, if `per` is a variable, then this timer is effectively converted to a normal continuous timer. |

## Forward Backward Single Pulse Timer

Forward/Backward (in short FB) timers are capable to count forward to a preset value or backward to zero. The direction is determined by a `Direction` binary flag. It can be in one of the two states `FBS_FORWARD` and `FBS_BACKWARD`. The flag is controlled by the application - the application decides when the timer to count forward or backward.

While counting forward, when the timer's counter reaches the preset setting the timer's `Expired` flag is raised and the timer is stopped.

While counting backward, when the timer's counter reaches zero it stays here (does not make integer overflow).

FB timers act as integrating circuits - they charge linearly a capacitor in `FB_FORWARD` mode and discharge linearly in `FB_BACKWARD` mode. The `Setting` value acts as a comparator's threshold. When the counter reaches the threshold the comparator toggles an `Expired` flag. FB timers can be used in algorithms implementing temperature protection.

### Declaration.

| Macro | Description |
| --- | --- |
| `DEFINE_FBSINGLE_PULSE_TIMER(tag,ttype)` | Declare a FB timer in **.c** file by decalring its variables. `tag` is the tag of the timer, and `ttype` is its type. |
| `EXTERN_FBSINGLE_PULSE_TIMER(tag,ttype)` | Define external definitions in **.h** file. `tag` is the tag of the timer, and `ttype` is its type. |

### Variables.

| Variable | Description |
| --- | --- |
| `FBSinglePulseTimerSetting(tag)` | Setting of the timer. It can be used as `lvalue`. This variable hold the value to which timer counters forward. |
| `FBSinglePulseTimerCounter(tag)` | Counter of type `ttype`. It can be used as `lvalue`. Direct access to this variable is not recommended. |
| `FBSinglePulseTimerDirection(tag)` | This variable accepts one of the two values `FBS_BACKWARD` and `FBS_FORWARD`. It can be used as `lvalue`. It determines the direction of the timer. Direct access to this variable is not recommended. |
| `FBSinglePulseTimerFlag(tag)` | When `true`, this flag indicates active, working timer. When `false` the flag indicates a stopped timer. |
| `FBSinglePulseTimerExpired(tag)` | When `true`, the flag indicates that the time interval has expired. When `false` the flag indicates that the time interval is not expired or the timer is not started at all. It can be used as `lvalue`. |

### Manipulation macros.

| Macro | Description |
| --- | --- |
| `SetFBSinglePulseTimer(tag,per,direction)` | This macro activates a timer with tag `tag`, sets `FBSinglePulseTimerSetting(tag)` to `per` and `FBSinglePulseTimerDirection(tag)` to `direction`. The macro disables the interrupts at the beginning and enables them at the end. |
| `SetFBSinglePulseTimerI(tag,per,direction)` | This macro activates a timer with tag `tag`, sets `FBSinglePulseTimerSetting(tag)` to `per` and `FBSinglePulseTimerDirection(tag)` to `direction`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. |
| `StopFBSinglePulseTimer(tag)` | This macro stops a timer with tag `tag`. It simply clears both `FBSinglePulseTimerFlag(tag)` and `FBSinglePulseTimerExpired(tag)`. The macro disables the interrupts at the beginning and enables them at the end of its execution. |
| `ResetFBSinglePulseTimer(tag)` | This macro stops a timer with tag `tag`. It simply clears both `FBSinglePulseTimerFlag(tag)` and `FBSinglePulseTimerExpired(tag)`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. |
| `ClearFBSinglePulseTimer(tag)` | This macro clears the variables of a timer with tag `tag`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. |
| `ClearFBSinglePulseTimerExpired(tag)` | This macro clears `FBSinglePulseTimerExpired(tag)`. |
| `ChangeFBSinglePulseSetting(tag,per)` | This macro changes the setting `FBSinglePulseTimerSetting(tag)`. If `FBSinglePulseTimerCounter(tag)` >= `FBSinglePulseTimerSetting(tag)` the timer is stopped and `FBSinglePulseTimerExpired(tag)` is risen. |
| `SetFBSinglePulseTimerDirection(tag,d)` | This macro changes the direction of counting. |
| `TickFBSinglePulseTimer(tag)` | This macro executes increments or decrements `FBSinglePulseTimerCounter(tag)` depending on `FBSinglePulseTimerDirection(tag)`. If counting forward, if after incrementing `FBSinglePulseTimerCounter(tag)` becomes equal ot greater than `FBSinglePulseTimerSetting(tag)` the timer is stopped and `FBSinglePulseTimerExpired(tag)` is risen. if counting backward, the counter is not decremented below zero. |

## Forward Backward Variable Single Pulse Timer

Forward/Backward Variable (in short FBV) timers are capable to count forward to a preset value or backward to zero. The direction is determined by a `Direction` binary flag. It can be in one of the two states `FBS_FORWARD` and `FBS_BACKWARD`. The flag is controlled by the application - the application decides when the timer to count forward or backward.

While counting forward, when the timer's counter reaches the preset setting the timer's `Expired` flag is raised and the timer is stopped.

FBV timers have two variables that define steps for forward and for backward counting. This way it is possible to have different steps for the opposite directions.

While counting backward, when the timer's counter reaches zero it stays here (does not make integer overflow).

FB timers act as integrating circuits - they charge linearly a capacitor in `FB_FORWARD` mode and discharge linearly in `FB_BACKWARD` mode. The `Setting` value acts as a comparator's threshold. When the counter reaches the threshold the comparator toggles an `Expired` flag. FB timers can be used in algorithms implementing temperature protection.

An application may manipulate forward and backward steps depending on some external conditions. Par example if an FBV timer is used in temperature protection of a device, its forward step may be set bigger when the temperature is bigger. This way the timer will expire faster and will prevent the device from heat damage. Similarly, the backward step may simulate cooling.

### Declaration.

| Macro | Description |
| --- | --- |
| `DEFINE_FBVSINGLE_PULSE_TIMER(tag,ttype)` | Declare a FBV timer in **.c** file by decalring its variables. `tag` is the tag of the timer, and `ttype` is its type. |
| `EXTERN_FBVSINGLE_PULSE_TIMER(tag,ttype)` | Define external definitions in **.h** file. `tag` is the tag of the timer, and `ttype` is its type. |

### Variables.

| Variable | Description |
| --- | --- |
| `FBVSinglePulseTimerSetting(tag)` | Setting of the timer of type `ttype`. It can be used as `lvalue`. This variable hold the value to which timer counters forward. |
| `FBVSinglePulseTimerCounter(tag)` | Counter of type `ttype`. It can be used as `lvalue`. Direct access to this variable is not recommended. |
| `FBVSinglePulseTimerStepF(tag)` | This variable accepts one of the two values `FBS_BACKWARD` and `FBS_FORWARD`. It can be used as `lvalue`. It determines the direction of the timer. Direct access to this variable is not recommended. |
| `FBVSinglePulseTimerStepB(tag` | Forward step of type `ttype`. |
| `FBVSinglePulseTimerDirection(tag)` | Backward step of type `ttype`. |
| `FBVSinglePulseTimerFlag(tag)` | When `true`, this flag indicates active, working timer. When `false` the flag indicates a stopped timer. |
| `FBVSinglePulseTimerExpired(tag)` | When `true`, the flag indicates that the time interval has expired. When `false` the flag indicates that the time interval is not expired or the timer is not started at all. It can be used as `lvalue`. |

### Manipulation macros.

| Macro | Description |
| --- | --- |
| `SetFBVSinglePulseTimer(tag,per,stepF,stepB,direction)` | This macro activates a timer with tag `tag`. It sets the setting, the steps and the direction. The counter is set to zero. The macro disables the interrupts at the beginning and enables them at the end. |
| `SetFBVSinglePulseTimerI(tag,per,stepF,stepB,direction)` | This macro activates a timer with tag `tag`. It sets the setting, the steps and the direction. The counter is set to zero. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. |
| `StopFBVSinglePulseTimer(tag)` | This macro stops a timer with tag `tag`. It simply clears both flags `FBVSinglePulseTimerFlag(tag)` and `FBVSinglePulseTimerExpired(tag)`. |
| `ResetFBVSinglePulseTimer(tag)` | This macro stops a timer with tag `tag`. It simply clears both flags `FBVSinglePulseTimerFlag(tag)` and `FBVSinglePulseTimerExpired(tag)`. The macro disables the interrupts at the beginning and enables them at the end of its execution. |
| `ClearFBVSinglePulseTimer(tag)` | This macro clears the variables of a timer with tag `tag`. The macro does not touch the interrupts and thus it is convenient to be used with previously disabled interrupts. |
| `ClearFBVSinglePulseTimerExpired(tag)` | This macro clears `FBVSinglePulseTimerExpired(tag)`. |
| `SetFBVSinglePulseTimerDirection(tag,d)` | This macro changes the direction of counting. |
| `ChangeFBVSinglePulseTimerSetting(tag,per)` | This macro changes the setting `FBVSinglePulseTimerSetting(tag)`. If `FBVSinglePulseTimerCounter(tag)` >= `FBVSinglePulseTimerSetting(tag)` the timer is stopped and `FBVSinglePulseTimerExpired(tag)` is risen. |
| `SetFBVSinglePulseTimerStepF(tag,stepF)` | This macro changes the forward step. |
| `SetFBVSinglePulseTimerStepB(tag,stepB)` | This macro changes the backward step. |
| `TickFBVSinglePulseTimer(tag)` | This macro executes increments or decrements `FBSinglePulseTimerCounter(tag)` depending on `FBSinglePulseTimerDirection(tag)`. If counting forward, if after incrementing `FBSinglePulseTimerCounter(tag)` becomes equal ot greater than `FBVSinglePulseTimerSetting(tag)` the timer is stopped and `FBVSinglePulseTimerExpired(tag)` is risen. If counting backward, the counter is not decremented below zero. |
