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
#include"scheduler.h"

/*******************************************************************************
 *                      definitions & configurations                           *
 *******************************************************************************/

typedef  uint8 ceiling_priority;
typedef boolean occupation;




/*******************************************************************************
 *                                  structures & unions                        *
 *******************************************************************************/



typedef struct
{
	ceiling_priority ceiling_prior;
	occupation resource_occupation;
}os_resource_info;


os_resource_info resource_info [Resources_count];


#endif /*_resourse_H*/
