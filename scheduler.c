/******************************************************************************
 *
 * Module: scheduler
 *
 * File Name: scheduler.c
 *
 * Description: Source file for scheduler
 *
 * Author:
 *
 *******************************************************************************/
/*
calling context:

TerminateTask
	OsSched_RunningToSuspended()
	OsSched_reschedule()

WaitEvent
	OsSched_RunningToWaiting()
	OsSched_reschedule()

ReleaseResource
	OsSched_reschedule()

schedule
	OsSched_scheduleInternal()


ActivateTask
	OsSched_SuspendedToReady(taskID);
	OsSched_reschedule()

ChainTask
	OsSched_RunningToSuspended()
	OsSched_SuspendedToReady(taskID)
	OsSched_reschedule()

SetEvent
	OsSched_WaitingToReady(taskID)
	OsSched_reschedule()

*/


#include "scheduler.h"
#define CALL_SWITCH_CONTEXT() __asm volatile( "ecall" ); /* trigger exception to perform context switch */

OsTask_TCBType              		OsTask_TCBs        [OSTASK_NUMBER_OF_TASKS]; /* TCB array for tasks based on task ID */
STATIC Os_ReadyListType             OsTask_ReadyList           [OSTASK_PRIORITY_LEVELS]; /* array of ready lists based on priority */
STATIC TaskType                     OsTask_RunningTaskID;                         /* currently running task */
STATIC TaskType						OsTask_HighestBasePriority;		        	 /* the highest priority ready or running */
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	/* if we activate a task that has priority higher than the running task */
																		    /* but the running task is non-preemptive ,so store highest priority in this variable  */
OsTask_TCBType * currentTCBPtr ; /* pointer to the TCB of the running task , it is used in context switching to save the context of the current task */
OsTask_TCBType * nextTCBPtr ;    /* pointer to the TCB of the task to be running next , it is used in context switching to restore the context of the next task */
/*******************************************************************************
 *                            static Function Prototypes 		               *
 *******************************************************************************/
STATIC void OsSched_ReadyListAddToHead
(
		Os_ReadyListType* list,
		TaskType 		  taskID
);

STATIC void OsSched_ReadyListAddToTail
(
	 Os_ReadyListType* list,
	 TaskType 	     taskID
);

STATIC void OsSched_ReadyListRemoveFromHead
(
	Os_ReadyListType* list
);

STATIC void OsSched_getHighestReadyTask
(
		TaskType *taskIDPtr
);

/*******************************************************************************
*Function Name: OsSched_schedulerInit
*Parameter (In): none.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: initialize ready list , OsTask_RunningTaskID, OsTask_HighestBasePriority  .
*********************************************************************************/
void OsSched_schedulerInit()
{
	uint8 i;
	OsTask_RunningTaskID=0;
	OsTask_HighestBasePriority=0;
	for(i=0; i<OSTASK_PRIORITY_LEVELS ;i++)
	{
		OsTask_ReadyList[i].head=INVALID_TASK;
		OsTask_ReadyList[i].tail=INVALID_TASK;
	}
}



/*******************************************************************************
*Function Name: OsSched_ReadyListAddToHead
*Parameter (In): list   -ready list to add task to.
*			     taskID	-task to add to list
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: Add task to the given ready list at the head of the list
********************************************************************************/
STATIC void OsSched_ReadyListAddToHead(
										Os_ReadyListType* list,
										TaskType 		  taskID
									   )
{
    OsTask_TCBs[taskID].next = list->head;
    list->head = taskID;
	if (list->tail == INVALID_TASK)
	{
        list->tail = taskID;
    }
	else
	{
		/* Do Nothing */
	}
}

/*******************************************************************************
*Function Name: OsSched_ReadyListRemoveFromHead
*Parameter (In): list  	    -ready list to remove task from.
                 taskID		-task to be added to list
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: Add the task to the tail of the list .
********************************************************************************/
STATIC void OsSched_ReadyListAddToTail(
									   Os_ReadyListType* list,
									   TaskType 	     taskID
									   )
{
    OsTask_TCBs[taskID].next = INVALID_TASK;
    if (list->head == INVALID_TASK)
    {
        list->head = taskID;
    }
    else
    {
        OsTask_TCBs[list->tail].next = taskID;
    }
    list->tail = taskID;
}



