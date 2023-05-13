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


extern OsTask_TCBType              	OsTask_TCBs        [OSTASK_NUMBER_OF_TASKS];


/*******************************************************************************
*Function Name: OsSched_RunningToWaiting
*Parameter (In): none
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: move task from running to waiting.
*********************************************************************************/
#if( (OS_CONFORMANCE == OS_CONFORMANCE_ECC1) ||  (OS_CONFORMANCE == OS_CONFORMANCE_ECC2) )
void OsSched_RunningToWaiting(void);
#endif

/*******************************************************************************
*Macro Name: OsSched_RunningToSuspended
*Parameter (In): none
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: move task from running to suspended.
*********************************************************************************/
void OsSched_RunningToSuspended(void);

/*******************************************************************************
*Function Name: OsSched_RunningToReady
*Parameter (In): none.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: change task state from running to ready,
*			  add the task to the head of the ready list.
*********************************************************************************/
void OsSched_RunningToReady(void);

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


/*******************************************************************************
*Function Name: OsSched_schedulerInit
*Parameter (In): none.
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: initialize ready list , OsTask_RunningTaskID, OsTask_HighestBasePriority  .
*********************************************************************************/
void OsSched_schedulerInit();



/*******************************************************************************
*Function Name: OsSched_reschedule
*Parameter (In): none
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: get highest priority task and switch context to it  .
*Remark: this function check if the running task is preemptive or NOT before perform switch context.
*********************************************************************************/
void OsSched_reschedule();


/*******************************************************************************
*Function Name: OsSched_getRunningTaskID
*Parameter (In): none
*Parameter (Out): none
*Parameter (In/Out): none
*Return : OsTask_RunningTaskID   -Running Task ID
*Description: get Running Task ID  .
*********************************************************************************/
TaskType OsSched_getRunningTaskID();


/*******************************************************************************
*Function Name: OsSched_scheduleInternal
*Parameter (In): none
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description:this function switch the context to the highest priority task.
*Remark: this function is called only in schedule API.
*********************************************************************************/
void OsSched_scheduleInternal();


/*******************************************************************************
*Function Name: Ossched_StartScheduler
*Parameter (In): none
*Parameter (Out): none
*Parameter (In/Out): none
*Return : none
*Description: switch context to the highest task in ready list .
*********************************************************************************/
void Ossched_StartScheduler();

#endif /* SCHEDULER_H_ */
