 /******************************************************************************
 *
 * Module: Alarm
 *
 * File Name: Alarm.h
 *
 * Description: Header file for Alarm management 
 *
 * Author:
 ******************************************************************************/

#ifndef ALARM_H
#define ALARM_H

/* General OS definitions */
#include "Os.h"


/************************************************************************************
* Service Name: IncrementCounter
* Service ID[hex]: 
* Sync/Async: 
* Reentrancy: 
* Parameters (in): AlarmID - Reference to alarm 
*                  Increment_value - Value we will be using 
* Parameters (out): minimal increment
* Description: The system service used to increment the counter.
************************************************************************************/
#if OSALARM_NUMBER_OF_ALARMS 
TickType IncrementCounter(AlarmType AlarmID, TickType Increment_value);
#endif

/************************************************************************************
* Service Name: AlarmManagement
* Service ID[hex]: 
* Sync/Async: 
* Reentrancy: 
* Parameters (in): AlarmID - Reference to alarm 
*                  Increment_value - Value we will be using 
* Parameters (out): Rest of increment
* Description: The system service used to increment the alarm.
************************************************************************************/
#if OSALARM_NUMBER_OF_ALARMS
TickType AlarmManagement(AlarmType AlarmID, TickType Increment_value);
#endif


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Alarm and other modules */
//extern const Alarm_ConfigType Alarm_Configuration;

#endif /* ALARM_H */
