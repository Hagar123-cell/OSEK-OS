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
#include "Alarm.h"

/*******************************************************************************
 *                             ISR Definitions                                 *
 *******************************************************************************/

#define ISR(x)                 void OsIsr_##x##Func(void)
#define CALL_ISR(x)            OsIsr_##x##Func()

/*******************************************************************************
 *                                 Global Variables                            *
 *******************************************************************************/

uint8 suspend_All_Counter = 0;
uint32 OsSavedIntState = 0;
TickType CounterIncrement = 1;

/*******************************************************************************
 *                         Interrupt Service Routines                          *
 *******************************************************************************/

ISR(SysTickTimer)
{
  CounterIncrement = IncrementCounter(0, 1);
}

void OsCallSysTickIsr(void)
{
  CALL_ISR(SysTickTimer);
  OSInterruptStruct->IntNestingDeepth --;
}

/*******************************************************************************
 *                             Helper Functions                                *
 *******************************************************************************/

void Interrupt_init(void)
{
	/*set the mtvec value to our interrupt vector table*/
	uint32 mtvecValue = ((uint32)OsCallSysTickIsr & 0xFFFFFFFC) | 0x1;
	csr_write_mtvec(mtvecValue);

	/*initialization of interrupts*/
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

boolean osIsCat2IntContext(void)
{
	return((boolean)OSInterruptStruct->Cat2IntLevel);
}

boolean osIsInterruptContext(void)
{
	return((OSInterruptStruct->IntNestingDeepth > 0) ? TRUE : FALSE);
}

void osRunCat2Isr(void)
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

  OSInterruptStruct->IntNestingDeepth--;
}

void osSaveAndDisableIntState(void)
{
	uint32 mstatus;
	mstatus = csr_read_clear_bits_mstatus(MSTATUS_MIE_BIT_MASK);
	OsSavedIntState = mstatus & MSTATUS_MIE_BIT_MASK;
}

void osRestoreSavedIntState(void)
{
	csr_write_mstatus(OsSavedIntState);
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

/*******************************************************************************
 *                                  Interrupt APIs                             *
 *******************************************************************************/

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
		 *  So do nothing.
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
		 *  so just do nothig.
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
	OSInterruptStruct->IntSavedLevel = osGetPMR();

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
	osSetPMR(OSInterruptStruct->IntSavedLevel);
}
