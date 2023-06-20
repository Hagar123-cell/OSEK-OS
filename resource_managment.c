/******************************************************************************
 *
 * Module: resource_management
 *
 * File Name: resource_management.c
 *
 * Description: resource management APIs implementation
 *
 *******************************************************************************/


/*******************************************************************************
 *                                  includes                                   *
 *******************************************************************************/
#include "resource_managment.h"



/*******************************************************************************
 *                                  global variables                           *
 *******************************************************************************/




/*******************************************************************************
 *                                  function definitions                       *
 *******************************************************************************/

/*
 * setting ceiling priority for each resource
 */
void get_ceiling_priority(get_using_tasks x )
{
	ceiling_priority max = 0;
  for(uint8 i=0; i<Resources_count; i++)
  {

	  for(uint8 j=0; j<OSTASK_NUMBER_OF_TASKS; j++)
	  {
		 if(max < OsTask_TCBs[j].OsTaskConfig -> OsTaskPriority)
			 max = OsTask_TCBs[j].OsTaskConfig -> OsTaskPriority;

	  }
	  resource_info[i].ceiling_prior = max+1;
  }
}

void Resource_init(get_using_tasks x )
{
	for(uint8 i=0; i<Resources_count; i++)
	{
		resource_info[i].resource_occupation = 0;
	}
	get_ceiling_priority(x);
}
/*
 * This call serves to enter critical sections in the code that are
 * assigned to the resource referenced by <ResID>. A critical
 * section shall always be left using ReleaseResource
 */

/*OSEK_RESOURCE_1*/
StatusType GetResource (ResourceType ResID )
{
	StatusType status;

/*OSEK_RESOURCE_3*/
	if(ResID >= Resources_count)
	{
		status = E_OS_ID;
	}

/*OSEK_RESOURCE_3*/
	else if((resource_info[ResID].resource_occupation == 1) || (OsTask_TCBs[OsSched_getRunningTaskID()].CurrentPriority  > resource_info[ResID].ceiling_prior))
	{
		status = E_OS_ACCESS;
	}
/*OSEK_RESOURCE_2*/
	else
	{
		status = E_OK;
/*OSEK_RESOURCE_4*/
		resource_info[ResID].resource_occupation = 1;
	    OsTask_TCBs[OsSched_getRunningTaskID()].CurrentPriority = resource_info[ResID].ceiling_prior;
	    OsTask_TCBs[OsSched_getRunningTaskID()].Resources ++;// increment no of resources occupied by running task

	}

	return status;
}



/*
 * ReleaseResource is the counterpart of GetResource and
 * serves to leave critical sections in the code that are assigned to
 * the resource referenced by <ResID>
 */

/*OSEK_RESOURCE_5*/
StatusType ReleaseResource ( ResourceType ResID )
{
	StatusType status;

/*OSEK_RESOURCE_7*/
	if(ResID >= Resources_count)
	{
		status = E_OS_ID;
	}
/*OSEK_RESOURCE_7*/
	else if (OsTask_TCBs[OsSched_getRunningTaskID()].CurrentPriority > resource_info[ResID].ceiling_prior)
	{
		status = E_OS_ACCESS;
	}
/*OSEK_RESOURCE_7*/
	else if(resource_info[ResID].resource_occupation == 0)
	{
		status = E_OS_NOFUNC;
	}
/*OSEK_RESOURCE_6*/
	else
	{
		status = E_OK;
/*OSEK_RESOURCE_8*/
		resource_info[ResID].resource_occupation = 0;
		OsTask_TCBs[OsSched_getRunningTaskID()].CurrentPriority = OsTask_TCBs[OsSched_getRunningTaskID()].OsTaskConfig->OsTaskPriority ;
	    OsTask_TCBs[OsSched_getRunningTaskID()].Resources --;// decrement no of resources occupied by running task
/*OSEK_RESOURCE_9*/
		OsSched_reschedule();//call scheduler
	}

	return status;
}


