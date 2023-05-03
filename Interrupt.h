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

#include "Std_types.h"
#include "OS_Cfg.h"


#define PLIC_BASE_ADDR              0xC000000


#define SUSPEND_ALL_MAX_COUNTER     0xFF
#define MSTATUS_MIE_BIT_MASK        0x8
#define OS_CAT1_PRIO_MASK           0U

/* HW DEPENDENT MACROS */
#define ENABLE_INTERRUPTS()       __asm__ volatile 	( "csrs mstatus,MSTATUS_MIE_BIT_MASK" )
#define DISABLE_INTERRUPTS()      __asm__ volatile 	( "csrc mstatus,MSTATUS_MIE_BIT_MASK" )

typedef struct {
    volatile uint32 threshold; /* PLIC threshold register */
    /* Other PLIC registers ... */
} plic_t;
/* Pointer to PLIC base address */
#define PLIC ((plic_t *)PLIC_BASE_ADDR)



/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern structure to be used by Interrupt and other modules */
extern Interrupt_ConfigType Interrupt_Configuration;

/*******************************************************************************
 *                                 Prototypes                                  *
 *******************************************************************************/
void osSaveAndDisableIntState(void);

void osRestoreSavedIntState(void);

uint32 osGetPMR(void);

void osSetPMR(uint32 level);

#endif /* INTERRUPT_H_ */
