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

/* Alarm Pre-Compile Configuration Header file */
#include "Alarm_cfg.h"

/* Non AUTOSAR files */
#include "Common_Macros.h"


/*******************************************************************************
 *                 Os Counter Configuration                                    *
 *******************************************************************************/

/* Type definition contains counter increment type */
typedef uint32 OsCounterIncrementType;

/* Type definition contains the natural type or unit of the counter */
typedef enum{
		HARDWARE , SOFTWARE
}OsCounterTypeType;


/* Structure specifies the config of counter */
typedef struct
{
  TickType OsCounterMaxAllowedValue;
  TickType OsCounterMinCycle;
  TickType OsCounterTicksPerBase;
  OsCounterTypeType OsCounterType;
  TickType Time;
  //OsSecondsPerTick;

}OsCounter;


/*******************************************************************************
 *                 Os Alarm Configuration                                    *
 *******************************************************************************/

/** Type definition for Alarm State
 **
 ** This type defines the possibly states of one alarm which are:
 ** 0 disable
 ** 1 enable
 **/
typedef enum{
		Disable , Enable
}OsAlarmStateType;

/** Type definition for Alarm Autostart
 **
 ** This type defines the possibly autostarts of one alarm which are:
 ** 0 False
 ** 1 True
 **/
typedef enum{
		False, True
}OsAlarmautostartType;

/* Type definition for Alarm Time */
typedef unsigned int AlarmTimeType;

/*Type definition for Alarm Cycle Time */
typedef uint32 AlarmCycleTimeType;


/** Type definition for Alarm Actions
 **
 ** This type defines the possibly actions of one alarm which are:
 ** 0 activate a task
 ** 1 callback function
 ** 2 increment a counter
 ** 3 set an event
 **/
typedef enum{

  OsAlarmActiveTask,
  OsAlarmCallback,
  OsAlarmIcrementCounter,
  OsAlarmSetEvent

}OsAlarmActionType;

/* Type definition for Alarm callback function */
typedef void (*OsAlarmCallbackType)( void  );

typedef struct{

  TaskType TaskID;
  OsAlarmCallbackType OsAlarmCallbackFunction;
  OsCounter* OsAlarmCounter;
  EventMaskType Event;

}OsAlarmActionInfo;

typedef struct
{
  AlarmTimeType AlarmTime;    //expire time
  AlarmCycleTimeType AlarmCycleTime;
  OsAlarmStateType AlarmState;
  OsCounter* OsAlarmCounterRef;
  OsAlarmActionType OsAction;
  OsAlarmActionInfo OsActionInfo;
  OsAlarmautostartType Alarmautostar;

  
}OsAlarm;

/* Data Structure required for initializing the Alarm */
//typedef struct Alarm_ConfigType
//{
//	OsAlarm Alarms[No_ALARMS];
//} Alarm_ConfigType;

OsAlarm Alarms[OSALARM_NUMBER_OF_ALARMS];
OsCounter Counters[OSALARM_NUMBER_OF_COUNTERS];


TickType IncrementCounter(AlarmType AlarmID, TickType Increment_value);


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Alarm and other modules */
//extern const Alarm_ConfigType Alarm_Configuration;

#endif /* ALARM_H */
