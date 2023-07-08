#include "Os.h"
#include "Os_PBcfg.h"

uint32 task1Stack [STACKSIZE];
uint32 task2Stack [STACKSIZE];



const Task_ConfigType Task_Configuration = {
     task1Stack,STACKSIZE,Task1,EXTENDED,0,1,FULL,0,TRUE,
	 task2Stack,STACKSIZE,Task2,EXTENDED,0,2,FULL,0,FALSE
};


typedef struct Counter_ConfigType
{
	OsCounter Counters[OSALARM_NUMBER_OF_COUNTERS];
} Counter_ConfigType;

const Counter_ConfigType Counter_Configuration = {
	{OS_COUNTER_MAX_ALLOWED_VALUE_1, OS_COUNTER_MIN_CYCLE_1, OS_COUNTER_TICKS_PER_BASE_1, SOFTWARE, 0},
	{OS_COUNTER_MAX_ALLOWED_VALUE_1, OS_COUNTER_MIN_CYCLE_1, OS_COUNTER_TICKS_PER_BASE_1, SOFTWARE, 0}
   
};

typedef struct Alarm_ConfigType
{
	OsAlarm Alarms[OSALARM_NUMBER_OF_ALARMS];
} Alarm_ConfigType;

const Alarm_ConfigType Alarm_Configuration = {
	{0,667 ,Disable, &Counter_Configuration, OsAlarmActiveTask, {Task1, NULL_PTR, &Counter_Configuration, 0}, False},
	{0,667 , Disable, &Counter_Configuration+1, OsAlarmActiveTask, {Task2, NULL_PTR, &Counter_Configuration+1, 0}, False}
   
};

