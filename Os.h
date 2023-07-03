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
  *                                 init Prototypes                            *
  *******************************************************************************/
/* Description: The system service used to initialize the alarm. */
#if OSALARM_NUMBER_OF_ALARMS 
void Alarm_init(void);
#endif

/*******************************************************************************
*Function Name: OsSched_schedulerInit
*Parameter (In): none.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: initialize ready list , OsTask_RunningTaskID, OsTask_HighestBasePriority  .
*********************************************************************************/
void OsSched_schedulerInit();

/*******************************************************************************
 *Function Name: OsTask_taskInit
 *Parameter (In): none
 *Parameter (Out): none
 *Parameter (In/Out): none
 *Return : none
 *Description: initialize tasks TCB and ready list . move autostart task to ready list .
 *********************************************************************************/
void OsTask_taskInit();

/* Description: The system service used to initialize the interrupts. */
void Interrupt_init(void);


  /*******************************************************************************
   *                                  structures & unions                        *
   *******************************************************************************/

   /*
	*  This data type is used for all status information the API services offer
	*/
typedef enum {
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


/*This data type identifies a task.*/
typedef uint8 TaskType;

/*******************************************************************************
 *                         Resource definitions                                *
 *******************************************************************************/
enum
{
	OS_CONFORMANCE_BCC1,
	OS_CONFORMANCE_ECC1,
	OS_CONFORMANCE_BCC2,
	OS_CONFORMANCE_ECC2
};

/* OS Pre-Compile Configuration Header file */
#include "Os_Cfg.h"
/*
 * type of resource which is the input to GetResource & ReleaseResource
 */
typedef uint8 ResourceType ;

/* define a type to instantiate the variable resources from */
typedef  uint8 OsResource;

/* struct to store the tasks that use each resource */
typedef struct
{
	TaskType using_tasks [Resources_count][OSTASK_NUMBER_OF_TASKS];
}get_using_tasks;


/* Description: The system service used to initialize the resources. */
void Resource_init(get_using_tasks x );
/*******************************************************************************
 *                            Event definitions                                *
 *******************************************************************************/
typedef uint32 OsEventMask;

typedef OsEventMask EventMaskType;

/* define a type to instantiate the mask from */
typedef EventMaskType* EventMaskRefType;

typedef uint32 TaskEventsType;  


typedef struct
{
	OsEventMask OsEventMaskX; //1 -> represent events that the task is interested in
}OsEvent;

typedef OsEvent* OsEventRefType;




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
StatusType GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info);

/* The system service GetAlarm returns the relative value in ticks
	before the alarm <AlarmID> expires. */
StatusType GetAlarm(AlarmType AlarmID, TickRefType Tick);

/* The system service occupies the alarm <AlarmID> element.
	After <increment> ticks have elapsed, the task assigned to the
	alarm <AlarmID> is activated or the assigned event (only for
	extended tasks) is set or the alarm-callback routine is called. */
StatusType SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle);

/* The system service occupies the alarm <AlarmID> element.
	When <start> ticks are reached, the task assigned to the alarm
	<AlarmID> is activated or the assigned event (only for extended
	tasks) is set or the alarm-callback routine is called. */
StatusType SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle);

/* The system service cancels the alarm <AlarmID>. */
StatusType CancelAlarm(AlarmType AlarmID);


/*******************************************************************************
 *                 Os Counter Configuration                                    *
 *******************************************************************************/

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
  //uint8	AlarmsCount;
  //AlarmType* AlarmRef;

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

/* Type definition for Alarm Struct */
typedef struct
{
  AlarmTimeType AlarmTime;    //expire time
  AlarmCycleTimeType AlarmCycleTime;
  OsAlarmStateType AlarmState;
  OsCounter* OsAlarmCounterRef;
  OsAlarmActionType OsAction;
  OsAlarmActionInfo* OsActionInfo;
  OsAlarmautostartType Alarmautostart;

  
}OsAlarm;

/* Data Structure required for initializing the Alarm */
//typedef struct Alarm_ConfigType
//{
//	OsAlarm Alarms[No_ALARMS];
//} Alarm_ConfigType;

OsAlarm Alarms[OSALARM_NUMBER_OF_ALARMS];
OsCounter Counters[OSALARM_NUMBER_OF_COUNTERS];

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

/*
 *The events of the extended task calling ClearEvent are cleared 
 *according to the event mask <Mask>
*/
StatusType ClearEvent ( EventMaskType Mask );

/*
 *The events of task <TaskID> are set according to the event 
 *mask <Mask>. Calling SetEvent causes the task <TaskID> to 
 *be transferred to the ready state, if it was waiting for at least 
 *one of the events specified in <Mask>.
*/
StatusType SetEvent ( TaskType TaskID ,EventMaskType Mask );


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





