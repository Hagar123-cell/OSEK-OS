/******************************************************************************
 *
 * Module: Interrupts
 *
 * File Name: Interrupt.h
 *
 * Description: Header File for interrupts services for OSEK OS
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#define SUSPEND_ALL_MAX_COUNTER     0xFF
#define MSTATUS_MIE_BIT             0x8

/* HW DEPENDENT MACROS */
#define ENABLE_INTERRUPTS()       __asm volatile 	( "csrs mstatus,MSTATUS_MIE_BIT" )
#define DISABLE_INTERRUPTS()      __asm volatile 	( "csrc mstatus,MSTATUS_MIE_BIT" )


#endif /* INTERRUPT_H_ */
