/******************************************************************************
 *
 * Module: TaskManagement
 *
 * File Name: taskManagement.c
 *
 * Description: Source file for TaskManagement
 *
 * Author:
 *
 *******************************************************************************/
#include "task_management.h"
#include "scheduler.h"

#define DISABLE_INTERRUPTS()
#define ENABLE_INTERRUPTS()


#if(OS_EXTENDED_ERROR==TRUE)
volatile OsTask_callLevelType OS_callLevel;
#endif
/************************************************************************************
 *Service Name: ActivateTask
 *Parameter (In):  TaskID 	-Task reference
 *Parameter (Out): none
 *Description: The task <TaskID> is transferred from the suspended state into the ready state.
 *			  The operating system ensures that the task code is being executed from the first statement.
 *Particularities: The service may be called from interrupt level and from task level.
 *				  Rescheduling after the call to ActivateTask depends on the place it is called from (ISR, non preemptable task, preemptable task).
 *				  If E_OS_LIMIT is returned the activation is ignored.
 *				  When an extended task is transferred from suspended state into ready state all its events are cleared.
 *Status:
 *	Standard: • No error, E_OK
 *			  • Too many task activations of <TaskID>, E_OS_LIMIT
 *	Extended: • Task <TaskID> is invalid, E_OS_ID
 *Conformance: BCC1, BCC2, ECC1, ECC2
 ************************************************************************************/
/*@OSEK_TASK_1
The system service StatusType ActivateTask (TaskType TaskID) shall be defined.*/

StatusType ActivateTask ( TaskType TaskID )
{
	StatusType status=E_OK;
	DISABLE_INTERRUPTS();

	/*@OSEK_TASK_6
	In ActivateTask API: If other than E_OK is returned the activation is ignored. */
	/*@OSEK_TASK_9
	In ActivateTask API: Added possible return values in Extended mode is: E_OS_ID if the Task TaskID is invalid. */
#if(OS_EXTENDED_ERROR==TRUE)
	/*check if task id is invalid */
	if(TaskID >= OSTASK_NUMBER_OF_TASKS) /* invalid task id */
	{
		status=E_OS_ID; /*Task <TaskID> is invalid, E_OS_ID */

	}
	else
#endif
	{ /* valid task id */

		OsTask_TCBType * taskTCB=&OsTask_TCBs[TaskID];/* pointer to configuration structure */

		/* check if the task state is NOT suspended */
		if (taskTCB->state != SUSPENDED )
		{
#if ((OS_CONFORMANCE == OS_CONFORMANCE_ECC2) ||  (OS_CONFORMANCE == OS_CONFORMANCE_BCC2))

			if( (taskTCB->OsTaskConfig->taskKind==BASIC) && ( (taskTCB->Activations) < (taskTCB->OsTaskConfig->OsTaskActivation) ) )
			{
				taskTCB->Activations++; /* increase number of activations */
			}
			else /* extended task or basic task exceeded maximum activation*/
			{
				/*@OSEK_TASK_6
				In ActivateTask API: If other than E_OK is returned the activation is ignored. */
				/*@OSEK_TASK_8
				In ActivateTask API: Possible return values in Standard mode are: E_OK if no errors E_OS_LIMIT if too many task activations of TaskID.*/
				status=E_OS_LIMIT; /* Too many task activations of <TaskID>, E_OS_LIMIT */
			}
#else   /*OS_CONFORMANCE_ECC1 ,OS_CONFORMANCE_BCC1 */
			/* if task is activate while it is NOT suspended */
			status=E_OS_LIMIT;/* Too many task activations of <TaskID>, E_OS_LIMIT */



#endif
		}
		else /* task state is Suspended */
		{

			/*@OSEK_TASK_4
			In ActivateTask API: The service may be called from interrupt category 2 level and from task level. */

			/*@OSEK_TASK_2
			In ActivateTask API: The task TaskID shall be transferred from the suspended state into the ready state. */
			OsSched_SuspendedToReady( TaskID);/* change task state and add the task to ready list */
			taskTCB->stackPtr=taskTCB->OsTaskConfig->stackPtr + taskTCB->OsTaskConfig->stackSize; /*set stack pointer to the bottom of stack*/
			/*@OSEK_TASK_3
			In ActivateTask API: The operating system shall ensure that the task code is being executed from the first statement. */
			/* ensures that the task code is being executed from the first statement.*/
			taskTCB->stackPtr=initialiseStack(taskTCB->stackPtr ,taskTCB->OsTaskConfig->entry );

			/*@OSEK_TASK_7
			In ActivateTask API: When an extended task is transferred from suspended state into ready state all its events are cleared.*/
			/* Implemented initialize Events , EventsWait , Resources*/
			taskTCB->Events.OsEventMaskX=0;
			taskTCB->EventsWait.OsEventMaskX=0;
			taskTCB->Resources=0;
			ENABLE_INTERRUPTS();
			if(OS_GET_CALL_LEVEL() ==TASK_LEVEL)
			{
				/*@OSEK_TASK_5
				In ActivateTask API:Rescheduling shall take place only if called from a preemptable task. */
				if(taskTCB->OsTaskConfig->OsTaskSchedule==FULL)
				{
					OS_SET_CALL_LEVEL(SYSTEM_LEVEL);
					OsSched_reschedule(); /* this function may Not return immediately and switch to another task  */
					OS_SET_CALL_LEVEL(TASK_LEVEL);
				}
			}
			else /* if activateTask API is called from ISR cat2 , rescheduling occurs after return from ISR cat2 */
			{
				/* Do Nothing */
			}
		}

	}
	ENABLE_INTERRUPTS();
	return status;
}


