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
#include "InterruptVectorTable.h"
#include "Os.h"


/*******************************************************************************
 *                       OS Interrupt Definitions                              *
 *******************************************************************************/

#define SUSPEND_ALL_MAX_COUNTER     0xFF
#define OS_CAT1_PRIO_MASK           0U

/* HW DEPENDENT MACROS */
#define ENABLE_INTERRUPTS()       csr_set_bits_mstatus(MSTATUS_MIE_BIT_MASK)
#define DISABLE_INTERRUPTS()      csr_clear_bits_mstatus(MSTATUS_MIE_BIT_MASK)


/*******************************************************************************
 *                                 Prototypes                                  *
 *******************************************************************************/
void OsCallSysTickIsr(void);

void osSaveAndDisableIntState(void);

void osRestoreSavedIntState(void);

uint32 osGetPMR(void);

void osSetPMR(uint32 level);

boolean osIsInterruptContext(void);

boolean osIsCat2IntContext(void);

void osRunCat2Isr(void);

#endif /* INTERRUPT_H_ */
