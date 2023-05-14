/******************************************************************************
 *
 * Module: resource_management
 *
 * File Name: resource_management.h
 *
 * Description: resource management APIs implementation
 *
 *******************************************************************************/
#ifndef  _resourse_H
#define _resourse_H

/*******************************************************************************
 *                                  includes                                   *
 *******************************************************************************/
#include"Os.h"
#include "resource_event_cfg.h"
#include"scheduler.h"

/*******************************************************************************
 *                                  structures & unions                        *
 *******************************************************************************/
typedef struct
{
	 typedef enum
		{INTERNAL, LINKED, STANDARD}OsResourceProperty;
     struct OsResource *OsResourceLinkedResourceRef;
}OsResource;


/*******************************************************************************
 *                      definitions & configurations                           *
 *******************************************************************************/



/*******************************************************************************
 *                      extern module shared global variables                  *
 *******************************************************************************/
extern boolean occupation[Resources_count];
extern uint8 ceiling_priority[Resources_count];// in progress



#endif /*_resourse_H*/
