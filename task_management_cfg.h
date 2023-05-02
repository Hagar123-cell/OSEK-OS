/******************************************************************************
 *
 * Module: TaskManagement_cfg
 *
 * File Name: taskManagement_cfg.h
 *
 * Description: Description: Pre-Compile Configuration Header file for Task Management
 *
 * Author:
 *
 *******************************************************************************/

#ifndef TASK_MANAGEMENT_CFG_H_
#define TASK_MANAGEMENT_CFG_H_

#define OSTASK_NUMBER_OF_TASKS  20   /* 		1 .. 255		 */

#define OSTASK_PRIORITY_LEVELS  8

#define OS_CONFORMANCE OS_CONFORMANCE_ECC2
#define OS_EXTENDED_ERROR    TRUE
/*******************************************************************************
 *                              App Mode Configuration                         *
 *******************************************************************************/

#define OSAPPMODE_CURRENT_APPMODE OSDEFAULTAPPMODE
#endif /* TASK_MANAGEMENT_CFG_H_ */