/*******************************************************************************
 *Service Name: TerminateTask
 *Parameter (In): none
 *Parameter (Out): none
 *Description: This service causes the termination of the calling task.
 *			  The calling task is transferred from the running state into the suspended state.
 *Particularities: An internal resource assigned to the calling task is automatically released.
 *				  Other resources occupied by the task shall have been released before the call to TerminateTask.
 *				  If a resource is still occupied in standard status the behaviour is undefined.
 *				  If the call was successful, TerminateTask does not return to the call level and the status can not be evaluated.
 *				  If the version with extended status is used, the service returns in case of error, and provides a status which can be evaluated in the application.
 *				  If the service TerminateTask is called successfully, it enforces a rescheduling.
 *				  Ending a task function without call to TerminateTask or ChainTask is strictly forbidden and may leave the system in an undefined state.
 *Status:
 *	Standard: No return to call level
 *	Extended: • Task still occupies resources, E_OS_RESOURCE
 *			  • Call at interrupt level, E_OS_CALLEVEL
 *Conformance: BCC1, BCC2, ECC1, ECC2
 *******************************************************************************/
/*@OSEK_TASK_10
The system service StatusType TerminateTask (void) shall be defined.*/
StatusType TerminateTask ( void )
{
	StatusType status=E_OK;
	DISABLE_INTERRUPTS();
	TaskType runningTaskID=OsSched_getRunningTaskID();
	OsTask_TCBType * taskTCB=&OsTask_TCBs[runningTaskID];/* pointer to TCB structure */

	/*@OSEK_TASK_14
	In TerminateTask API: If the version with extended status is used, the service returns in case of error,
	and provides a status which can be evaluated in the application. */

	/*@OSEK_TASK_16
	In TerminateTask API: This function will never return in Standard mode.*/
#if(OS_EXTENDED_ERROR==TRUE)
	/*@OSEK_TASK_17
	In TerminateTask API: Possibly return values in Extended mode are E_OS_RESOURCE if the Task still occupies resources,
	or E_OS_CALLEVEL if called at interrupt level. */
	if(taskTCB->Resources !=0 ) /*Implemented task occupies resources*/
	{
		status=E_OS_RESOURCE;
	}
	else if(OS_GET_CALL_LEVEL() == ISR2_LEVEL )
	{
		status=E_OS_CALLEVEL;
	}
	else
#endif

	{
#if ((OS_CONFORMANCE == OS_CONFORMANCE_ECC2) ||  (OS_CONFORMANCE == OS_CONFORMANCE_BCC2))
		if((taskTCB->Activations >= 1) && (taskTCB->OsTaskConfig->taskKind==BASIC))
		{
			/*@OSEK_TASK_11
			In TerminateTask API: The calling task shall be transferred from the running state into the suspended state. */
			OsSched_RunningToSuspended();
			OsSched_SuspendedToReady(runningTaskID);
			taskTCB->stackPtr=taskTCB->OsTaskConfig->stackPtr + taskTCB->OsTaskConfig->stackSize; /*set stack pointer to the bottom of stack*/

			/* ensures that the task code is being executed from the first statement.*/
			taskTCB->stackPtr=initialiseStack(taskTCB->stackPtr ,taskTCB->OsTaskConfig->entry );


			/* Implemented initialize Events , EventsWait , Resources*/
			taskTCB->Events.OsEventMaskX=0;
			taskTCB->EventsWait.OsEventMaskX=0;
			taskTCB->Resources=0;
			taskTCB->Activations--;
		}
		else
#endif
		{
			/*@OSEK_TASK_11
			In TerminateTask API: The calling task shall be transferred from the running state into the suspended state. */
			OsSched_RunningToSuspended();
		}
		ENABLE_INTERRUPTS();
		/*OSEK_TASK_13
		In TerminateTask API: If the call was successful, TerminateTask does not return to the call level and the status cannot be evaluated.*/

		/*@OSEK_TASK_15
		In TerminateTask API: If the service TerminateTask is called successfully, it enforces a rescheduling. */
		OS_SET_CALL_LEVEL(SYSTEM_LEVEL);
		OsSched_reschedule();
	}
	ENABLE_INTERRUPTS();
	return status;
}


