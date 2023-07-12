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

//#include "Std_Types.h"
/*******************************************************************************
 *                  Task Management Pre-Compile Configurations                 *
 *******************************************************************************/

#define TEST 

#define OSTASK_NUMBER_OF_TASKS  1   /* 		1 .. 255		 */

#define INVALID_TASK OSTASK_NUMBER_OF_TASKS


#define OSTASK_PRIORITY_LEVELS  8

#define OS_CONFORMANCE OS_CONFORMANCE_ECC2
#define OS_EXTENDED_ERROR    TRUE

/*******************************************************************************
 *                  Resource Management Pre-Compile Configurations             *
 *******************************************************************************/
#define Resources_count 15



/*******************************************************************************
 *                              App Mode Configuration                         *
 *******************************************************************************/
#define OSDEFAULTAPPMODE  1
#define OSAPPMODE_CURRENT_APPMODE OSDEFAULTAPPMODE

#endif /* OS_CFG_H_ */
