/******************************************************************************
 *
 * File Name: task_chainTask_2.c
 *
 * Author: Peter Samir
 *
 * Description: Test ChainTask API
 *
 * Scenario:  task1 and task2 have same priority which is 1, both tasks are auto start ,task1 will start execution since it's added to ready queue first,
 *	      task1 call chainTask to terminate itself and activate itself ,then task2 start excution since it becomes first in the queue 
 *	      breakpoint at task2 to show the state of task1 is ready (task1 activated) and to show events of task1 has been cleared when it's activated.
 *******************************************************************************/
 
 
#include "Os.h"
#include "scheduler.h"
#define TASK1_ID 0
#define TASK2_ID 1



void riscv_context_switch(void);



int inTaskMum=0;






int main()
{
/* set mtvec to RISCV_CONTEXT_SWITCH , for ecall to jump to RISCV_CONTEXT_SWITCH */
    __asm__ volatile ("csrw    mtvec, %0"
              : /* output: none */
              : "r" (riscv_context_switch) /* input : from register */
              : /* clobbers: none */);
    StartOS(OSDEFAULTAPPMODE);
}




void Task1 (void)
{
     OsTask_TCBs[TASK1_ID].Events.OsEventMaskX=3; /*to make sure events will be cleared after calling activate task*/
     OsTask_TCBs[TASK1_ID].EventsWait.OsEventMaskX=9; /*to make sure eventsWait will be cleared after calling activate task*/
     ChainTask(TASK1_ID);
for(;;)
  {


  }
}

void Task2 (void)
{

for(;;)
  {


  }
}


