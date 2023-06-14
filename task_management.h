/******************************************************************************
 *
 * Module: TaskManagement
 *
 * File Name: taskManagement.h
 *
 * Description: Header file for TaskManagement
 *
 * Author:
 *//////////////////////////////////////
 *******************************************************************************/


#ifndef TASK_MANAGEMENT_H_
#define TASK_MANAGEMENT_H_
#include "Os.h"





/*******************************************************************************
 *Function Name: OsTask_taskInit
 *Parameter (In): OsTaskConfig	 - pointer to the first element of static configuration array.
 *Parameter (Out): none
 *Parameter (In/Out): none
 *Return : none
 *Description: initialize tasks TCB and ready list . move autostart task to ready list .
 *********************************************************************************/
void OsTask_taskInit(OsTask * OsTaskConfig);

/*******************************************************************************
 *Function Name: initialiseStack
 *Syntax : OsTask_stackType initialiseStack( OsTask_stackType stackTop , OsTask_EntryType entry)
 *Parameter (In): stackTop    -pointer to stack top.
 *                entry       -pointer to task entry
 *Parameter (Out): none
 *Parameter (In/Out): none
 *Return : pointer to top of context .
 *Description: initialize stack context .
 *             store entry into stack , to ensures that the task code is being executed from the first statement.
 *             setup and store mstatus into stack .
 *Remark: it is implemented in assembly in riscv_context_switching.S file.
 *********************************************************************************/
OsTask_stackType initialiseStack( OsTask_stackType stackTop , OsTask_EntryType entry);

#endif /* TASK_MANAGEMENT_H_ */