/*******************************************************************************
 *Service Name: ChainTask
 *Parameter (In): TaskID 	-Reference to the sequential succeeding task to be activated.
 *Parameter (Out): none
 *Description: This service causes the termination of the calling task. After termination of the calling task a succeeding task <TaskID> is activated.
 * 	 	 	 Using this service, it ensures that the succeeding task starts to run at the earliest after the calling task has been terminated.
 *Particularities: If the succeeding task is identical with the current task, this does not result in multiple requests.
 *	 	 	 	 The task is not transferred to the suspended state, but will immediately become ready again.
 *			 	 An internal resource assigned to the calling task is automatically released, even if the succeeding task is identical with the current task.
 *				 Other resources occupied by the calling shall have been released before ChainTask is called.
 *				 If a resource is still occupied in standard status the behaviour is undefined.
 *				 If called successfully, ChainTask does not return to the call level and the status can not be evaluated.
 *				 In case of error the service returns to the calling task and provides a status which can then be evaluated in the application.
 *				 If the service ChainTask is called successfully, this enforces a rescheduling.
 *				 Ending a task function without call to TerminateTask or ChainTask is strictly forbidden and may leave the system in an undefined state.
 *  	   	   	     If E_OS_LIMIT is returned the activation is ignored.
 * 	 	 	 	 When an extended task is transferred from suspended state into ready state all its events are cleared.
 *Status:
 *	Standard: • No return to call level
 *			  • Too many task activations of <TaskID>, E_OS_LIMIT
 *	Extended: • Task <TaskID> is invalid, E_OS_ID
 *		  	  • Calling task still occupies resources, E_OS_RESOURCE
 *		  	  • Call at interrupt level, E_OS_CALLEVEL
 *Conformance: BCC1, BCC2, ECC1, ECC2
 *******************************************************************************/
