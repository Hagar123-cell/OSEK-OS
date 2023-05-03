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
 *                                 resource configurations                     *
 *******************************************************************************/


/*******************************************************************************
 *                                 Interrupt configurations                     *
 *******************************************************************************/

typedef void (*ISRFunc_ptr)(void);

typedef struct {
	ISRFunc_ptr IsrFunc;
	uint8 IntID;            /* unique identifier for this ICB */
	uint8 IntPRIO;          /* priority of the interrupt source */
	uint8 IntENABLED;       /* flag indicating whether the interrupt source is enabled or disabled */
	uint32 IntSavedLevel;
	uint32 Cat2IntLevel;
	uint32 IntNestingDeepth;
	uint32 IntNestingSavedLevel;
} Interrupt_ConfigType;

Interrupt_ConfigType Interrupt_Configuration;

/*******************************************************************************
 *                                  structures & unions                        *
 *******************************************************************************/
typedef struct
{
	 typedef enum
		{INTERNAL, LINKED, STANDARD}OsResourceProperty;
     struct OsResource *OsResourceLinkedResourceRef;
}OsResource;

#endif /* OS_CFG_H_ */