/*******************************************************************************
*Function Name: OsSched_ReadyListRemoveFromHead
*Parameter (In): list  	    -ready list to remove task from.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: Remove the task at the head of the list .
********************************************************************************/
STATIC void OsSched_ReadyListRemoveFromHead(
											Os_ReadyListType* list
										   )
{
	TaskType oldHead;

	if(list->head == INVALID_TASK) /* list is already empty */
	{
		/* Do Nothing */
	}
	else if (list->head == list->tail ) /* there is only one task in list */
	{
		list->head = INVALID_TASK;
		list->tail = INVALID_TASK;
		/* Removed task next is already INVALID_TASK */
	}
	else  /* list contains more than one task */
	{
		oldHead=list->head;
		list->head=OsTask_TCBs[oldHead].next;
		OsTask_TCBs[oldHead].next=INVALID_TASK; /* assign Removed task next to INVALID_TASK */
	}
}



/*******************************************************************************
*Function Name: OsSched_RunningToWaiting
*Parameter (In): none
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: move task from running to waiting.
*********************************************************************************/
#if( (OS_CONFORMANCE == OS_CONFORMANCE_ECC1) ||  (OS_CONFORMANCE == OS_CONFORMANCE_ECC2) )
void OsSched_RunningToWaiting(void)
{
	OsTask_TCBs[OsTask_RunningTaskID].state=WAITING;
}
#endif

/*******************************************************************************
*Macro Name: OsSched_RunningToSuspended
*Parameter (In): none
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: move task from running to suspended.
*********************************************************************************/
void OsSched_RunningToSuspended(void)
{
	OsTask_TCBs[OsTask_RunningTaskID].state= SUSPENDED;
}

/*******************************************************************************
*Function Name: OsSched_RunningToReady
*Parameter (In): none.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: change task state from running to ready,
*			  add the task to the head of the ready list.
*********************************************************************************/
/********************OSEK_SCHEDULER_4*******************************************
A preempted task is considered to be the first (oldest) task in the ready 
list of its current priority.
*******************************************************************************/
void OsSched_RunningToReady(void)
{
    OsTask_TCBs[OsTask_RunningTaskID].state = READY;
    OsSched_ReadyListAddToHead(&OsTask_ReadyList[OsTask_TCBs[OsTask_RunningTaskID].CurrentPriority], OsTask_RunningTaskID);
}


/*******************************************************************************
*Macro Name: OsSched_SuspendedToReady
*Parameter (In): taskID		-id of the task to be moved from Suspended to ready.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: change task state from Suspended to ready,
*			  add the task to the tail of the ready list,
*			  update OsTask_HighestBasePriority .
*********************************************************************************/
void OsSched_SuspendedToReady
(
	 TaskType taskID
)
{
/*
 * task release all resources and internal resources before termination (move to suspended state),
 * so its current priority returns to the base priority set at configuration .
 */
#if 0
	OsTaskPriorityType priority;
    priority =OsTask_TCBs[taskID].OsTaskConfig->OsTaskPriority;
    OsTask_TCBs[taskID].CurrentPriority = priority;
#endif
    OsSched_ReadyListAddToTail(&OsTask_ReadyList[OsTask_TCBs[taskID].CurrentPriority], taskID);
    OsTask_TCBs[taskID].state    = READY; /* change state of the task to ready*/

    if(OsTask_TCBs[taskID].CurrentPriority > OsTask_HighestBasePriority)
    {
    	OsTask_HighestBasePriority=OsTask_TCBs[taskID].CurrentPriority;
    }
    else
    {
    	/* Do Nothing */
    }
}