/*******************************************************************************
 *                              App Mode Start			                       *
 *******************************************************************************/

typedef uint16 AppModeType;
typedef struct {
	AppModeType appMode; /* support 16 App Mode ,each bit refer to an App mode */
}OsAppMode;
/*******************************************************************************
 *                              App Mode End			                       *
 *******************************************************************************/


typedef OsEvent* OsEventRefType;

/*******************************************************************************
  *                                 OS Prototypes                              *
  *******************************************************************************/

void StartOS(AppModeType);

void ShutdownOS(StatusType);


/*******************************************************************************
 *                          Task Management Data Types   	                   *
 *******************************************************************************/
 /* in OS SWS */
typedef uint8 OsTaskActivationType;
typedef uint8 OsTaskAutostartType;  /* TRUE or FALSE */
typedef uint8 OsTaskPriorityType;
typedef void (*OsTask_EntryType)(void);
typedef void* OsTask_stackType;
typedef uint16 OsTask_stackSizeType;



/* in OSEK Specification */



/*This data type points to a variable of TaskType. */
typedef TaskType* TaskRefType;

/*This data type identifies the state of a task.*/
typedef enum {
	READY = 0,
#if( (OS_CONFORMANCE == OS_CONFORMANCE_ECC1) ||  (OS_CONFORMANCE == OS_CONFORMANCE_ECC2) )
	WAITING,
#endif
	RUNNING,
	SUSPENDED,
	INVALID_STATE
}TaskStateType;


/*This data type points to a variable of the data type TaskStateType. */
typedef TaskStateType* TaskStateRefType;

/*******************************************************************************
 *                             Task Management Enums	                       *
 *******************************************************************************/
typedef enum {
	FULL, NON
}OsTaskScheduleType;


typedef enum
{
	BASIC,
	EXTENDED
}OsTask_taskKindType;


typedef enum
{
	TASK_LEVEL, /* set calling level to TASK_LEVEL , before switch context and after calling scheduler in some cases */
	SYSTEM_LEVEL, /* set calling level to SYSTEM_LEVEL , before calling scheduler  */
	ISR2_LEVEL
}OsTask_callLevelType;


/*******************************************************************************
 *                             Task Management Externs			               *
 *******************************************************************************/
#if(OS_EXTENDED_ERROR==TRUE)
extern volatile OsTask_callLevelType OS_callLevel;
#endif


/*******************************************************************************
 *                          Task Management Function-Like Macro	               *
 *******************************************************************************/
#if(OS_EXTENDED_ERROR==TRUE)
 /* change the calling level */
#define OS_SET_CALL_LEVEL(callLevel) OS_callLevel=(callLevel)
/* return the calling level*/
#define OS_GET_CALL_LEVEL() OS_callLevel
#endif

/*******************************************************************************
 *                             Task Management Structures	                   *
 *******************************************************************************/


typedef struct {
	OsTask_stackType stackPtr; /* fixed stack pointer */
	OsTask_stackSizeType stackSize; /* stack size of the task in bytes */
	OsTask_EntryType entry; /* address of the entry point of the task */
	OsTask_taskKindType taskKind;  /* BASIC or EXTENDED */
#if( (OS_CONFORMANCE == OS_CONFORMANCE_ECC2) ||  (OS_CONFORMANCE == OS_CONFORMANCE_BCC2) )
	OsTaskActivationType OsTaskActivation;
#endif
	OsTaskPriorityType OsTaskPriority;
	OsTaskScheduleType OsTaskSchedule;
	/*  OsTaskAccessingApplication */     /*Reference to applications which have an access to this object.*/
#if( (OS_CONFORMANCE == OS_CONFORMANCE_ECC1) ||  (OS_CONFORMANCE == OS_CONFORMANCE_ECC2) )
	OsEventRefType  OsTaskEventRef;
#endif


	OsTaskAutostartType OsTaskAutostart;
	/*OsTaskTimingProtection */			  /*This container contains all parameters regarding timing protection of the task.*/
}OsTask;


typedef struct {
	OsTask_stackType stackPtr; /* current top of stack pointer , changes during run time  */
	TaskStateType state;
	OsTaskPriorityType CurrentPriority;
#if( (OS_CONFORMANCE == OS_CONFORMANCE_ECC2) ||  (OS_CONFORMANCE == OS_CONFORMANCE_BCC2) )
	OsTaskActivationType Activations;
#endif
#if( (OS_CONFORMANCE == OS_CONFORMANCE_ECC1) ||  (OS_CONFORMANCE == OS_CONFORMANCE_ECC2) )
	OsEvent Events;
	OsEvent EventsWait;
#endif
	OsResource Resources;
	TaskType next;
	OsTask* OsTaskConfig;
}OsTask_TCBType;




