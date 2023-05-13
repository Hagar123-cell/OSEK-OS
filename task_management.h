/******************************************************************************
 *
 * Module: TaskManagement
 *
 * File Name: taskManagement.h
 *
 * Description: Header file for TaskManagement
 *
 * Author:
 *
 *******************************************************************************/


#ifndef TASK_MANAGEMENT_H_
#define TASK_MANAGEMENT_H_
#include "Os.h"
#include "scheduler.h"


/*******************************************************************************
 *                              App Mode Start			                       *
 *******************************************************************************/
#define OSDEFAULTAPPMODE  1

typedef uint16 AppModeType ;
typedef struct {
	AppModeType appMode; /* support 16 App Mode ,each bit refer to an App mode */
}OsAppMode;
/*******************************************************************************
 *                              App Mode End			                       *
 *******************************************************************************/

#define INVALID_TASK OSTASK_NUMBER_OF_TASKS

/*******************************************************************************
 *                               Types from os event 		                    *
 *******************************************************************************/
typedef uint16 OsEvent; /* delete later */
typedef OsEvent* OsEventRefType;



/*******************************************************************************
 *                               Types from os resource                        *
 *******************************************************************************/
/*typedef uint16 OsResource;*/  /* delete later */
typedef OsResource* OsResourceRefType;


/*******************************************************************************
 *                              Module Data Types   	                       *
 *******************************************************************************/
/* in OS SWS */
typedef uint8 OsTaskActivationType;
typedef uint8 OsTaskPriorityType;
typedef void (*OsTask_EntryType)(void);
typedef void* OsTask_stackType;
typedef uint16 OsTask_stackSizeType;





/* in OSEK Specification */

/*This data type identifies a task.*/
typedef uint8 TaskType;

/*This data type points to a variable of TaskType. */
typedef TaskType* TaskRefType;

/*This data type identifies the state of a task.*/
typedef enum{
	READY=0,
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
 *                             		 Enums				  	                   *
 *******************************************************************************/
typedef enum{
	FULL , NON
}OsTaskScheduleType;

enum
{
	OS_CONFORMANCE_BCC1,
	OS_CONFORMANCE_ECC1,
	OS_CONFORMANCE_BCC2,
	OS_CONFORMANCE_ECC2
};
typedef enum
{
	BASIC ,
	EXTENDED
}OsTask_taskKindType;


typedef enum
{
	TASK_LEVEL, /* set calling level to TASK_LEVEL , before switch context and after calling scheduler in some cases */
	SYSTEM_LEVEL, /* set calling level to SYSTEM_LEVEL , before calling scheduler  */
	ISR2_LEVEL
}OsTask_callLevelType;


/* Task Management Pre-Compile Configuration Header file */
#include "task_management_cfg.h"

/*******************************************************************************
 *                              Externs			  	                       *
 *******************************************************************************/
#if(OS_EXTENDED_ERROR==TRUE)
extern volatile OsTask_callLevelType OS_callLevel;
#endif


/*******************************************************************************
 *                              Structures			  	                       *
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
	OsResourceRefType OsTaskResourceRef;

	struct {
		OsAppMode* OsTaskAppModeRef;
	}OsTaskAutostart;
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
	OsTask * OsTaskConfig;
}OsTask_TCBType;

typedef struct Os_ReadyListType {
	TaskType head;             /* pointer to the first ready task */
	TaskType tail;             /* pointer to the last ready task */
} Os_ReadyListType;

/*******************************************************************************
 *                            	Function-Like Macro				               *
 *******************************************************************************/
#if(OS_EXTENDED_ERROR==TRUE)
/* change the calling level */
#define OS_SET_CALL_LEVEL(callLevel) OS_callLevel=(callLevel)
/* return the calling level*/
#define OS_GET_CALL_LEVEL() OS_callLevel
#endif
/*******************************************************************************
 *                            Constructional elements			               *
 *******************************************************************************/

/*  Definition of the  DeclareTask Macro */
#define DeclareTask(TaskIdentifier) void Task ## TaskIdentifier (void)


/*******************************************************************************
 *                      System services	                                       *
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
StatusType ActivateTask ( TaskType TaskID );


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
StatusType TerminateTask ( void );


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
StatusType ChainTask ( TaskType TaskID );


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
StatusType Schedule ( void );

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
StatusType GetTaskID ( TaskRefType TaskID );

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
StatusType GetTaskState ( TaskType TaskID, TaskStateRefType State );


/*******************************************************************************
 *Function Name: OsTask_taskInit
 *Parameter (In): OsTaskConfig	 - pointer to the first element of static configuration array.
 *Parameter (Out): none
 *Parameter (In/Out): none
 *Return : none
 *Description: initialize tasks TCB and ready list . move autostart task to ready list .
 *********************************************************************************/
void OsTask_taskInit(OsTask * OsTaskConfig);

/*******************************************************************************
 *Function Name: initialiseStack
 *Syntax : OsTask_stackType initialiseStack( OsTask_stackType stackTop , OsTask_EntryType entry)
 *Parameter (In): stackTop    -pointer to stack top.
 *                entry       -pointer to task entry
 *Parameter (Out): none
 *Parameter (In/Out): none
 *Return : pointer to top of context .
 *Description: initialize stack context .
 *             store entry into stack , to ensures that the task code is being executed from the first statement.
 *             setup and store mstatus into stack .
 *Remark: it is implemented in assembly in riscv_context_switching.S file.
 *********************************************************************************/
OsTask_stackType initialiseStack( OsTask_stackType stackTop , OsTask_EntryType entry);

#endif /* TASK_MANAGEMENT_H_ */
