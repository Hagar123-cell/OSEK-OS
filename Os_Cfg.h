/******************************************************************************
 *
 * Module: Os_Cfg
 *
 * File Name: Os_Cfg.h
 *
 * Description: configurations for the os
 *
 *******************************************************************************/

#ifndef OS_CFG_H_
#define OS_CFG_H_

#include "Std_Types.h"
/*******************************************************************************
 *                  Task Management Pre-Compile Configurations                 *
 *******************************************************************************/

#define OSTASK_NUMBER_OF_TASKS  20   /* 		1 .. 255		 */

#define INVALID_TASK OSTASK_NUMBER_OF_TASKS


#define OSTASK_PRIORITY_LEVELS  8

#define OS_CONFORMANCE OS_CONFORMANCE_ECC2
#define OS_EXTENDED_ERROR    TRUE

/*******************************************************************************
 *                              App Mode Configuration                         *
 *******************************************************************************/
#define OSDEFAULTAPPMODE  1
#define OSAPPMODE_CURRENT_APPMODE OSDEFAULTAPPMODE

/*******************************************************************************
 *                                  structures & unions                        *
 *******************************************************************************/



/*******************************************************************************
 *                       OS Interrupt Configuration                            *
 *******************************************************************************/

/* Type definition contains the nesting type of interrupts */
typedef enum
{
  NOT_NESTED,
  NESTED
}OsInterruptNestingType;

/* Type definition for ISR*/
typedef void (*ISRFunc_ptr)(void);


/* Structures specifies the config of interrupt */
typedef struct {
	ISRFunc_ptr IsrFunc;
	uint8 IntID;            /* unique identifier for this ICB */
	uint8 IntPRIO;          /* priority of the interrupt source */
	OsInterruptNestingType IntType;
}Interrupt_ConfigType;

/* Pointer to Interrupt configuration*/
Interrupt_ConfigType *Interrupt_Config_Ptr;


typedef struct
{
	uint32 IntSavedLevel;
	uint32 Cat2IntLevel;
	uint32 IntNestingDeepth;
	uint8 IntENABLED;      /* flag indicating whether the interrupt source is enabled or disabled*/
}OS_Interrupt;

/* Pointer to Interrupt struct*/
OS_Interrupt *OSInterruptStruct;




#endif /* OS_CFG_H_ */