/*******************************************************************************
 *                       Task Management Constructional elements               *
 *******************************************************************************/

 /*  Definition of the  DeclareTask Macro */
#define DeclareTask(TaskIdentifier) void Task ## TaskIdentifier (void)




/*******************************************************************************
 *                     Task Management System services	                       *
 *******************************************************************************/

 /************************************************************************************
  *Service Name: ActivateTask
  *Parameter (In):  TaskID 	-Task reference
  *Parameter (Out): none
  *Description: The task <TaskID> is transferred from the suspended state into the ready state.
  *			  The operating system ensures that the task code is being executed from the first statement.
  *Status:
  *	Standard: • No error, E_OK
  *			  • Too many task activations of <TaskID>, E_OS_LIMIT
  *	Extended: • Task <TaskID> is invalid, E_OS_ID
  *Conformance: BCC1, BCC2, ECC1, ECC2
  ************************************************************************************/
StatusType ActivateTask(TaskType TaskID);


/*******************************************************************************
 *Service Name: TerminateTask
 *Parameter (In): none
 *Parameter (Out): none
 *Description: This service causes the termination of the calling task.
 *			  The calling task is transferred from the running state into the suspended state.
 *Status:
 *	Standard: No return to call level
 *	Extended: • Task still occupies resources, E_OS_RESOURCE
 *			  • Call at interrupt level, E_OS_CALLEVEL
 *Conformance: BCC1, BCC2, ECC1, ECC2
 *******************************************************************************/
StatusType TerminateTask(void);


/*******************************************************************************
 *Service Name: ChainTask
 *Parameter (In): TaskID 	-Reference to the sequential succeeding task to be activated.
 *Parameter (Out): none
 *Description: This service causes the termination of the calling task. After termination of the calling task a succeeding task <TaskID> is activated.
 * 	 	 	 Using this service, it ensures that the succeeding task starts to run at the earliest after the calling task has been terminated.
 *Status:
 *	Standard: • No return to call level
 *			  • Too many task activations of <TaskID>, E_OS_LIMIT
 *	Extended: • Task <TaskID> is invalid, E_OS_ID
 *		  	  • Calling task still occupies resources, E_OS_RESOURCE
 *		  	  • Call at interrupt level, E_OS_CALLEVEL
 *Conformance: BCC1, BCC2, ECC1, ECC2
 *******************************************************************************/
StatusType ChainTask(TaskType TaskID);


/*******************************************************************************
 *Service Name: Schedule
 *Parameter (In): none
 *Parameter (Out): none
 *Description: If a higher-priority task is ready, the internal resource of the task is released, the current task is put into the ready state,
 * 	 	 	 its context is saved and the higher-priority task is executed. Otherwise the calling task is continued.
 *Status:
 *	Standard: • No error, E_OK
 *	Extended: • Call at interrupt level, E_OS_CALLEVEL
 *			  • Calling task occupies resources, E_OS_RESOURCE
 *Conformance: BCC1, BCC2, ECC1, ECC2
 *******************************************************************************/
StatusType Schedule(void);

/*******************************************************************************
 *Service Name: GetTaskID
 *Parameter (In): none
 *Parameter (Out): TaskID	 -Reference to the task which is currently running
 *Description: GetTaskID returns the information about the TaskID of the task which is currently running.
 *Status:
 *	Standard: • No error, E_OK
 *	Extended: • No error, E_OK
 *Conformance: BCC1, BCC2, ECC1, ECC2
 *******************************************************************************/
StatusType GetTaskID(TaskRefType TaskID);

/*******************************************************************************
 *Service Name: GetTaskState
 *Syntax: StatusType GetTaskState ( TaskType <TaskID>, TaskStateRefType <State> )
 *Parameter (In): TaskID 	-Task reference
 *Parameter (Out): State 	-Reference to the state of the task <TaskID>
 *Description: Returns the state of a task (running, ready, waiting, suspended) at the time of calling GetTaskState.
 *Status:
 *	Standard: • No error, E_OK
 *	Extended: • Task <TaskID> is invalid, E_OS_ID
 *Conformance: BCC1, BCC2, ECC1, ECC2
 *******************************************************************************/
StatusType GetTaskState(TaskType TaskID, TaskStateRefType State);


/*******************************************************************************
 *                       External Configurations                                    *
 *******************************************************************************/
extern OsTask * OsTaskConfig;

#endif /* OS_H */
