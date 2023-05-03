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



/*******************************************************************************
 *                                  includes                                   *
 *******************************************************************************/

#include "Std_Types.h"
#include "Os_Cfg.h"



/*******************************************************************************
 *                                  structures & unions                        *
 *******************************************************************************/

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
 *                                  definitions                                *
 *******************************************************************************/

#define TaskType  uint8 /*delete later by task management team*/



/*******************************************************************************
 *                         Resource definitions                                *
 *******************************************************************************/

/*
 * type of resource which is the input to GetResource & ReleaseResource
 */
typedef uint8 ResourceType ;  //error with typedef

typedef ResourceType* ResourceRefType;  // if needed

/*******************************************************************************
 *                            Event definitions                                *
 *******************************************************************************/

typedef uint32 EventMaskType;
typedef EventMaskType* EventMaskRefType;

typedef uint32 TaskEventsType;  // usage?


/*******************************************************************************
 *                      Alarm Data Types                                        *
 *******************************************************************************/

/* Type definition represents count values in ticks */
typedef unsigned int TickType;

/* Type definition points to the data type TickType */
typedef TickType* TickRefType;

/* Structure for AlarmBaseType for storage of counter characteristics */
typedef struct
{
  /* Maximum possible allowed count value in ticks */
  TickType maxallowedvalue;

  /* Number of ticks required to reach a counter-specific (significant) unit */
  TickType ticksperbase;

  /* Smallest allowed value for the cycle-parameter of SetRelAlarm/SetAbsAlarm (only for systems with extended status) */
  TickType mincycle;

}AlarmBaseType;

/* Type definition points to the data type AlarmBaseType */
typedef AlarmBaseType* AlarmBaseRefType;

/* Type definition represents an alarm object */
typedef unsigned int AlarmType;


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
StatusType SetRelAlarm ( AlarmType AlarmID, TickType increment, TickType cycle );

/* The system service occupies the alarm <AlarmID> element.
    When <start> ticks are reached, the task assigned to the alarm
    <AlarmID> is activated or the assigned event (only for extended
    tasks) is set or the alarm-callback routine is called. */
StatusType SetAbsAlarm ( AlarmType AlarmID, TickType start, TickType cycle );

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
 *                      Event API Prototypes                                *
 *******************************************************************************/

/*
 *This service returns the current state of all event bits of the task
 *<TaskID>, not the events that the task is waiting for.
 *The service may be called from interrupt service routines, task
 *level and some hook routines
 *The current status of the event mask of task <TaskID> is copied
 *to <Event>.
*/
StatusType GetEvent ( TaskType TaskID , EventMaskRefType Event );

/*
 *The state of the calling task is set to waiting, unless at least one
 *of the events specified in <Mask> has already been set.
*/
StatusType WaitEvent ( EventMaskType Mask );

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
