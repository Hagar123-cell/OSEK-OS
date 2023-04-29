 /******************************************************************************
 *
 * Module: Alarm
 *
 * File Name: Alarm.h
 *
 * Description: Header file for Alarm management 
 *
 * Author: Yasmin Afifi
 *
 ******************************************************************************/

#ifndef ALARM_H
#define ALARM_H

/* General OS definitions */
#include "Os.h"

/* Alarm Pre-Compile Configuration Header file */
#include "Os_Cfg.h"

/* Non AUTOSAR files */
#include "Common_Macros.h"


/*******************************************************************************
 *                              Module Data Types                              *
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

/* Type definition for os event Reference */
typedef uint16 OsEvent;     //////////////////////
typedef OsEvent* OsEventRefType;

/* Type definition for os task Reference */
typedef uint16 OsTask;     //////////////////////
typedef OsTask* OsTaskRefType;


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
  //OsSecondsPerTick;

}OsCounter;


/* Type definition for os Counter Reference */
typedef OsCounter* OsCounterRefType;

/* Structure specifies the parameters to activate a task */
typedef struct
{
  OsTaskRefType OsAlarmActivateTaskRef;

}OsAlarmActiveTask;


/* Structure specifies the parameters to call a callback OS alarm action */
typedef struct
{

  OsAlarmCallbackName;   //////////////////
 
}OsAlarmCallback;


/* Strcture specifies the parameters to increment a counter */
typedef struct
{
  OsCounterRefType OsAlarmIncrementCounterRef;

}OsAlarmIcrementCounter;

/* Structure specifies the parameters to set an event*/
typedef struct
{

  OsEventRefType OsAlarmSetEventRef;
  OsTaskRefType OsAlarmSetEventTaskRef;


}OsAlarmSetEvent;

/* Structure defines which type of notification is used when the alarm expires */
typedef struct
{
  OsAlarmActiveTask OsActiveTask;
  OsAlarmCallback OsCallback;
  OsAlarmIcrementCounter OsIncrementCounter;
  OsAlarmSetEvent OsSetEvent;

}OsAlarmAction;


typedef struct
{
  OsCounterRefType OsAlarmCounterRef;
  OsAlarmAction OsAction;


  //Alarmautostart

  
}OsAlarm;

/* Data Structure required for initializing the Alarm */
typedef struct Alarm_ConfigType
{
	OsAlarm Alarms[No_ALARMS];
} Alarm_ConfigType;






/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Alarm and other modules */
extern const Alarm_ConfigType Alarm_Configuration;

#endif /* ALARM_H */