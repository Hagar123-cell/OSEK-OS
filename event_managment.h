/******************************************************************************
 *
 * Module: event_management
 *
 * File Name: event_management.h
 *
 * Description: event management APIs implementation
 *
 *******************************************************************************/

#ifndef EVENT_MANAGMENT_H_
#define EVENT_MANAGMENT_H_

 /*******************************************************************************
  *                                  includes                                   *
  *******************************************************************************/
#include"Os.h"
#include "resource_event_cfg.h"
#include"scheduler.h"

  /*******************************************************************************
   *                      definitions & configurations                           *
   *******************************************************************************/

typedef uint32 OsEventMask;

typedef OsEventMask EventMaskType;
typedef EventMaskType* EventMaskRefType;

typedef uint32 TaskEventsType;  // usage?
typedef OsEvent* OsEventRefType;

/*******************************************************************************
 *                                  structures & unions                        *
 *******************************************************************************/

typedef struct
{
	OsEventMask OsEventMaskX; //1 -> represent events that the task is interested in
}OsEvent;

typedef OsEvent* OsEventRefType;

/*******************************************************************************
 *                      extern module shared global variables                          *
 *******************************************************************************/

#endif /* EVENT_MANAGMENT_H_ */
