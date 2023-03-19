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

/* Standard AUTOSAR types */
#include "Std_Types.h"

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


/* Structure specifies the config of counter */
typedef struct
{


}OsCounter;

/* Structure specifies the parameters to activate a task */
typedef struct
{
  OsTask    *OsAlarmActivateTaskRef;

}AlarmActiveTask;


/* Structure specifies the parameters to call a callback OS alarm action */
typedef struct
{

  OsAlarmCallbackName   //////////////////
 
}AlarmCallback;


/* Strcture specifies the parameters to increment a counter */
typedef struct
{
  OsCounter   *OsAlarmIncrementCounterRef;

}AlarmIcrementCounter;

/* Structure specifies the parameters to set an event*/
typedef struct
{

  OsEvent   *OsAlarmSetEventRef;

  OsTask    *OsAlarmSetEventTaskRef;


}AlarmSetEvent;

/* Structure defines which type of notification is used when the alarm expires */
typedef struct
{
  AlarmActiveTask ActiveTask;

  AlarmCallback Callback;

  AlarmIcrementCounter IncrementCounter;

  AlarmSetEvent SetEvent;

}AlarmAction;



//implement config struct if found 

typedef struct
{
  OsCounter  *AlarmCounterRef;
  
  AlarmAction Action;


  //Alarmautostart

  
}Alarm_ConfigChannel;

/* Data Structure required for initializing the Alarm */
typedef struct Alarm_ConfigType
{
	Alarm_ConfigChannel Alarms[No_ALARMS];
} Alarm_ConfigType;






/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Alarm and other modules */
extern const Alarm_ConfigType Alarm_Configuration;

#endif /* ALARM_H */