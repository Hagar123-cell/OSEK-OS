/******************************************************************************
 * Author: Hagar Ahmed & Heba Adel
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

typedef enum
{
	INTERNAL, LINKED, STANDARD
}OsResourceProperty;
/*
typedef struct
{
	 OsResourceProperty ResourceProperty;
	 OsResource *OsResourceLinkedResourceRef;
}OsResource;
*/

typedef struct
{
	ceiling_priority ceiling_prior;
	occupation resource_occupation;
}OsResource;

/*******************************************************************************
 *                      definitions & configurations                           *
 *******************************************************************************/

typedef  uint8 ceiling_priority;
typedef boolean occupation;
OsResource resource_info[Resources_count];



#endif /*_resourse_H*/
