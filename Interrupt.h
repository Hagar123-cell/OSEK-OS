/******************************************************************************
 *
 * Module: Interrupts
 *
 * File Name: OsInterrupts.h
 *
 * Description: Header File for interrupts services for OSEK OS
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "Interrupt_HW.h"
#include "InterruptVectorTable_Cfg.h"
#include "Os.h"

/*******************************************************************************
 *                       OS Interrupt Definitions                              *
 *******************************************************************************/

#define SUSPEND_ALL_MAX_COUNTER     0xFF
#define MSTATUS_MIE_BIT_MASK        0x8
#define OS_CAT1_PRIO_MASK           0U

/* HW DEPENDENT MACROS */
#define ENABLE_INTERRUPTS()       __asm__ volatile 	( "csrs mstatus,MSTATUS_MIE_BIT_MASK" )
#define DISABLE_INTERRUPTS()      __asm__ volatile 	( "csrc mstatus,MSTATUS_MIE_BIT_MASK" )


/*******************************************************************************
 *                                 Prototypes                                  *
 *******************************************************************************/
void osSaveAndDisableIntState(void);

void osRestoreSavedIntState(void);

uint32 osGetPMR(void);

void osSetPMR(uint32 level);

boolean OsIsInterruptContext(void);

boolean OsIsCat2IntContext(void);

void osInitInterrupts(void);

void OsRunCat2Isr(void);

#endif /* INTERRUPT_H_ */
