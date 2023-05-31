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

#define OSAPPMODE_CURRENT_APPMODE OSDEFAULTAPPMODE

/*******************************************************************************
 *                                  structures & unions                        *
 *******************************************************************************/


/*******************************************************************************
 *                                 Interrupt configurations                     *
 *******************************************************************************/

typedef enum
{
  NOT_NESTED = 0,
  NESTED
}OsInterruptNestingType;

typedef void (*ISRFunc_ptr)(void);

typedef struct {
	ISRFunc_ptr IsrFunc;
	uint8 IntID;            /* unique identifier for this ICB */
	uint8 IntPRIO;          /* priority of the interrupt source */
	OsInterruptNestingType IntType;
} Interrupt_ConfigType;



typedef struct
{
	uint32 IntSavedLevel;
	uint32 Cat2IntLevel;
	uint32 IntNestingDeepth;
	uint8 IntENABLED;       /* flag indicating whether the interrupt source is enabled or disabled */
}OS_Interrupt;


#endif /* OS_CFG_H_ */
