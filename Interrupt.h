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

#include "OS_Cfg.h"
#include "Std_Types.h"
#include "InterruptVectorTable_Cfg.h"


#define PLIC_BASE_ADDR              0xC000000


#define SUSPEND_ALL_MAX_COUNTER     0xFF
#define MSTATUS_MIE_BIT_MASK        0x8
#define OS_CAT1_PRIO_MASK           0U

/* HW DEPENDENT MACROS */
#define ENABLE_INTERRUPTS()       __asm__ volatile 	( "csrs mstatus,MSTATUS_MIE_BIT_MASK" )
#define DISABLE_INTERRUPTS()      __asm__ volatile 	( "csrc mstatus,MSTATUS_MIE_BIT_MASK" )


/* Pointer to PLIC base address */
#define PLIC ((PLIC_Type *)PLIC_BASE_ADDR)


typedef struct {                                    /*!< (@ 0x0C000000) PLIC Structure                                         */

	union {
		volatile uint32  reg;                             /*!< (@ 0x0C000000) Interrupt Priority Register                            */

		struct {
			volatile uint32  priority   :  3;               /*!< [0..2] (null)                                                         */
		} bit;                                          /*!< [3] BitSize                                                           */
	} priority[53];
	volatile  uint32  RESERVED[971];
	volatile uint32  pending[2];                        /*!< (@ 0x0C001000) Interrupt Pending Register                             */
	volatile  uint32  RESERVED1[1022];
	volatile uint32  enable[2];                         /*!< (@ 0x0C002000) Interrupt Enable Register                              */
	volatile  uint32  RESERVED2[522238];

	union {
		volatile uint32  reg;                             /*!< (@ 0x0C200000) Priority Threshold Register                            */

		struct {
			volatile uint32  priority   :  3;               /*!< [0..2] (null)                                                         */
		} bit;                                          /*!< [3] BitSize                                                           */
	} threshold;
	volatile uint32  claim;                             /*!< (@ 0x0C200004) Claim/Complete Register                                */
} PLIC_Type;

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/


/* Extern structure to be used by Interrupt and other modules */
Interrupt_ConfigType Interrupt_Configuration;

OS_Interrupt interrupt_struct;

//PLIC_Type plic_type;

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
