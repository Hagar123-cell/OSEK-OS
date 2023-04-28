/******************************************************************************
 *
 * Module: scheduler
 *
 * File Name: scheduler.h
 *
 * Description: Header file for scheduler
 *
 * Author:
 *
 *******************************************************************************/

#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include "task_management.h"


extern OsTask_TCBType              	OsTask_TCBs        [OSTASK_NUMBER];

/*******************************************************************************
*Macro Name: OSSCHED_RUNNING_TO_WAITING
*Parameter (In): taskID		-id of the task to be moved from running to waiting.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: move task from running to waiting.
*********************************************************************************/
#if( (OS_CONFORMANCE == OS_CONFORMANCE_ECC1) ||  (OS_CONFORMANCE == OS_CONFORMANCE_ECC2) )
#define OSSCHED_RUNNING_TO_WAITING(taskID) OsTask_TCBs[(taskID)].state=WAITING;
#endif

/*******************************************************************************
*Macro Name: OSSCHED_RUNNING_TO_SUSPENDED
*Parameter (In): taskID		-id of the task to be moved from running to suspended.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: move task from running to suspended.
*********************************************************************************/
#define OSSCHED_RUNNING_TO_SUSPENDED(taskID)  OsTask_TCBs[(taskID)].state= SUSPENDED;



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
							);


/*******************************************************************************
*Macro Name: OsSched_SuspendedToReady
*Parameter (In): taskID		-id of the task to be moved from Suspended to ready.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: change task state from Suspended to ready,
*			  add the task to the tail of the ready list.
*********************************************************************************/
void OsSched_SuspendedToReady(
								TaskType taskID
								);

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
							);


/*******************************************************************************
*Function Name: OsSched_WaitingToReady
*Parameter (In): taskID		-id of the task to be moved from waiting to ready.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: change task state from waiting to ready,
*			  add the task to the tail the ready list.
*********************************************************************************/
#if( (OS_CONFORMANCE == OS_CONFORMANCE_ECC1) ||  (OS_CONFORMANCE == OS_CONFORMANCE_ECC2) )
void OsSched_WaitingToReady(
							TaskType taskID
							);
#endif

#endif /* SCHEDULER_H_ */
