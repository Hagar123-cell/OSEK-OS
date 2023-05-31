/******************************************************************************
 *
 * Module: Interrupts
 *
 * File Name: OsInterrupts.h
 *
 * Description: Source File for interrupts services for OSEK OS
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#include "Interrupt.h"
#include "Os.h"

uint8 suspend_All_Counter = 0;
uint32 OsSavedIntState = 0;

//extern Interrupt_ConfigType Interrupt_Configuration;
//extern OS_Interrupt interrupt_struct;
//extern PLIC_Type plic_type;

void osInitInterrupts(void)
{
	for(uint32 Intsource = 0; Intsource < 53; Intsource++)
	{
		/* enable the interrupt */
		*(volatile uint64*)(PLIC->enable) |= (uint64)(1ull << Intsource);
	}
	/* PLIC nested interrupts are not supported */
	PLIC->threshold.reg = 0;

	/* clear all the PLIC pending flags before enabling the global external interrupt flag */
	while(PLIC->claim != 0u)
	{
		PLIC->claim = PLIC->claim;
	}

	/* set the global interrupts enable flags */
	ENABLE_INTERRUPTS();

}

boolean OsIsCat2IntContext(void)
{
	return((boolean)interrupt_struct.Cat2IntLevel);
}

boolean OsIsInterruptContext(void)
{
	return((interrupt_struct.IntNestingDeepth > 0) ? TRUE : FALSE);
}

void OsRunCat2Isr(void)
{
  /* get the PLIC pending interrupt ID */
  static uint32 PlicIntId = 0;

  PlicIntId = PLIC->claim;

  if(PlicIntId < 52u)
  {
    /* call the appropriate interrupt service routine */
	  interruptVectorTable[PlicIntId];
  }

  /* clear pending interrupt flag by setting the associated enable bit */
  *(volatile uint64*)(PLIC->enable) |= (uint64)(1ull << PlicIntId);

  /* set the interrupt as completed */
  PLIC->claim = (uint32)PlicIntId;

  interrupt_struct.IntNestingDeepth--;
}

void osSaveAndDisableIntState(void)
{
	unsigned int mstatus;
	__asm__ volatile("csrrc %0, mstatus, %1" : "=r" (mstatus) : "r" (MSTATUS_MIE_BIT_MASK));
	OsSavedIntState = mstatus& MSTATUS_MIE_BIT_MASK;
}

void osRestoreSavedIntState(void)
{
	__asm__ volatile ("csrw    mstatus, %0"
			: /* output: none */
			: "r" (OsSavedIntState)); /* input : from register */
}

uint32 osGetPMR(void)
{
	uint32 pmr_value;
	DISABLE_INTERRUPTS();
	pmr_value = PLIC->threshold.reg;
	ENABLE_INTERRUPTS();
	return pmr_value;
}

void osSetPMR(uint32 level)
{
	PLIC->threshold.reg = level;
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
	/* Get the global mask prio */
	interrupt_struct.IntSavedLevel = osGetPMR();

	/* Disable OS interrupts */
	osSetPMR(OS_CAT1_PRIO_MASK);
}

/*
 * This service restores the recognition status of interrupts saved
 * by the SuspendOSInterrupts service.
 */
void ResumeOSInterrupts(void)
{
	/* Restore the global mask prio */
	osSetPMR(interrupt_struct.IntSavedLevel);
}


