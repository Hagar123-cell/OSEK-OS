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
#include "resourse_managment.h"



/*******************************************************************************
 *                                  global variables                           *
 *******************************************************************************/
boolean occupation[Resources_count] = {0};
uint8 ceiling_priority[Resources_count] = {5, 3, 2}; //in progress




/*******************************************************************************
 *                                  function definitions                       *
 *******************************************************************************/

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
	else if((occupation[ResID] == 1) || (OsTask_TCBs[OsSched_getRunningTaskID()].CurrentPriority  > ceiling_priority[ResID]))
	{
		status = E_OS_ACCESS;
	}
/*OSEK_RESOURCE_2*/
	else
	{
		status = E_OK;
/*OSEK_RESOURCE_4*/
		occupation[ResID] = 1;
	    OsTask_TCBs[OsSched_getRunningTaskID()].CurrentPriority = ceiling_priority[ResID];
	    // is it complete
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
	else if (OsTask_TCBs[OsSched_getRunningTaskID()].CurrentPriority > ceiling_priority[ResID])
	{
		status = E_OS_ACCESS;
	}
/*OSEK_RESOURCE_7*/
	else if(occupation[ResID] == 0)
	{
		status = E_OS_NOFUNC;
	}
/*OSEK_RESOURCE_6*/
	else
	{
		status = E_OK;
/*OSEK_RESOURCE_8*/
		occupation[ResID] = 0;
		OsTask_TCBs[OsSched_getRunningTaskID()].CurrentPriority = OsTask_TCBs[OsSched_getRunningTaskID()].OsTaskConfig->OsTaskPriority ;
/*OSEK_RESOURCE_9*/
		OsSched_reschedule();//call scheduler
	}

	return status;
}
