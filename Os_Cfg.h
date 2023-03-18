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

/*******************************************************************************
 *                                 resource configurations                     *
 *******************************************************************************/

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