/*******************************************************************************
*Function Name: OsSched_ReadyToRunning
*Parameter (In): taskID		-id of the task to be moved from ready to running.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: change task state from ready to running,
*			  remove the task from the ready list.
*********************************************************************************/
/**********************************OSEK_SCHEDULER_3 ****************************
Tasks on the same priority level are started depending on their order of activation
*******************************************************************************/
void OsSched_ReadyToRunning(
							TaskType taskID
							)
{
    OsSched_ReadyListRemoveFromHead(&OsTask_ReadyList[OsTask_TCBs[taskID].CurrentPriority]);
    OsTask_TCBs[taskID].state = RUNNING;
}


/*******************************************************************************
*Function Name: OsSched_WaitingToReady
*Parameter (In): taskID		-id of the task to be moved from waiting to ready.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: change task state from waiting to ready,
*			  add the task to the tail the ready list,
*			  update OsTask_HighestBasePriority .
*********************************************************************************/
/*************************************OSEK_SCHEDULER_5**************************
A task being released from the waiting state is 
treated like the last (newest) task in the ready queue of its priority
*******************************************************************************/
#if( (OS_CONFORMANCE == OS_CONFORMANCE_ECC1) ||  (OS_CONFORMANCE == OS_CONFORMANCE_ECC2) )
void OsSched_WaitingToReady
(
			TaskType taskID
)
{
	OsTask_TCBs[taskID].state=READY;
	OsSched_ReadyListAddToTail(&OsTask_ReadyList[OsTask_TCBs[taskID].CurrentPriority], taskID);

	if(OsTask_TCBs[taskID].CurrentPriority > OsTask_HighestBasePriority)
	{
		OsTask_HighestBasePriority=OsTask_TCBs[taskID].CurrentPriority;
	}
	else
	{
		/* Do Nothing */
	}
}
#endif


/*******************************************************************************
*Function Name: OsSched_getHighestReadyTask
*Parameter (In): none
*Parameter (Out): taskIDPtr		-pointer to store highest priority task ID.
*Parameter (In/Out): none
*Return : none
*Description: search the ready list to get the highest priority task ID .
*********************************************************************************/
/********************************** OSEK_SCHEDULER_2 ***************************
The value 0 is defined as the lowest priority of a task. Accordingly bigger 
numbers define higher priorities.
***************************************************************************/
STATIC void OsSched_getHighestReadyTask
(
		TaskType *taskIDPtr
)
{
	sint16 i=(sint16)OsTask_HighestBasePriority; /* signed to exit when (i<0) otherwise the condition always true */
	*taskIDPtr=INVALID_TASK;
	for( ; (*taskIDPtr==INVALID_TASK) && (i>=0) ;i--)
	{
		*taskIDPtr =OsTask_ReadyList[i].head;
	}

}


