/******************************************************************************
 *
 * File Name: task_shedule.c
 *
 * Author: David Samir
 *
 * Description: Test shedule API
 *
 * Scenario: priorities of tasks task3,task2 and task1 are 3,2 and 1 respectively, task1 is auto start so task1 will start execution,
 *           task1 call ActivateTask 2 times to activate task2 and task3 ,no scheduling take place after activating task2 and task3 since task1 is NON-Preemptive
 *           then call Schedule which force scheduling and switch context to highest priority task which is task3 ,then call Schedule in task3 
 *	     to force scheduling but execution of task there will be continued since there is no higher priority task than task3
 *	     breakpoint at the super loop in task3 to show the return value of Schedule on successful execution is E_OK.
 *******************************************************************************/
#include "Os.h"
#include "scheduler.h"
#define TASK1_ID 0
#define TASK2_ID 1
#define TASK3_ID 2


void riscv_context_switch(void);

StatusType sched;

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
   ActivateTask(TASK2_ID);
   ActivateTask(TASK3_ID); /*task1 (NON-preemptive) activate task3 which is higher priority so it can switch to task3 when calling Schedule*/ 
   /*@OSEK_TASK_29 	
   The system service StatusType Schedule (void) shall be defined.*/ 
   /* tested by calling the API according to the prototype in the specs */
	
   /*@OSEK_TASK_31 	
   In Schedule API: the current task is put into the ready state, its context is saved and the higher-priority task is executed. 
   Otherwise, the calling task is continued.*/ 
   /*tested since there are higher priority tasks in ready queue so after calling schedule it will switch context to the higher priority task */
   Schedule();
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
  /*@OSEK_TASK_31 	
  In Schedule API: the current task is put into the ready state, its context is saved and the higher-priority task is executed. 
  Otherwise, the calling task is continued.*/ 
  /*tested since there is NO higher priority tasks in ready queue so after calling schedule the calling task is continued */
   
  /*@OSEK_TASK_32 	
  In Schedule API: Possible return values in Standard mode is E_OK */
  /* tested by printing the return value of Schedule using Qemu that shows the return value is E_OK*/
  sched= Schedule();
  for(;;)
  {


  }
}



