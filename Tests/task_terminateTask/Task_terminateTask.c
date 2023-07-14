/************************************************************************************************************************************
 *
 * File Name: task_shedule.c
 *
 * Author: David Samir
 *
 * Description: Test shedule API
 *
 * Scenario: priorities of tasks task2 , task1 and IdleTask are 2 ,1 and 0 respectively, the 3 tasks are auto start so task2 will start execution,
 *           task2 call TerminateTask to terminate itself and force scheduling ,hence context is switched to highest priority task which is task1,
 *           task1 increment the number of its activations by 1 manually then call TerminateTask to terminate itself ,hence task1 start execution
 *           from the first instruction since its activations >0 and its the highest priority task in ready queue, then task1 will call TerminateTask
 *           so IdleTask can start execution
 *	    	 breakpoint at IdleTask to show the value of num_of_Task1_hits which will be 2 and the state of the 3 tasks.
 ************************************************************************************************************************************/
#include "Os.h"
#include "scheduler.h"
#define TASK1_ID 0
#define TASK2_ID 1
#define IdleTask_ID 2


void riscv_context_switch(void);

int num_of_Task1_hits=0; /* used to indicate the number of hits for task1 */

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


	num_of_Task1_hits++; /*increase the number of hits for task1 by 1*/

	if (num_of_Task1_hits<2) /* this condition is executed once */
	{
		OsTask_TCBs[TASK1_ID].Activations=1;/* increase the number of activations manually */
	}
	else
	{
	    /*nothing*/
	}


	TerminateTask();



for(;;)
  {


  }
}

void IdleTask (void)
{

  for(;;)
  {


  }
}
void Task2 (void)
{
   /*@OSEK_TASK_10
   The system service StatusType TerminateTask (void) shall be defined. */
   /* tested by calling the API according to the prototype in the specs */

   /*@OSEK_TASK_11
   In TerminateTask API: The calling task shall be transferred from the running state into the suspended state. */
   /*tested by printing the TCB of task2 using Qemu that shows the state of the task is suspended*/

   /*OSEK_TASK_13
   In TerminateTask API: If the call was successful, TerminateTask does not return to the call level and the status cannot be evaluated.*/
   /*tested since the task is terminated and force rescheduling to switch to another task so no return from TerminateTask */

   /*OSEK_TASK_15
   In TerminateTask API: If the service TerminateTask is called successfully, it enforces a rescheduling. */
   /*tested since the task is terminated , force rescheduling and swtich to another task which is task1*/


  TerminateTask();


  for(;;)
  {


  }
}