/*******************************************************************************
*Function Name: OsSched_reschedule
*Parameter (In): none
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: get highest priority task and switch context to it  .
*Remark: this function check if the running task is preemptive or NOT before perform switch context.
*********************************************************************************/
/*******************************************************************************
****************OSEK_SCHEDULER_1************************************************
The scheduler decides on the basis of the task 
priority which is the next of the ready tasks to be 
transferred into the running state
***************************************************************************/
void OsSched_reschedule()
{
	TaskType peekTaskID;
	OsSched_getHighestReadyTask(&peekTaskID);
	/*
	 * IF condition is True when
	 * 1.running task state is RUNNING .
	 * because in this case we need to compare the running task priority with the peek priority in ready list .
	 * this sub-condition True in case of ActivateTask, SetEvent and ReleaseResource APIs.
	 * 2.running task state is FULL preemptive .
	 * because ActivateTask, SetEvent and ReleaseResource APIs are rescheduling points only in case of FULL preemptive.
	 *
	 */
	/*********************OSEK_SCHEDULER_6***********************************.
	Full preemptive scheduling will put the running task into the 
 	ready state, as soon as a higher-priority task has got ready.
	*************************************************************************/

	if(OsTask_TCBs[OsTask_RunningTaskID].state==RUNNING)
		/**OSEK_SCHEDULER_10&13&14*/
	{
		if(  (OsTask_TCBs[OsTask_RunningTaskID].OsTaskConfig->OsTaskSchedule==FULL)\
		   &&(OsTask_TCBs[peekTaskID].CurrentPriority > OsTask_TCBs[OsTask_RunningTaskID].CurrentPriority))
		{
			OsSched_RunningToReady();
			OsSched_ReadyToRunning(peekTaskID);
			OsTask_HighestBasePriority=OsTask_TCBs[peekTaskID].CurrentPriority;
			currentTCBPtr=&OsTask_TCBs[OsTask_RunningTaskID];
			nextTCBPtr =&OsTask_TCBs[peekTaskID];
			OsTask_RunningTaskID=peekTaskID;
			OS_SET_CALL_LEVEL(TASK_LEVEL);
			CALL_SWITCH_CONTEXT();
		}
		else
		{
			/* Do Nothing */
		}
	}
	else  /*task state is NOT RUNNING in case of TerminateTask , ChainTask and WaitEvent APIs*/
		/****************************************************OSEK_SCHEDULER_8 &&9&12 *****************/

	{
		OsSched_ReadyToRunning(peekTaskID);
		OsTask_HighestBasePriority=OsTask_TCBs[peekTaskID].CurrentPriority;
		if(OsTask_TCBs[OsTask_RunningTaskID].state==WAITING)
		{
			currentTCBPtr=&OsTask_TCBs[OsTask_RunningTaskID]; /* address of TCB of the task to be saved */
		}
		else
		{
			/* currentTCBPtr = NULL_PTR  to indicate that the task context will NOT be saved */
			currentTCBPtr=NULL_PTR;
		}
		nextTCBPtr =&OsTask_TCBs[peekTaskID];
		OsTask_RunningTaskID=peekTaskID;
		OS_SET_CALL_LEVEL(TASK_LEVEL);
		CALL_SWITCH_CONTEXT();
	}

}


/*******************************************************************************
*Function Name: OsSched_getRunningTaskID
*Parameter (In): none
*Parameter (Out): none
*Parameter (In/Out): none
*Return : OsTask_RunningTaskID   -Running Task ID
*Description: get Running Task ID  .
*********************************************************************************/
TaskType OsSched_getRunningTaskID()
{
	return OsTask_RunningTaskID;
}



/*******************************************************************************
*Function Name: OsSched_scheduleInternal
*Parameter (In): none
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description:this function switch the context to the highest priority task.
*Remark: this function is called only in schedule API.
*********************************************************************************/
/****************OSEK_SCHEDULER_1************************************************
The scheduler decides on the basis of the task 
priority which is the next of the ready tasks to be 
transferred into the running state
***************************************************************************/
void OsSched_scheduleInternal()
{
	TaskType peekTaskID;
	OsSched_getHighestReadyTask(&peekTaskID);

	if(OsTask_TCBs[peekTaskID].CurrentPriority > OsTask_TCBs[OsTask_RunningTaskID].CurrentPriority)
	{
		OsSched_RunningToReady();
		OsSched_ReadyToRunning(peekTaskID);
		OsTask_HighestBasePriority=OsTask_TCBs[peekTaskID].CurrentPriority;
		currentTCBPtr=&OsTask_TCBs[OsTask_RunningTaskID];
		nextTCBPtr =&OsTask_TCBs[peekTaskID];
		OsTask_RunningTaskID=peekTaskID;
		OS_SET_CALL_LEVEL(TASK_LEVEL);
		CALL_SWITCH_CONTEXT();
	}
	else
	{
		/* Do Nothing */
	}
}



/*******************************************************************************
*Function Name: Ossched_StartScheduler
*Parameter (In): none
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: switch context to the highest task in ready list .
*********************************************************************************/
void Ossched_StartScheduler()
{
	TaskType peekTaskID;
	OsSched_getHighestReadyTask(&peekTaskID);

	OsSched_ReadyToRunning(peekTaskID);
	OsTask_HighestBasePriority=OsTask_TCBs[peekTaskID].CurrentPriority;
	currentTCBPtr=NULL_PTR; /* currentTCBPtr = NULL_PTR  to indicate that the task context will NOT be saved */
	nextTCBPtr =&OsTask_TCBs[peekTaskID];
	OsTask_RunningTaskID=peekTaskID;
	CALL_SWITCH_CONTEXT();
}





