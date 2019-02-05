/* timedefs.h
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

#if !defined(timedefs_h_included)
#define timedefs_h_included

// SINGLE PULSE TIMER
// variables
#define SinglePulseTimerCounter(x) ST_Counter_##x
#define SinglePulseTimerFlag(x) ST_Flag_##x
#define SinglePulseTimerExpired(x) ST_Expired_##x
// declaration in a header file
#define EXTERN_SINGLE_PULSE_TIMER(x,ttype) extern B1 ST_Flag_##x; \
    extern B1 ST_Expired_##x; \
    extern ttype ST_Counter_##x;
// variables definition in a C file
#define DEFINE_SINGLE_PULSE_TIMER(x,ttype) B1 ST_Flag_##x; \
    B1 ST_Expired_##x; \
    ttype ST_Counter_##x;

// start when interrupts are enabled
#define SetSinglePulseTimer(x,per) { \
    DisableInterrupts(); \
    ST_Counter_##x = (per); \
    ST_Flag_##x = true; \
    ST_Expired_##x = false; \
    EnableInterrupts(); \
}
// start when interrupts are disabled
#define SetSinglePulseTimerI(x,per) { \
    ST_Counter_##x = (per); \
    ST_Flag_##x = true; \
    ST_Expired_##x = false; \
}
// stop when interrupts are enabled
#define StopSinglePulseTimer(x) { \
    DisableInterrupts(); \
    ST_Flag_##x = false; \
    ST_Expired_##x = false; \
    EnableInterrupts(); \
}
// timer reset when interrupts are disabled
#define ResetSinglePulseTimer(x) { \
    ST_Flag_##x = false; \
    ST_Expired_##x = false; \
}
// timer clear
#define ClearSinglrPulseTimer(x) { \
    ST_Flag_##x = false; \
    ST_Expired_##x = false; \
    ST_Counter_##x = 0u; \
}
// suspend timer
#define SuspendSinglePulseTimer(x) { \
    DisableInterrupts(); \
    ST_Flag_##x = false; \
    EnableInterrupts(); \
}
// resume timer
#define ResumeSinglePulseTimer(x) { \
    DisableInterrupts(); \
    ST_Flag_##x = true; \
    EnableInterrupts(); \
}
// tick
#define TickSinglePulseTimer(x) { \
    if (ST_Flag_##x == true) { \
        if (--ST_Counter_##x == 0u) { \
            ST_Flag_##x = false; \
            ST_Expired_##x = true; \
        } \
    } \
}
#define ClearSinglePulseTimerExpired(x) { \
    ST_Expired_##x = false; \
}

// CONTINUOUS TIMER
// variables
#define ContinuousTimerCounter(x) CT_Counter_##x
#define ContinuousTimerSetting(x) CT_Setting_##x
#define ContinuousTimerFlag(x) CT_Flag_##x
#define ContinuousTimerTick(x) CT_Tick_##x
#define EXTERN_CONTINUOUS_TIMER(x,ttype) extern ttype CT_Counter_##x; \
    extern ttype CT_Setting_##x; \
    extern B1 CT_Flag_##x; \
    extern B1 CT_Tick_##x;
#define DEFINE_CONTINUOUS_TIMER(x,ttype) ttype CT_Counter_##x; \
    ttype CT_Setting_##x; \
    B1 CT_Flag_##x; \
    B1 CT_Tick_##x;

// start when interrupts are enabled
#define SetContinuousTimer(x,per) { \
    DisableInterrupts(); \
    CT_Setting_##x = (per); \
    CT_Counter_##x = (per); \
    CT_Flag_##x = true; \
    CT_Tick_##x = false; \
    EnableInterrupts(); \
}
// start when interrupts are disabled
#define SetContinuousTimerI(x,per) { \
    CT_Setting_##x = (per); \
    CT_Counter_##x = (per); \
    CT_Flag_##x = true; \
    CT_Tick_##x = false; \
}
// stop when interrupts are enabled
#define StopContinuousTimer(x) { \
    DisableInterrupts(); \
    CT_Flag_##x = false; \
    CT_Tick_##x = false; \
    EnableInterrupts(); \
}
// timer reset when interrupts are disabled
#define ResetContinuousTimer(x) { \
    CT_Flag_##x = false; \
    CT_Tick_##x = false; \
}
// clear timer
#define ClearContinuousTimer(x) { \
    CT_Flag_##x = false; \
    CT_Tick_##x = false; \
    CT_Counter_##x = 0u; \
    CT_Setting_##x = 0u; \
}
// pause (suspend)
#define SuspendContinuousTimer(x) { \
    DisableInterrupts(); \
    PT_Flag_##x = false; \
    EnableInterrupts(); \
}
// resume
#define ResumeContinuousTimer(x) { \
    DisableInterrupts(); \
    CT_Flag_##x = true; \
    EnableInterrupts(); \
}
// tick
#define TickContinuousTimer(x) { \
    if (CT_Flag_##x == true) { \
        if (--CT_Counter_##x == 0u) { \
            CT_Counter_##x = CT_Setting_##x; \
            CT_Tick_##x = true; \
        } \
    } \
}
#define ClearContinuousTimerTick(x) { \
    CT_Tick_##x = false; \
}

// CONST_CONTINUOUS_TIMER
// variables
#define ConstContinuousCounter(x) CCT_Counter_##x
#define ConstContinuousTimerFlag(x) CCT_Flag_##x
#define ConstContinuousTimerTick(x) CCT_Tick_##x
#define EXTERN_CONST_CONTINUOUS_TIMER(x,ttype) extern ttype CCT_Counter_##x; \
    extern B1 CCT_Flag_##x; \
    extern B1 CCT_Tick_##x;
#define DEFINE_CONST_CONTINUOUS_TIMER(x,ttype) ttype CCT_Counter_##x; \
    B1 CCT_Flag_##x; \
    B1 CCT_Tick_##x;

// start when interrupts are enabled
#define SetConstContinuousTimer(x,per) { \
    DisableInterrupts(); \
    CCT_Counter_##x = (per); \
    CCT_Flag_##x = true; \
    CCT_Tick_##x = false; \
    EnableInterrupts(); \
}
// start when interrupts are disabled
#define SetConstContinuosTimerI(x,per) { \
    CCT_Counter_##x = (per); \
    CCT_Flag_##x = true; \
    CCT_Tick_##x = false; \
}
// stop when interrupts are enabled
#define StopConstContinuosTimer(x) { \
    DisableInterrupts(); \
    CCT_Flag_##x = false; \
    CCT_Tick_##x = false; \
    EnableInterrupts(); \
}
// timer reset when interrupts are disabled
#define ResetConstContinuosTimer(x) { \
    CCT_Flag_##x = false; \
    CCT_Tick_##x = false; \
}
// clear timer
#define ClearConstContinuosTimer(x) { \
    CCT_Flag_##x = false; \
    CCT_Tick_##x = false; \
    CCT_Counter_##x = 0u; \
}
// pause (suspend)
#define SuspendContinuosTimer(x) { \
    DisableInterrupts(); \
    CCT_Flag_##x = false; \
    EnableInterrupts(); \
}
// resume
#define ResumeConstContinuousTimer(x) { \
    DisableInterrupts(); \
    CCT_Flag_##x = true; \
    EnableInterrupts(); \
}
// tick
#define TickConstContinuousTimer(x,per) { \
    if (CCT_Flag_##x == true) { \
        if (--CCT_Counter_##x == 0u) { \
            CCT_Counter_##x = (per); \
            CCT_Tick_##x = true; \
        } \
    } \
}
#define ClearConstContinuousTick(x) { \
    CCT_Tick_##x = false; \
}

// CONST_FREE_CONTINUOUS_TIMER
// variables
#define ConstFreeContinuousTimerCounter(x) CFCT_Counter_##x
#define ConstFreeContinuousTimerTick(x) CFCT_Tick_##x
#define EXTERN_CONST_FREE_CONTINUOUS_TIMER(x,ttype) extern ttype CFCT_Counter_##x; \
    extern B1 CFCT_Tick_##x;
#define DEFINE_CONST_FREE_CONTINUOUS_TIMER(x,ttype) ttype CFCT_Counter_##x; \
    B1 CFCT_Tick_##x;

// start when interrupts are enabled
#define SetConstFreeContinuousTimer(x,per) { \
    DisableInterrupts(); \
    CFCT_Counter_##x = (per); \
    CFCT_Tick_##x = false; \
    EnableInterrupts(); \
}
// start when interrupts are disabled
#define SetConstFreeContinuousTimerI(x,per) { \
    CFCT_Counter_##x = (per); \
    CFCT_Tick_##x = false; \
}
// timer reset when interrupts are disabled
#define ResetConstFreeContinuousTimer(x,per) { \
    CFCT_Counter_##x = (per); \
    CFCT_Tick_##x = false; \
}
// clear timer
#define ClearConstFreeContinuousTimer(x,per) { \
    CFCT_Counter_##x = (per); \
    CFCT_Tick_##x = false; \
}
// tick
#define TickConstFreeContinuousTimer(x,per) { \
    if (--CFCT_Counter_##x == 0u) { \
        CFCT_Counter_##x = (per); \
        CFCT_Tick_##x = true; \
    } \
}
#define ClearConstFreeContinuousTimerTick(x) { \
    CFCT_Tick_##x = false; \
}

// forward/backward single pulse timers

#define FBS_FORWARD (true)
#define FBS_BACKWARD (false)

// FB_SINGLE_SHOT_TIMER
// variables
#define FBSinglePulseTimerFlag(x) FBS_Flag_##x
#define FBSinglePulseTimerExpired(x) FBS_Expired_##x
#define FBSinglePulseTimerDirection(x) FBS_Direction_##x
#define FBSinglePulseTimerCounter(x) FBS_Counter_##x
#define FBSinglePulseTimerSetting(x) FBS_Setting_##x
// declaration in a header file
#define EXTERN_FBSINGLE_PULSE_TIMER(x,ttype) extern B1 FBS_Flag_##x; \
    extern B1 FBS_Expired_##x; \
    extern B1 FBS_Direction_##x; \
    extern ttype FBS_Counter_##x; \
    extern ttype FBS_Setting_##x;
// variables definition in C file
#define DEFINE_FBSINGLE_PULSE_TIMER(x,ttype) B1 FBS_Flag_##x; \
    B1 FBS_Expired_##x; \
    B1 FBS_Direction_##x; \
    ttype FBS_Counter_##x; \
    ttype FBS_Setting_##x;

// start when interrupts are enabled
#define SetFBSinglePulseTimer(x,per,direction) { \
    DisableInterrupts(); \
    FBS_Counter_##x = 0u; \
    FBS_Setting_##x = (per); \
    FBS_Direction_##x = (direction); \
    FBS_Flag_##x = true; \
    FBS_Expired_##x = false; \
    EnableInterrupts(); \
}
// start when interrupts are disabled
#define SetFBSinglePulseTimerI(x,per,direction) { \
    FBS_Counter_##x = 0u; \
    FBS_Setting_##x = (per); \
    FBS_Direction_##x = (direction); \
    FBS_Flag_##x = true; \
    FBS_Expired_##x = false; \
}
// tick
#define TickFBSinglePulseTimer(x) { \
    if (FBS_Flag_##x == true) { \
        if (FBS_Direction_##x == FBS_FORWARD) { \
            if (++FBS_Counter_##x >= FBS_Setting_##x) { \
                FBS_Flag_##x = false; \
                FBS_Expired_##x = true; \
            } \
        } else { \
            if (FBS_Counter_##x != 0u) { \
                FBS_Counter_##x--; \
            } \
        } \
    } \
}
#define StopFBSinglePulseTimer(x) { \
    DisableInterrupts(); \
    FBS_Flag_##x = false; \
    FBS_Expired_##x = false; \
    EnableInterrupts(); \
}
// timer reset when interrupts are disabled
#define ResetFBSinglePulseTimer(x) { \
    FBS_Flag_##x = false; \
    FBS_Expired_##x = false; \
}
// clear timer
#define ClearFBSinglePulseTimer(x) { \
    FBS_Flag_##x = false; \
    FBS_Expired_##x = false; \
    FBS_Direction_##x = 0u; \
    FBS_Counter_##x = 0u; \
    FBS_Setting_##x = 0u; \
}
#define ClearFBSinglePulseTimerExpired(x) { \
    FBS_Expired_##x = false; \
}
#define ReviveFBSinglePulseTimer(x) { \
    DisableInterrupts(); \
    FBS_Expired_##x = false; \
    FBS_Flag_##x = true; \
    FBS_Direction_##x = FBS_BACKWARD; \
    EnableInterrupts(); \
}
#define ChangeFBSinglePulseSetting(x,per) { \
    DisableInterrupts(); \
    FBS_Setting_##x = (per); \
    if (FBS_Direction_##x == FBS_FORWARD) { \
        if (FBS_Counter_##x >= FBS_Setting_##x) { \
            FBS_Flag_##x = false; \
            FBS_Expired_##x = true; \
        } \
    } \
    EnableInterrupts(); \
}
#define SetFBSinglePulseTimerDirection(x,d) { \
    FBS_Direction_##x = (d); \
}

// FBV_SINGLE_PULSE_TIMER (V = variable step)
// variables
#define FBVSinglePulseTimerFlag(x) FBVS_Flag_##x
#define FBVSinglePulseTimerExpired(x) FBVS_Expired_##x
#define FBVSinglePulseTimerDirection(x) FBVS_Direction_##x
#define FBVSinglePulseTimerCounter(x) FBVS_Counter_##x
#define FBVSinglePulseTimerSetting(x) FBVS_Setting_##x
#define FBVSinglePulseTimerStepF(x) FBVS_StepF_##x
#define FBVSinglePulseTimerStepB(x) FBVS_StepB_##x
// declaration in a header file
#define EXTERN_FBVSINGLE_PULSE_TIMER(x,ttype) extern B1 FBVS_Flag_##x; \
    extern B1 FBVS_Expired_##x; \
    extern B1 FBVS_Direction_##x; \
    extern ttype FBVS_Counter_##x; \
    extern ttype FBVS_Setting_##x; \
    extern ttype FBVS_StepF_##x; \
    extern ttype FBVS_StepB_##x;
// variables definition in C file
#define DEFINE_FBVSINGLE_PULSE_TIMER(x,ttype) B1 FBVET_Flag_##x; \
    B1 FBVS_Expired_##x; \
    B1 FBVS_Direction_##x; \
    ttype FBVS_Counter_##x; \
    ttype FBVS_Setting_##x; \
    ttype FBVS_StepF_##x; \
    ttype FBVS_StepB_##x;

// start when interrupts are enabled
// per+step should be in ttype domain
#define SetFBVSinglePulseTimer(x,per,stepF,stepB,direction) { \
    DisableInterrupts(); \
    FBVS_Counter_##x = 0u; \
    FBVS_Setting_##x = (per); \
    FBVS_StepF_##x = (stepF); \
    FBVS_StepB_##x = (stepB); \
    FBVS_Direction_##x = (direction); \
    FBVS_Flag_##x = true; \
    FBVS_Expired_##x = false; \
    EnableInterrupts(); \
}
// start when interrupts are disabled
#define SetFBVSinglePulseTimerI(x,per,stepF,stepB,direction) { \
    FBVS_Counter_##x = 0u; \
    FBVS_Setting_##x = (per); \
    FBVS_StepF_##x = (stepF); \
    FBVS_StepB_##x = (stepB); \
    FBVS_Direction_##x = (direction); \
    FBVS_Flag_##x = true; \
    FBVS_Expired_##x = false; \
}
// tick
#define TickFBVSinglePulseTimer(x) { \
    if (FBVS_Flag_##x == true) { \
        if (FBVS_Direction_##x == FBS_FORWARD) { \
            FBVS_Counter_##x += FBVS_StepF_##x; \
            if (FBVS_Counter_##x >= FBVS_Setting_##x) { \
                FBVS_Flag_##x = false; \
                FBVS_Expired_##x = true; \
            } \
        } else { \
            if (FBVS_Counter_##x > FBVS_StepB_##x) { \
                FBVS_Counter_##x -= FBVS_StepB_##x; \
            } else { \
                FBVS_Counter_##x = 0u; \
            } \
        } \
    } \
}
#define StopFBVSinglePulseTimer(x) { \
    DisableInterrupts(); \
    FBVS_Flag_##x = false; \
    FBVS_Expired_##x = false; \
    EnableInterrupts(); \
}
// timer reset when interrupts are disabled
#define ResetFBVSinglePulseTimer(x) { \
    FBVS_Flag_##x = false; \
    FBVS_Expired_##x = false; \
}
// clear timer
#define ClearFBVSinglePulseTimer(x) { \
    FBVS_Flag_##x = false; \
    FBVS_Expired_##x = false; \
    FBVS_Direction_##x = false; \
    FBVS_Counter_##x = 0u; \
    FBVS_Setting_##x = 0u; \
    FBVS_StepF_##x = 0u; \
    FBVS_StepB_##x = 0u; \
}
#define ClearFBVSinglePulseTimerExpired(x) { \
    FBVS_Expired_##x = false; \
}
#define SetFBVSinglePulseTimerDirection(x,d) { \
    FBVS_Direction_##x = (d); \
}
#define ReviveFBVSinglePulseTimer(x) { \
    DisableInterrupts(); \
    FBVS_Expired_##x = false; \
    FBVS_Flag_##x = true; \
    FBVS_Direction_##x = FBS_BACKWARD; \
    EnableInterrupts(); \
}
#define ChangeFBVSinglePulseTimerSetting(x,per) { \
    DisableInterrupts(); \
    FBVS_Setting_##x = (per); \
    if (FBVS_Direction_##x == FBS_FORWARD) { \
        if (FBVS_Counter_##x >= FBVS_Setting_##x) { \
            FBVS_Flag_##x = false; \
            FBVS_Expired_##x = true; \
        } \
    } \
    EnableInterrupts(); \
}
#define SetFBVSinglePulseTimerStepF(x,stepF) { \
    DisableInterrupts(); \
    FBVS_StepF_##x = (stepF); \
    EnableInterrupts(); \
}
#define SetFBVSinglePulseTimerStepB(x,stepB) { \
    DisableInterrupts(); \
    FBVS_StepB_##x = (stepB); \
    EnableInterrupts(); \
}

// asymmetric continuous timers
// generation of asymmetric sequences
//
//   +------+            +------+            +-
//   | high |     low    | high |     low    |
//  -+      +------------+      +------------+

#define ACT_STATE_HIGH  (true)
#define ACT_STATE_LOW   (false)

// ASYMMETRIC_CONTINUOUS_TIMER
// variables
#define AsymmetricContinuousTimerCounter(x) ACT_Counter_##x
#define AsymmetricContinuousTimerSettingHigh(x) ACT_SettingHigh_##x
#define AsymmetricContinuousTimerSettingLow(x) ACT_SettingLow_##x
#define AsymmetricContinuousTimerFlag(x) ACT_Flag_##x
#define AsymmetricContinuousTimerState(x) ACT_State_##x
#define AsymmetricContinuousTimerTick(x) ACT_Tick_##x
#define EXTERN_ASYMMETRIC_CONTINUOUS_TIMER(x,ttype) extern ttype ACT_Counter_##x; \
    extern ttype ACT_SettingHigh_##x; \
    extern ttype ACT_SettingLow_##x; \
    extern B1 ACT_Flag_##x; \
    extern B1 ACT_State_##x; \
    extern B1 ACT_Tick_##x;
#define DEFINE_ASYMMETRIC_CONTINUOUS_TIMER(x,ttype) ttype ACT_Counter_##x; \
    ttype ACT_SettingHigh_##x; \
    ttype ACT_SettingLow_##x; \
    B1 ACT_Flag_##x; \
    B1 ACT_State_##x; \
    B1 ACT_Tick_##x;

// start when interrupts are enabled
#define SetAsymmetricContinuousTimer(x,perh, perl) { \
    DisableInterrupts(); \
    ACT_SettingHigh_##x = (perh); \
    ACT_Counter_##x = (perh); \
    ACT_SettingLow_##x = (perl); \
    ACT_State_##x = ACT_STATE_HIGH; \
    ACT_Flag_##x = true; \
    ACT_Tick_##x = false; \
    EnableInterrupts(); \
}
// start when interrupts are disabled
#define SetAsymmetricContinuousTimerI(x,perh,perl) { \
    ACT_SettingHigh_##x = (perh); \
    ACT_Counter_##x = (perh); \
    ACT_SettingLow_##x = (perl); \
    ACT_State_##x = ACT_STATE_HIGH; \
    ACT_Flag_##x = true; \
    ACT_Tick_##x = false; \
}
// stop when interrupts are enabled
#define StopAsymmetricContinuousTimer(x) { \
    DisableInterrupts(); \
    ACT_Flag_##x = false; \
    ACT_Tick_##x = false; \
    EnableInterrupts(); \
}
// timer reset when interrupts are disabled
#define ResetAsymmetricContinuousTimer(x) { \
    ACT_Flag_##x = false; \
    ACT_Tick_##x = false; \
}
// clear timer
#define ClearAsymmetricContinuousTimer(x) { \
    ACT_Flag_##x = false; \
    ACT_State_##x = false; \
    ACT_Tick_##x = false; \
    ACT_Counter_##x =  0u; \
    ACT_SettingHigh_##x = 0u; \
    ACT_SettingLow_##x = 0u; \
}
// pause (suspend)
#define SuspendAsymmetricContinuousTimer(x) { \
    DisableInterrupts(); \
    PeriodTimerFlag_##x = false; \
    EnableInterrupts(); \
}
// resume
#define ResumeAsymmetricContinuousTimer(x) { \
    DisableInterrupts(); \
    PeriodTimerFlag_##x = true; \
    EnableInterrupts(); \
}
#define ChangeAsymmetricContinuousTimerSetting(x,perh,perl) { \
    DisableInterrupts(); \
    ACT_SettingHigh_##x = (perh); \
    ACT_SettingLow_##x = (perl); \
    EnableInterrupts(); \
}
#define ChangeAsymmetricContinuousTimerState(x,perh,perl,state) { \
    DisableInterrupts(); \
    ACT_State_##x = (state); \
    ACT_SettingHigh_##x = (perh); \
    ACT_SettingLow_##x = (perl); \
    EnableInterrupts(); \
}
// tick
#define TickAsymmetricContinuousTimer(x) { \
    if (ACT_Flag_##x == true) { \
        if (--ACT_Counter_##x == 0u) { \
            if (ACT_State_##x == ACT_STATE_HIGH) { \
                if (ACT_SettingLow_##x != 0u) { \
                    ACT_State_##x = ACT_STATE_LOW; \
                    ACT_Counter_##x = ACT_SettingLow_##x; \
                } else { \
                    ACT_Counter_##x = ACT_SettingHigh_##x; \
                } \
            } else { \
                if (ACT_SettingHigh_##x != 0u) { \
                    ACT_State_##x = ACT_STATE_HIGH; \
                    ACT_Counter_##x = ACT_SettingHigh_##x; \
                } else { \
                    ACT_Counter_##x = ACT_SettingLow_##x; \
                } \
            } \
            ACT_Tick_##x = true; \
        } \
    } \
}
#define ClearAsymmetricContinuousTimerTick(x) { \
    ACT_Tick_##x = false; \
}

// ASYMMETRIC SINGLE PULSE TIMER
//
//          +--------+
//   first  | second |
// +--------+        +
// or
// +--------+
// | first  | second
// +        +--------+

// variables
#define AsymmetricSinglePulseTimerCounter(x) ASP_Counter_##x
#define AsymmetricSinglePulseTimerSettingFirst(x) ASP_SettingFirst_##x
#define AsymmetricSinglePulseTimerSettingSecond(x) ASP_SettingSecond_##x
#define AsymmetricSinglePulseTimerFlag(x) ASP_Flag_##x
#define AsymmetricSinglePulseTimerSemiperiod(x) ASP_sp_##x
#define AsymmetricSinglePulseTimerState(x) ASP_State_##x
#define AsymmetricSinglePulseTimerSemiperiodExpired(x) ASP_SemiPeriod_Expired_##x
#define AsymmetricSinglePulseTimerExpired(x) ASP_Expired_##x
#define EXTERN_ASYMMETRIC_SINGLE_PULSE_TIMER(x,ttype) extern ttype ASP_Counter_##x; \
    extern ttype ASP_SettingFirst_##x; \
    extern ttype ASP_SettingSecond_##x; \
    extern B1 ASP_Flag_##x; \
    extern B1 ASP_sp_##x; \
    extern B1 ASP_State_##x; \
    extern B1 ASP_SemiPeriod_Expired_##x; \
    extern B1 ASP_Expired_##x;
#define DEFINE_ASYMMETRIC_SINGLE_PULSE_TIMER(x,ttype) ttype ASP_Counter_##x; \
    ttype ASP_SettingFirst_##x; \
    ttype ASP_SettingSecond_##x; \
    B1 ASP_Flag_##x; \
    B1 ASP_sp_##x; \
    B1 ASP_State_##x; \
    B1 ASP_SemiPeriod_Expired_##x; \
    B1 ASP_Expired_##x;

// start when interrupts are enabled
#define SetAsymmetricSinglePulseTimer(x,first,second,istate) { \
    DisableInterrupts(); \
    ASP_SettingFirst_##x = (first); \
    ASP_SettingSecond_##x = (second); \
    if (first != 0u) { \
        ASP_Counter_##x = (first); \
        ASP_State_##x = istate; \
        ASP_sp_##x = false; \
        ASP_SemiPeriod_Expired_##x = false; \
        ASP_Flag_##x = true; \
        ASP_Expired_##x = false; \
    } else if (second != 0u) { \
        ASP_Counter_##x = (second); \
        ASP_State_##x = !istate; \
        ASP_sp_##x = true; \
        ASP_SemiPeriod_Expired_##x = true; \
        ASP_Flag_##x = true; \
        ASP_Expired_##x = false; \
    } else { \
        ASP_sp_##x = false; \
        ASP_Flag_##x = false; \
        ASP_SemiPeriod_Expired_##x = false; \
        ASP_Expired_##x = false; \
    } \
    EnableInterrupts(); \
}
// start when interrupts are disabled
#define SetAsymmetricSinglePulseTimerI(x,first,second,istate) { \
    ASP_SettingFirst_##x = (first); \
    ASP_SettingSecond_##x = (second); \
    ASP_Counter_##x = (first); \
    ASP_State_##x = istate; \
    ASP_Flag_##x = true; \
    ASP_sp_##x = false; \
    ASP_SemiPeriod_Expired_##x = false; \
    ASP_Expired_##x = false; \
}
// stop when interrupts are enabled
#define StopAsymmetricSinglePulseTimer(x) { \
    DisableInterrupts(); \
    ASP_Flag_##x = false; \
    ASP_sp_##x = false; \
    ASP_State_##x = ACT_STATE_LOW; \
    ASP_SemiPeriod_Expired_##x = false; \
    ASP_Expired_##x = false; \
    EnableInterrupts(); \
}
// timer reset when interrupts are disabled
#define ResetAsymmetricSinglePulseTimer(x) { \
    ASP_Flag_##x = false; \
    ASP_sp_##x = false; \
    ASP_State_##x = ACT_STATE_LOW; \
    ASP_SemiPeriod_Expired_##x = false; \
    ASP_Expired_##x = false; \
}
// clear timer
#define ClearAsymmetricSinglePulseTimer(x) { \
    ASP_Counter_##x = 0u; \
    ASP_SettingFirst_##x = 0u; \
    ASP_SettingSecond_##x = 0u; \
    ASP_Flag_##x = false; \
    ASP_sp_##x = false; \
    ASP_State_##x = false; \
    ASP_SemiPeriod_Expired_##x = false; \
    ASP_Expired_##x = false; \
}
// tick
#define TickAsymmetricSinglePulseTimer(x) { \
    if (ASP_Flag_##x == true) { \
        if (--ASP_Counter_##x == 0u) { \
            if (ASP_sp_##x == false) { \
                ASP_SemiPeriod_Expired_##x = true; \
                if (ASP_SettingSecond_##x != 0u) { \
                    ASP_Counter_##x = ASP_SettingSecond_##x; \
                    ASP_State_##x = !ASP_State_##x; \
                    ASP_sp_##x = true; \
                } else { \
                    ASP_Flag_##x = false; \
                    ASP_Expired_##x = true; \
                } \
            } else { \
                ASP_Flag_##x = false; \
                ASP_Expired_##x = true; \
            } \
        } \
    } \
}

// BURST GENERATOR

//  ------ pulses -----
//  +---+  +---+  +---+            +---+  +---+  +---+
//  |   |  |   |  |   |            |   |  |   |  |   |
//  |   |  |   |  |   |            |   |  |   |  |   |
// -+   +--+   +--+   +------------+   +--+   +--+   +---------
//   ht  lt                 it
// pulses - number of the pulses in a package
// ht - high time
// lt - low time
// it - idle time between the packages

#define BG_STATE_HIGH   (true)
#define BG_STATE_LOW    (false)

#define BurstGeneratorCounter(x) BG_Counter_##x
#define BurstGeneratorPulses(x) BG_pulses_##x
#define BurstGeneratorHighTime(x) BG_ht_##x
#define BurstGeneratorLowTime(x) BG_lt_##x
#define BurstGeneratorIdleTime(x) BG_it_##x
#define BurstGeneratorPulseCounter(x) BG_pc_##x
#define BurstGeneratorState(x) BG_state_##x
#define BurstGeneratorFlag(x) BG_Flag_##x
#define BurstGeneratorTick(x) BG_Tick_##x
#define EXTERN_BURST_GENERATOR(x,ttype) extern ttype BG_Counter_##x; \
    extern uint8_t BG_pulses_##x; \
    extern ttype BG_ht_##x; \
    extern ttype BG_lt_##x; \
    extern ttype BG_it_##x; \
    extern uint8_t BG_pc_##x; \
    extern uint8_t BG_state_##x; \
    extern B1 BG_Flag_##x; \
    extern B1 BG_Tick_##x;
#define DEFINE_BURST_GENERATOR(x,ttype) ttype BG_Counter_##x; \
    uint8_t BG_pulses_##x; \
    ttype BG_ht_##x; \
    ttype BG_lt_##x; \
    ttype BG_it_##x; \
    uint8_t BG_pc_##x; \
    uint8_t BG_state_##x; \
    B1 BG_Flag_##x; \
    B1 BG_Tick_##x;

// start when interrupts are enabled
#define SetBurstGenerator(x,pulses,ht,lt,it) { \
    DisableInterrupts(); \
    BG_pulses_##x = (pulses); \
    BG_ht_##x = (ht); \
    BG_lt_##x = (lt); \
    BG_it_##x = (it); \
    BG_Counter_##x = 1u; \
    BG_state_##x = BG_STATE_LOW; \
    BG_pc_##x = 0u; \
    BG_Tick_##x = false; \
    BG_Flag_##x = true; \
    EnableInterrupts(); \
}
#define SetBurstGeneratorI(x,pulses,ht,lt,it) { \
    BG_pulses_##x = (pulses); \
    BG_ht_##x = (ht); \
    BG_lt_##x = (lt); \
    BG_it_##x = (it); \
    BG_Counter_##x = 1u; \
    BG_state_##x = BG_STATE_LOW; \
    BG_pc_##x = 0u; \
    BG_Tick_##x = false; \
    BG_Flag_##x = true; \
}
// reset
#define ResetBurstGenerator(x) { \
    BG_state_##x = BG_STATE_LOW; \
    BG_Flag_##x = false; \
    BG_Tick_##x = false; \
}
// clear timer
#define ClearBurstGenerator(x) { \
    BG_Counter_##x = 0u; \
    BG_pulses_##x = 0u; \
    BG_ht_##x = 0u; \
    BG_lt_##x = 0u; \
    BG_it_##x = 0u; \
    BG_pc_##x = 0u; \
    BG_state_##x = BG_STATE_LOW; \
    BG_Flag_##x = false; \
    BG_Tick_##x = false; \
}
#define StopBurstGenerator(x) { \
    DisableInterrupts(); \
    BG_state_##x = BG_STATE_LOW; \
    BG_Flag_##x = false; \
    BG_Tick_##x = true; \
    EnableInterrupts(); \
}
// tick
#define TickBurstGenerator(x) { \
    if (BG_Flag_##x == true) { \
        if (--BG_Counter_##x == 0u) { \
            if (BG_state_##x == BG_STATE_LOW) { \
                if (BG_pc_##x == 0u) { \
                    BG_pc_##x = BG_pulses_##x; \
                } \
                BG_state_##x = BG_STATE_HIGH; \
                BG_Counter_##x = BG_ht_##x; \
            } else { \
                BG_state_##x = BG_STATE_LOW; \
                if (--BG_pc_##x != 0u) { \
                    BG_Counter_##x = BG_lt_##x; \
                } else { \
                    BG_Counter_##x = BG_it_##x; \
                } \
            } \
            BG_Tick_##x = true; \
        } \
    } \
}

// with output

#define SetBurstGeneratorWithOutput(x,pulses,ht,lt,it,out) { \
    DisableInterrupts(); \
    BG_pulses_##x = (pulses); \
    BG_ht_##x = (ht); \
    BG_lt_##x = (lt); \
    BG_it_##x = (it); \
    BG_Counter_##x = 1u; \
    out = lowstate; \
    BG_state_##x = BG_STATE_LOW; \
    BG_pc_##x = 0u; \
    BG_Tick_##x = false; \
    BG_Flag_##x = true; \
    EnableInterrupts(); \
}
#define SetBurstGeneratorIWithOutput(x,pulses,ht,lt,it,out) { \
    BG_pulses_##x = (pulses); \
    BG_ht_##x = (ht); \
    BG_lt_##x = (lt); \
    BG_it_##x = (it); \
    BG_Counter_##x = 1u; \
    out = lowstate; \
    BG_state_##x = BG_STATE_LOW; \
    BG_pc_##x = 0u; \
    BG_Tick_##x = false; \
    BG_Flag_##x = true; \
}
// reset
#define ResetBurstGeneratorWithOutput(x,out) { \
    out = lowstate; \
    BG_state_##x = BG_STATE_LOW; \
    BG_Flag_##x = false; \
    BG_Tick_##x = false; \
}
#define StopBurstGeneratorWithOutput(x,out) { \
    DisableInterrupts(); \
    out = lowstate; \
    BG_state_##x = BG_STATE_LOW; \
    BG_Flag_##x = false; \
    BG_Tick_##x = true; \
    EnableInterrupts(); \
}
// tick with output
#define TickBurstGeneratorWithOutput(x,out) { \
    if (BG_Flag_##x == true) { \
        if (--BG_Counter_##x == 0u) { \
            if (BG_state_##x == BG_STATE_LOW) { \
                out = highstate; \
                if (BG_pc_##x == 0u) { \
                    BG_pc_##x = BG_pulses_##x; \
                } \
                BG_state_##x = BG_STATE_HIGH; \
                BG_Counter_##x = BG_ht_##x; \
            } else { \
                out = lowstate; \
                BG_state_##x = BG_STATE_LOW; \
                if (--BG_pc_##x != 0u) { \
                    BG_Counter_##x = BG_lt_##x; \
                } else { \
                    BG_Counter_##x = BG_it_##x; \
                } \
            } \
            BG_Tick_##x = true; \
        } \
    } \
}

#endif  // !defined(timedefs_h_included)

// End of timedefs.h
