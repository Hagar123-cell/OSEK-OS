/******************************************************************************
 *
 * Module: resourse_managment
 *
 * File Name: resourse_managment.c
 *
 * Description: resourse managment APIs implementation
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
uint8 ceiling_priority[Resources_count] = {5, 3, 2}; /////////////////////

/*******************************************************************************
 *                                  function definitions                                   *
 *******************************************************************************/
StatusType GetResource (ResourceType ResID )
{
	StatusType status;

	if(ResID >= Resources_count) /* &&(ResID != RES_SCHEDULER)*/
	{
		status = E_OS_ID;
	}
	else if((occupation[ResID] == 1) || (currentTCB -> base_priority > ceiling_priority[ResID])) /* (currentTCB -> base_priority > ceiling_priority) to be deleted*/
	{
		status = E_OS_ACCESS;
	}
	else
	{
		status = E_OK;
		occupation[ResID] = 1;
		currentTCB -> new_priority = ceiling_priority[ResID];
	}

	return status;
}
StatusType ReleaseResource ( ResourceType ResID )
{
	StatusType status;

	if(ResID >= Resources_count) /* &&(ResID != RES_SCHEDULER)*/
	{
		status = E_OS_ID;
	}
	else if (currentTCB -> new_priority > ceiling_priority[ResID]) /* (currentTCB -> base_priority > ceiling_priority) to be deleted*/
	{
		status = E_OS_ACCESS;
	}
	else if(occupation[ResID] == 0)
	{
		status = E_OS_NOFUNC;
	}
	else
	{
		status = E_OK;
		occupation[ResID] = 0;
		currentTCB -> new_priority = base_priority;
	}

	return status;
}
