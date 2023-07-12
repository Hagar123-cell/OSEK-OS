/*
 * Os_PBcfg.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Peter
 */

#ifndef OSEK_OS_OS_PBCFG_H_
#define OSEK_OS_OS_PBCFG_H_
#include "Os.h"
#define STACKSIZE 240

typedef struct Task_ConfigType
{
	OsTask tasksConfig[OSTASK_NUMBER_OF_TASKS];
} Task_ConfigType;


extern const  Task_ConfigType Task_Configuration ;
void Task1 (void);
void Task2 (void);




#endif /* OSEK_OS_OS_PBCFG_H_ */
