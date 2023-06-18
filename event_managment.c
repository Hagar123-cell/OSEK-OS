/******************************************************************************
 *
 * Module: event_managment
 *
 * File Name: event_management.c
 *
 * Description: event management APIs implementation
 *
 *******************************************************************************/




/*******************************************************************************
 *                                  includes                                   *
 *******************************************************************************/
# include"event_managment.h"




/*******************************************************************************
 *                                  function definitions                       *
 *******************************************************************************/

/*
 *This service returns the current state of all event bits of the task
 *<TaskID>, not the events that the task is waiting for.
 *The service may be called from interrupt service routines, task
 *level and some hook routines
 *The current status of the event mask of task <TaskID> is copied
 *to <Event>.
*/

/* OSEK_EVENT_1 */
StatusType GetEvent ( TaskType TaskID , EventMaskRefType Event )
{
	StatusType status;

/* OSEK_EVENT_3 */
		if(TaskID>=OSTASK_NUMBER_OF_TASKS)
		{
			status = E_OS_ID;
		}
/* OSEK_EVENT_3 */
		else if(!(OsTask_TCBs[TaskID].OsTaskConfig -> taskKind == EXTENDED))
		{
			status = E_OS_ACCESS;
		}
/* OSEK_EVENT_3 */
		else if(OsTask_TCBs[TaskID].state == SUSPENDED)
		{
			status = E_OS_STATE;
		}
		else
/* OSEK_EVENT_2 */
		{
			status = E_OK;

/* OSEK_EVENT_4 */
/* OSEK_EVENT_5 */
			*Event = 0;
			/*retrieves the current state of the task's pending events, i.e., the event flags that are currently set for the task*/
			*Event = OsTask_TCBs[TaskID].Events.OsEventMaskX;
		}

		return status;
}


/*
 *The state of the calling task is set to waiting, unless at least one
 *of the events specified in <Mask> has already been set.
*/

/* OSEK_EVENT_6 */
StatusType WaitEvent ( EventMaskType Mask )
{
	StatusType status;

/* OSEK_EVENT_8 */
		if(!((OsTask_TCBs[OsSched_getRunningTaskID()]. OsTaskConfig -> taskKind )== EXTENDED))//not extended
		{
			status = E_OS_ACCESS;
		}
/* OSEK_EVENT_8 */
		else if(OS_GET_CALL_LEVEL() == ISR2_LEVEL)
		{
			status = E_OS_CALLEVEL;
		}
/* OSEK_EVENT_8 */
		else if(OsTask_TCBs[OsSched_getRunningTaskID()].Resources != 0)//has resources
		{
			status = E_OS_RESOURCE;
		}
/* OSEK_EVENT_7 */
		else
		{
			status = E_OK;/////////////////////////////////////////////
/* OSEK_EVENT_9 */
			if(!(OsTask_TCBs[OsSched_getRunningTaskID()].Events.OsEventMaskX & Mask))
			{
				OsTask_TCBs[OsSched_getRunningTaskID()].EventsWait.OsEventMaskX = Mask ;
				OsSched_RunningToWaiting();  //enter waiting state

/* OSEK_EVENT_10 */
				OsSched_reschedule();//call scheduler
			}
		}

		return status;
}

/* OSEK_EVENT_11 */
StatusType ClearEvent ( EventMaskType Mask )
{
	StatusType status;

/* OSEK_EVENT_13 */
			if(!((OsTask_TCBs[OsSched_getRunningTaskID()]. OsTaskConfig -> taskKind )== EXTENDED))//not extended
			{
				status = E_OS_ACCESS;
			}
/* OSEK_EVENT_13 */
			else if(OS_GET_CALL_LEVEL() == ISR2_LEVEL)
			{
				status = E_OS_CALLEVEL;
			}
			else
			{
/* OSEK_EVENT_12*/
				status = E_OK;
/* OSEK_EVENT_14*/
				OsTask_TCBs[OsSched_getRunningTaskID()].Events.OsEventMaskX &= ~ ( Mask & OsTask_TCBs[OsSched_getRunningTaskID()].OsTaskConfig->OsTaskEventRef->OsEventMaskX);
			}
			return status;
}

/* OSEK_EVENT_15 */
StatusType SetEvent ( TaskType TaskID ,EventMaskType Mask )
{
	StatusType status;

/* OSEK_EVENT_17 */
			if(TaskID>=OSTASK_NUMBER_OF_TASKS)
			{
				status = E_OS_ID;
			}
/* OSEK_EVENT_17 */
			else if(!((OsTask_TCBs[OsSched_getRunningTaskID()]. OsTaskConfig -> taskKind )== EXTENDED))
			{
				status = E_OS_ACCESS;
			}
/* OSEK_EVENT_17 */
			else if(OsTask_TCBs[TaskID].state == SUSPENDED)
			{
				status = E_OS_STATE;
			}
			else
			{
/* OSEK_EVENT_16*/
				status = E_OK;
				if(OsTask_TCBs[TaskID].state == RUNNING ||OsTask_TCBs[TaskID].state == READY || OsTask_TCBs[TaskID].state == WAITING)
				{
/* OSEK_EVENT_18 */
				    OsTask_TCBs[TaskID].Events.OsEventMaskX |= (Mask & OsTask_TCBs[OsSched_getRunningTaskID()].OsTaskConfig->OsTaskEventRef->OsEventMaskX);
				    if (( OsTask_TCBs[TaskID].state == WAITING ) && ( OsTask_TCBs[TaskID].EventsWait.OsEventMaskX & OsTask_TCBs[TaskID].Events.OsEventMaskX ) )
				    {
				    	OsSched_WaitingToReady(TaskID);//  from waiting to ready
				    }
/* OSEK_EVENT_19 */
				    OsSched_reschedule();//call scheduler
				}

			}
			return status;

}
