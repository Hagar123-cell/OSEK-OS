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

/*
 *  This data type is used for all status information the API services offer
 */
typedef uint8  StatusType;

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



#endif /* OS_H */
