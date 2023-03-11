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


#endif /* OS_H */
