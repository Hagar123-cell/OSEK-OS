/******************************************************************************
 *
 * Module: OS
 *
 * File Name: Os.h
 *
 * Description: General OS definitions 
 *
 *******************************************************************************/

#ifndef OS_H
#define OS_H

#include "Std_Types.h"

/*
 * type of resource which is the input to GetResource & ReleaseResource
 */
#define ResourceType  char
/*
 *  This data type is used for all status information the API services offer
 */
typedef uint8  StatusType;

typedef enum{
  
  E_OK,
  E_OS_ACCESS, 
  E_OS_CALLEVEL, 
  E_OS_ID, 
  E_OS_LIMIT, 
  E_OS_NOFUNC, 
  E_OS_RESOURCE, 
  E_OS_STATE, 
  E_OS_VALUE
  
}StatusType;

/*******************************************************************************
 *                      Resource API Prototypes                                *
 *******************************************************************************/
/*
 * This call serves to enter critical sections in the code that are 
 * assigned to the resource referenced by <ResID>. A critical 
 * section shall always be left using ReleaseResource
 */
StatusType GetResource ( ResourceType ResID );

/*
 * ReleaseResource is the counterpart of GetResource and 
 * serves to leave critical sections in the code that are assigned to 
 * the resource referenced by <ResID>
*/
StatusType ReleaseResource ( ResourceType ResID );
#endif /* OS_H */
