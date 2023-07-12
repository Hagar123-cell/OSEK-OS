/******************************************************************************
 *
 * File Name: task_chainTask_1.c
 *
 * Author: Peter Samir
 *
 * Description: Test ChainTask API
 *
 * Scenario: priorities of tasks task3,task2 and task1 are 3,2 and 1 respectively, task3 and task2 are auto start so task3 will start execution since it's higher priority,
 *           task3 call chainTask to terminate itself and activate task1,then task2 start execution since it's already ready and higher priority than task1	 
 *	     breakpoint at task2 to show the state of task3 is suspended (task3 terminated) and show the state of task1 is ready (task1 activated)
 *******************************************************************************/


#include "Os.h"
#include "scheduler.h"
#define TASK1_ID 0
#define TASK2_ID 1
#define TASK3_ID 2


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

void Task3 (void)
{
        /*@OSEK_TASK_18 	
	The system service StatusType ChainTask (TaskType TaskID) shall be defined.*/ 
	/* tested by calling the API according to the prototype in the specs */
	
	
	/*@OSEK_TASK_19 	
	In ChainTask API: This service causes the termination of the calling task.*/ 
	/*tested by termination of the calling task and switch to task2 otherwise it will be stuck at super loop*/
	
	
	/*@OSEK_TASK_20 	
	In ChainTask API: After termination of the calling task a succeeding task TaskID shall be activated. */
	/*tested by printing the state of task1 after activation by chainTask using Qemu that shows the state of the task is ready*/
	
	
	/*@OSEK_TASK_23 	
	In ChainTask API: If called successfully, ChainTask does not return to the call level and 
	the status cannot be evaluated. */
	/*tested by termination of the calling task and switch to another task without return*/

      /*@OSEK_TASK_24 	In ChainTask API: If the service 
      ChainTask is called successfully, this enforces a rescheduling. */
      /*tested by forcing rescheduling after calling chainTask*/


   ChainTask(TASK1_ID);

  for(;;)
  {


  }
}

