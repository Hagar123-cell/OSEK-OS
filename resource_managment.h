/******************************************************************************
 *
 * Module: resourse_managment
 *
 * File Name: resourse_managment.h
 *
 * Description: resourse managment APIs implementation
 *
 *******************************************************************************/
#ifndef  _resourse_H
#define _resourse_H

/*******************************************************************************
 *                                  includes                                   *
 *******************************************************************************/
#include"Os.h"

/*******************************************************************************
 *                      definitions & configurations                           *
 *******************************************************************************/
#define RES_SCHEDULER /////255//////////////
#define Resources_count 3


/*******************************************************************************
 *                      extern module shared global variables                          *
 *******************************************************************************/
extern boolean occupation[Resources_count];
extern uint8 ceiling_priority[Resources_count];



#endif /*_resourse_H*/