/*@OSEK_TASK_18
The system service StatusType ChainTask (TaskType TaskID) shall be defined. */
StatusType ChainTask ( TaskType TaskID )
{
	StatusType status=E_OK;
	OsTask_TCBType * taskTCB=&OsTask_TCBs[TaskID];/* pointer to configuration structure */
	DISABLE_INTERRUPTS();


	/*OSEK_TASK_28
	In ChainTask API: Added possible return values in Extended mode are:E_OS_ID if the TaskID is invalid,
	or E_OS_RESOURCE if the calling task still occupies resources, or E_OS_CALLEVEL if call at interrupt level. */

#if(OS_EXTENDED_ERROR==TRUE)
	/*check if task id is invalid */
	if(TaskID >= OSTASK_NUMBER_OF_TASKS) /* invalid task id */
	{
		status=E_OS_ID; /*Task <TaskID> is invalid, E_OS_ID */

	}
	else if (OsTask_TCBs[OsSched_getRunningTaskID()].Resources !=0 )/*Implemented task occupies resources*/
	{
		status=E_OS_RESOURCE;
	}
	else if(OS_GET_CALL_LEVEL() == ISR2_LEVEL)
	{
		status=E_OS_CALLEVEL;
	}
	else
#endif
	{



		/* check if the task state is READY or  WAITING */
		if ((taskTCB->state == READY) || (taskTCB->state == WAITING) )
		{

#if ((OS_CONFORMANCE == OS_CONFORMANCE_ECC2) ||  (OS_CONFORMANCE == OS_CONFORMANCE_BCC2))

			if( (taskTCB->OsTaskConfig->taskKind==BASIC) && ( (taskTCB->Activations) < (taskTCB->OsTaskConfig->OsTaskActivation) ) )
			{
				/*@OSEK_TASK_19
				In ChainTask API: This service causes the termination of the calling task. */
				OsSched_RunningToSuspended(); /* suspended the running task */

				/*@OSEK_TASK_20
				In ChainTask API: After termination of the calling task a succeeding task TaskID shall be activated. */
				taskTCB->Activations++; /* increase number of activations */
				ENABLE_INTERRUPTS();
				OS_SET_CALL_LEVEL(SYSTEM_LEVEL);
				OsSched_reschedule(); /* this function may Not return immediately and switch to another task  */
			}
			else /* extended task or basic task exceeded maximum activation*/
			{
				/*@OSEK_TASK_26
				In ChainTask API: If E_OS_LIMIT is returned the activation is ignored. */
				/*@OSEK_TASK_27
				In ChainTask API: Possible return values in Standard mode are no returns if no errors E_OS_LIMIT
				if too many task activations of TaskID.*/
				status=E_OS_LIMIT; /* Too many task activations of <TaskID>, E_OS_LIMIT */
			}
#else   /*OS_CONFORMANCE_ECC1 ,OS_CONFORMANCE_BCC1 */
			/* if task is activate while it is NOT suspended */
			status=E_OS_LIMIT;/* Too many task activations of <TaskID>, E_OS_LIMIT */



#endif
		}
		else /* task state is SUSPENDED or RUNNING */
		{

			if(taskTCB->state == SUSPENDED)
			{
				/*@OSEK_TASK_19
				In ChainTask API: This service causes the termination of the calling task. */
				OsSched_RunningToSuspended();/* suspended the running task */
			}
			else /* task state is RUNNING , activates itself */
			{
				/* Do Nothing */
			}

			/*@OSEK_TASK_20
			In ChainTask API: After termination of the calling task a succeeding task TaskID shall be activated. */
			/*@OSEK_TASK_21
			In ChainTask API: If the succeeding task is identical with the current task, this does not result in multiple requests.
			The task is not transferred to the suspended state but will immediately become ready again. */
			OsSched_SuspendedToReady( TaskID);/* change task state and add the task to ready list */
			taskTCB->stackPtr=taskTCB->OsTaskConfig->stackPtr + taskTCB->OsTaskConfig->stackSize; /*set stack pointer to the bottom of stack*/

			/* ensures that the task code is being executed from the first statement.*/
			taskTCB->stackPtr=initialiseStack(taskTCB->stackPtr ,taskTCB->OsTaskConfig->entry );

			/*@OSEK_TASK_25
			In ChainTask API: When an extended task is transferred from suspended state into ready state all its events are cleared. */


			/* Implemented initialize Events , EventsWait , Resources*/
			taskTCB->Events.OsEventMaskX=0;
			taskTCB->EventsWait.OsEventMaskX=0;
			taskTCB->Resources=0;
			ENABLE_INTERRUPTS();
			OS_SET_CALL_LEVEL(SYSTEM_LEVEL);

			/*@OSEK_TASK_23
			In ChainTask API: If called successfully, ChainTask does not return to the call level and the status cannot be evaluated. */

			/*@OSEK_TASK_24
			In ChainTask API: If the service ChainTask is called successfully, this enforces a rescheduling. */
			OsSched_reschedule(); /* this function may Not return immediately and switch to another task  */

		}
	}
	ENABLE_INTERRUPTS();
	return status;
}


