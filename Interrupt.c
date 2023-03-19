/******************************************************************************
 *
 * Module: Interrupts
 *
 * File Name: Interrupt.h
 *
 * Description: Source File for interrupts services for OSEK OS
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#include "Interrupt.h"
#include "Os.h"
#include "Std_types.h"

uint8 suspend_All_Counter = 0;
uint8 OsSavedIntState = 0;

void osSaveAndDisableIntState(void)
{
  OsSavedIntState = csr_read_clr_bits_mstatus(MSTATUS_MIE_BIT);
}

void osRestoreSavedIntState(void)
{
  csr_write_mstatus(OsSavedIntState);
}
/*
 * This service disables all interrupts for which the hardware
 * supports disabling. The state before is saved for the
 * EnableAllInterrupts call.
 */
void DisableAllInterrupts(void)
{
	DISABLE_INTERRUPTS();
}

/*
 * This service restores the state saved by DisableAllInterrupts.
 */
void EnableAllInterrupts(void)
{
	ENABLE_INTERRUPTS();
}

/*
 * This service saves the recognition status of all interrupts and
 * disables all interrupts for which the hardware supports
 * disabling.
 */

void SuspendAllInterrupts(void)
{
	if (suspend_All_Counter == SUSPEND_ALL_MAX_COUNTER) {
		/*
		 *  SuspendAllInterrupts has reached its max nest count
		 *  So do nothing. May a ResumeAllInterrupts call has been forgot.
		 */
	}
	else if (suspend_All_Counter == 0) {
		osSaveAndDisableIntState();
		suspend_All_Counter++;
	}
	else {
		suspend_All_Counter++;
	}
}

/*
 * This service restores the recognition status of all interrupts
 * saved by the SuspendAllInterrupts service.
 */
void ResumeAllInterrupts(void)
{
	if (suspend_All_Counter == 0) {
		/*
		 *  SuspendAllInterrupts hasn't been called before ResumeAllInterrupts
		 *  It's an error, so just do nothig.
		 */
	}
	else if (suspend_All_Counter == 1) {
		suspend_All_Counter--;
		osRestoreSavedIntState();
	}
	else {
		suspend_All_Counter--;
	}
}

/*
 * This service saves the recognition status of interrupts of
 * category 2 and disables the recognition of these interrupts.
 */
void SuspendOSInterrupts(void)
{

}

/*
 * This service restores the recognition status of interrupts saved
 * by the SuspendOSInterrupts service.
 */
void ResumeOSInterrupts(void)
{

}


