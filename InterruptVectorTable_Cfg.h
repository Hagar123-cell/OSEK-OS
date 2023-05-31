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

#ifndef INTERRUPTVECTORTABLE_CFG_H_
#define INTERRUPTVECTORTABLE_CFG_H_

#include "Os.h"

#define ISR(x)                 void OsIsr_##x##Func(void)
#define CALL_ISR(x)            OsIsr_##x##Func()

Interrupt_ConfigType Interrupt_Configuration;
OS_Interrupt interrupt_struct;

ISR(SysTickTimer)
{

}

void OsCallSysTickIsr(void)
{
  CALL_ISR(SysTickTimer);
  interrupt_struct.IntNestingDeepth --;
}

const ISRFunc_ptr interruptVectorTable[] =
{
	0,
	0,
	0,
	0,
	0,
	0,
	OsCallSysTickIsr,   // Interrupt Vector 7 (Machine Timer Interrupt)
};

// Set the address and mode in the mtvec register
//uint32 * vectorTableAddress = &interruptVectorTable;

uint32 vectorTableAddress = (uint32)interruptVectorTable;
uint32 mtvecValue = (vectorTableAddress & 0xFFFFFFFC) | 0x1; // to specify the mode

asm volatile("csrw mtvec, %0" :: "r"(mtvecValue));


#endif /* INTERRUPTVECTORTABLE_CFG_H_ */
