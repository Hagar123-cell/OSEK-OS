/******************************************************************************
 *
 * Module: OS
 *
 * File Name: Os.h
 *
 * Description: General OS definitions 
 *
 *******************************************************************************/

#ifndef OS_H
#define OS_H

#include "Std_Types.h"
#include "Os_Cfg.h"

#define ResourceType  char
/*
 *  This data type is used for all status information the API services offer
 */
typedef enum{
  
  E_OK,
  E_OS_ACCESS, 
  E_OS_CALLEVEL, 
  E_OS_ID, 
  E_OS_LIMIT, 
  E_OS_NOFUNC, 
  E_OS_RESOURCE, 
  E_OS_STATE, 
  E_OS_VALUE
  
}StatusType;

/*******************************************************************************
 *                      Alarm API Prototypes                                    *
 *******************************************************************************/

/* The system service GetAlarmBase reads the alarm base 
   characteristics. The return value <Info> is a structure in which 
   the information of data type AlarmBaseType is stored. */
StatusType GetAlarmBase ( AlarmType AlarmID, AlarmBaseRefType Info );

/* The system service GetAlarm returns the relative value in ticks 
    before the alarm <AlarmID> expires. */
StatusType GetAlarm ( AlarmType AlarmID, TickRefType Tick );

/* The system service occupies the alarm <AlarmID> element. 
    After <increment> ticks have elapsed, the task assigned to the 
    alarm <AlarmID> is activated or the assigned event (only for 
    extended tasks) is set or the alarm-callback routine is called. */
StatusType SetRelAlarm ( AlarmType AlarmID, TickRefType increment, TickType cycle );

/* The system service occupies the alarm <AlarmID> element. 
    When <start> ticks are reached, the task assigned to the alarm
    <AlarmID> is activated or the assigned event (only for extended 
    tasks) is set or the alarm-callback routine is called. */
StatusType SetAbsAlarm ( AlarmType AlarmID, TickRefType start, TickType cycle );

/* The system service cancels the alarm <AlarmID>. */
StatusType CancelAlarm ( AlarmType AlarmID );

/*******************************************************************************
 *                      Resource API Prototypes                                *
 *******************************************************************************/
/*
 * This call serves to enter critical sections in the code that are 
 * assigned to the resource referenced by <ResID>. A critical 
 * section shall always be left using ReleaseResource
 */
StatusType GetResource ( ResourceType ResID );

/*
 * ReleaseResource is the counterpart of GetResource and 
 * serves to leave critical sections in the code that are assigned to 
 * the resource referenced by <ResID>
 */
StatusType ReleaseResource ( ResourceType ResID );


/*******************************************************************************
 *                      Interrupt API Prototypes                                *
 *******************************************************************************/

/*
 * This service disables all interrupts for which the hardware
 * supports disabling. The state before is saved for the
 * EnableAllInterrupts call.
 */
void DisableAllInterrupts(void);

/*
 * This service restores the state saved by DisableAllInterrupts.
 */
void EnableAllInterrupts(void);

/*
 * This service saves the recognition status of all interrupts and
 * disables all interrupts for which the hardware supports
 * disabling.
 */
void SuspendAllInterrupts(void);

/*
 * This service restores the recognition status of all interrupts
 * saved by the SuspendAllInterrupts service.
 */
void ResumeAllInterrupts(void);

/*
 * This service saves the recognition status of interrupts of
 * category 2 and disables the recognition of these interrupts.
 */
void SuspendOSInterrupts(void);

/*
 * This service restores the recognition status of interrupts saved
 * by the SuspendOSInterrupts service.
 */
void ResumeOSInterrupts(void);


#endif /* OS_H */
