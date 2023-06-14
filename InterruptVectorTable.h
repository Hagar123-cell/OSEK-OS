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

/*******************************************************************************
 *                          ISR & Vector Table Definitions                     *
 *******************************************************************************/

#define ISR(x)                 void OsIsr_##x##Func(void)
#define CALL_ISR(x)            OsIsr_##x##Func()

#define VECTOR_TABLE_SIZE      64

/*******************************************************************************
 *                             Prototypes                                      *
 *******************************************************************************/

void set_vector_table_address(uint32 vectorTableAddress);


void set_mtvecValue(uint32 mtvecValue);

/*******************************************************************************
 *                         Interrupt Service Routines                          *
 *******************************************************************************/

ISR(SysTickTimer)
{

}

void OsCallSysTickIsr(void)
{
  CALL_ISR(SysTickTimer);
  OSInterruptStruct->IntNestingDeepth --;
}

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
