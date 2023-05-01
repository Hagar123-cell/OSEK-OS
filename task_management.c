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
StatusType ActivateTask ( TaskType TaskID )
{


	return 0;
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
StatusType TerminateTask ( void )
{


	return 0;
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
StatusType ChainTask ( TaskType TaskID )
{

	return 0;
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
StatusType Schedule ( void )
{

	return 0;
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
StatusType GetTaskID ( TaskRefType TaskID )
{

	return 0;
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
StatusType GetTaskState ( TaskType TaskID, TaskStateRefType State )
{


	return 0;
}