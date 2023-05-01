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

#include "scheduler.h"
OsTask_TCBType              		OsTask_TCBs        [OSTASK_NUMBER]; /* TCB array for tasks based on task ID */
static Os_ReadyListType             OsTask_ReadyList           [OSTASK_PRIORITY_LEVELS]; /* array of ready lists based on priority */
TaskType                     		OsTask_RunningTask;                         /* currently running task */
TaskType                   		    OsTask_RunningTaskNext;                    /*      task to be run next     */
static TaskType						OsTask_HighestPriority;		        	 /* the highest priority ready or running */
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	/* if we activate a task that has priority higher than the running task */
																		    /*but the running task is non-preemptive ,so store highest priority in this variable  */


/*******************************************************************************
 *                            static Function Prototypes 		               *
 *******************************************************************************/
static void OsSched_ReadyListAddToHead
(
		Os_ReadyListType* list,
		TaskType 		  taskID
);

static void OsSched_ReadyListAddToTail
(
	 Os_ReadyListType* list,
	 TaskType 	     taskID
);

static void OsSched_ReadyListRemoveFromHead
(
	Os_ReadyListType* list
);

static void OsSched_getHighestReadyTask
(
		TaskType *taskIDPtr
);

/*******************************************************************************
*Function Name: OsSched_ReadyListInit
*Parameter (In): list 		-the list to initialize.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: initialize readyList  .
*********************************************************************************/
void OsSched_ReadyListInit(
								  Os_ReadyListType* list
								  )
{
	uint8 i;
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
static void OsSched_ReadyListAddToHead(
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
static void OsSched_ReadyListAddToTail(
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
static void OsSched_ReadyListRemoveFromHead(
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
*Function Name: OsSched_RunningToReady
*Parameter (In): taskID		-id of the task to be moved from running to ready.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: change task state from running to ready,
*			  add the task to the head of the ready list.
*********************************************************************************/
void OsSched_RunningToReady(
							TaskType taskID
							)
{
    OsTask_TCBs[taskID].state = READY;
    OsSched_ReadyListAddToHead(&OsTask_ReadyList[OsTask_TCBs[taskID].CurrentPriority], taskID);
}


/*******************************************************************************
*Macro Name: OsSched_SuspendedToReady
*Parameter (In): taskID		-id of the task to be moved from Suspended to ready.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: change task state from Suspended to ready,
*			  add the task to the tail of the ready list,
*			  update OsTask_HighestPriority .
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

    if(OsTask_TCBs[taskID].CurrentPriority > OsTask_HighestPriority)
    {
    	OsTask_HighestPriority=OsTask_TCBs[taskID].CurrentPriority;
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
*			  update OsTask_HighestPriority .
*********************************************************************************/
#if( (OS_CONFORMANCE == OS_CONFORMANCE_ECC1) ||  (OS_CONFORMANCE == OS_CONFORMANCE_ECC2) )
void OsSched_WaitingToReady
(
			TaskType taskID
)
{
	OsTask_TCBs[taskID].state=READY;
	OsSched_ReadyListAddToTail(&OsTask_ReadyList[OsTask_TCBs[taskID].CurrentPriority], taskID);

	if(OsTask_TCBs[taskID].CurrentPriority > OsTask_HighestPriority)
	{
		OsTask_HighestPriority=OsTask_TCBs[taskID].CurrentPriority;
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
static void OsSched_getHighestReadyTask
(
		TaskType *taskIDPtr
)
{
	sint16 i=(sint16)OsTask_HighestPriority; /* signed to exit when (i<0) otherwise the condition always true */
	*taskIDPtr=INVALID_TASK;
	for( ; (*taskIDPtr==INVALID_TASK) && (i>=0) ;i--)
	{
		*taskIDPtr =OsTask_ReadyList[i].head;
	}

}