/*******************************************************************************
 *Service Name: Schedule
 *Parameter (In): none
 *Parameter (Out): none
 *Description: If a higher-priority task is ready, the internal resource of the task is released, the current task is put into the ready state,
 * 	 	 	 its context is saved and the higher-priority task is executed. Otherwise the calling task is continued.
 *Particularities: Rescheduling only takes place if the task an internal resource is assigned to the calling task16 during system generation.
 * 	 	 	 	 For these tasks, Schedule enables a processor assignment to other tasks with lower or equal priority
 * 	 	 	 	 than the ceiling priority of the internal resource and higher priority than the priority of the calling task
 * 	 	 	 	 in application-specific locations. When returning from Schedule, the internal resource has been taken again.
 *				 This service has no influence on tasks with no internal resource assigned (preemptable tasks).
 *Status:
 *	Standard: • No error, E_OK
 *	Extended: • Call at interrupt level, E_OS_CALLEVEL
 *			  • Calling task occupies resources, E_OS_RESOURCE
 *Conformance: BCC1, BCC2, ECC1, ECC2
 *******************************************************************************/
/*@OSEK_TASK_29
The system service StatusType Schedule (void) shall be defined.*/
StatusType Schedule ( void )
{
	/*@OSEK_TASK_32
	In Schedule API: Possible return values in Standard mode is E_OK */
	StatusType status=E_OK;
	DISABLE_INTERRUPTS();

	/*@OSEK_TASK_33
	In Schedule API: Extra possible return values in Extended mode are:
	E_OS_CALLEVEL if call at interrupt level, or
	E_OS_RESOURCE if the calling task occupies resources.*/
#if(OS_EXTENDED_ERROR==TRUE)
	if(OsTask_TCBs[OsSched_getRunningTaskID()].Resources !=0 ) /*Implemented task occupies resources*/
	{
		status=E_OS_RESOURCE;
	}
	else if(OS_GET_CALL_LEVEL() == ISR2_LEVEL)
	{
		status=E_OS_CALLEVEL;
	}
	else
#endif
	{
		ENABLE_INTERRUPTS();
		OS_SET_CALL_LEVEL(SYSTEM_LEVEL);

		/*@OSEK_TASK_31
		In Schedule API: the current task is put into the ready state, its context is saved and the higher-priority task is executed.
		Otherwise, the calling task is continued. */
		OsSched_scheduleInternal();
		OS_SET_CALL_LEVEL(TASK_LEVEL);
	}
	ENABLE_INTERRUPTS();

	return status;
}

/*******************************************************************************
 *Service Name: GetTaskID
 *Parameter (In): none
 *Parameter (Out): TaskID	 -Reference to the task which is currently running
 *Description: GetTaskID returns the information about the TaskID of the task which is currently running.
 *Particularities: Allowed on task level, ISR level and in several hook routines.
 *				  This service is intended to be used by library functions and hook routines.
 *				  If <TaskID> can’t be evaluated (no task currently running), the service returns INVALID_TASK as TaskType.
 *Status:
 *	Standard: • No error, E_OK
 *	Extended: • No error, E_OK
 *Conformance: BCC1, BCC2, ECC1, ECC2
 *******************************************************************************/
/*@OSEK_TASK_34
The system service StatusType GetTaskID (TaskRefType TaskID) shall be defined. */
StatusType GetTaskID ( TaskRefType TaskID )
{
	DISABLE_INTERRUPTS();
	TaskType runningTaskID = OsSched_getRunningTaskID();

	if (OsTask_TCBs[runningTaskID].state == RUNNING)
	{
		/*@OSEK_TASK_35
		In GetTaskID API: Shall returns the information about the TaskID of the task which is currently running. */
		*TaskID = runningTaskID;
	}
	else
	{
		/*@OSEK_TASK_36
		In GetTaskID API: If no task is currently running, the service returns INVALID_TASK as TaskType.*/
		*TaskID = INVALID_TASK;
	}
	ENABLE_INTERRUPTS();
	/*@OSEK_TASK_37
	In GetTaskID API: This function always returns E_OK. */
	return E_OK;
}

