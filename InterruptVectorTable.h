/******************************************************************************
 *
 * Module: Interrupts
 *
 * File Name: InterruptVectorTable.h
 *
 * Description: Header File for interrupt vector table
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#ifndef INTERRUPTVECTORTABLE_H_
#define INTERRUPTVECTORTABLE_H_

#include "Os.h"
#include "Interrupt.h"

#define VECTOR_TABLE_SIZE      64


/*******************************************************************************
 *                         Interrupt Vector Table                              *
 *******************************************************************************/
// Define the interrupt vector table
typedef struct
{
    uint32 interrupt_id;
    void (*ISRFunc_ptr)(void);
} InterruptVector;

InterruptVector interruptVectorTable[VECTOR_TABLE_SIZE] = {
    {1, NULL},
    {2, NULL},
	{3, NULL},
	{4, NULL},
	{5, NULL},
	{6, NULL},
	{7, (ISRFunc_ptr)OsCallSysTickIsr},
};

#endif /* INTERRUPTVECTORTABLE_H_ */