/*******************************************************************************
 *Service Name: GetTaskState
 *Syntax: StatusType GetTaskState ( TaskType <TaskID>, TaskStateRefType <State> )
 *Parameter (In): TaskID 	-Task reference
 *Parameter (Out): State 	-Reference to the state of the task <TaskID>
 *Description: Returns the state of a task (running, ready, waiting, suspended) at the time of calling GetTaskState.
 *Particularities: The service may be called from interrupt service routines, task level, and some hook routines.
 *				  When a call is made from a task in a full preemptive system, the result may already be incorrect at the time of evaluation.
 *				  When the service is called for a task, which is activated more than once,
 *				  the state is set to running if any instance of the task is running.
 *Status:
 *	Standard: • No error, E_OK
 *	Extended: • Task <TaskID> is invalid, E_OS_ID
 *Conformance: BCC1, BCC2, ECC1, ECC2
 *******************************************************************************/
/*@OSEK_TASK_38
The system service StatusType GetTaskState (TaskType TaskID, TaskStateRefType State) shall be defined. */
StatusType GetTaskState ( TaskType TaskID, TaskStateRefType State )
{
	StatusType status=E_OK;
	DISABLE_INTERRUPTS();
	/*@OSEK_TASK_41
	In GetTaskState API: Possible return values in Standard mode is E_OK*/
	/*@OSEK_TASK_42
	In GetTaskState API: Extra possible return values in Extended mode is E_OS_ID if the Task TaskID is invalid. */
#if(OS_EXTENDED_ERROR==TRUE)
	/*check if task id is invalid */
	if(TaskID >= OSTASK_NUMBER_OF_TASKS) /* invalid task id */
	{
		status=E_OS_ID; /*Task <TaskID> is invalid, E_OS_ID */
	}
	else
#endif
	{
		/*@OSEK_TASK_39
		In GetTaskState API: The service shall return the state of a task (running, ready, waiting, suspended)
		at the time of calling GetTaskState. */
		/*@OSEK_TASK_40
		In GetTaskState API: When the service is called for a task, which is activated more than once,
		the state is set to running if any instance of the task is running.*/
		*State =OsTask_TCBs[TaskID].state;
	}
	ENABLE_INTERRUPTS();
	return status;
}


/*******************************************************************************
 *Function Name: OsTask_taskInit
 *Parameter (In): none
 *Parameter (Out): none
 *Parameter (In/Out): none
 *Return : none
 *Description: initialize tasks TCB and ready list . move autostart task to ready list .
 *********************************************************************************/
void OsTask_taskInit()
{
	uint8 i;
	OS_SET_CALL_LEVEL(TASK_LEVEL);


	for(i=0; i < OSTASK_NUMBER_OF_TASKS;i++)
	{

		OsTask_TCBs[i].OsTaskConfig= &Task_Configuration.tasksConfig[i];

		/* OsTask_TCBs[i].next=INVALID_TASK;  initialized in OsSched_ReadyListAddToTail*/
		OsTask_TCBs[i].Activations=0;
		OsTask_TCBs[i].CurrentPriority=Task_Configuration.tasksConfig[i].OsTaskPriority;


		/*if(OsTaskConfig[i].OsTaskAutostart.OsTaskAppModeRef->appMode & OSAPPMODE_CURRENT_APPMODE)*/

		if(Task_Configuration.tasksConfig[i].OsTaskAutostart==TRUE)
		{
			OsTask_TCBs[i].state=READY;
			OsSched_SuspendedToReady(i);
			/* point to stack top*/
			OsTask_TCBs[i].stackPtr=Task_Configuration.tasksConfig[i].stackPtr + Task_Configuration.tasksConfig[i].stackSize;

			/* ensures that the task code is being executed from the first statement.*/
			OsTask_TCBs[i].stackPtr=initialiseStack(OsTask_TCBs[i].stackPtr ,Task_Configuration.tasksConfig[i].entry );

			/*Implemented initialize Events , EventsWait , Resources*/
			OsTask_TCBs[i].Events.OsEventMaskX=0;
			OsTask_TCBs[i].EventsWait.OsEventMaskX=0;
			OsTask_TCBs[i].Resources=0;

		}
		else
		{
			OsTask_TCBs[i].state=SUSPENDED;
		}
	}
}


