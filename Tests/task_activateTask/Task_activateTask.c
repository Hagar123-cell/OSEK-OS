/******************************************************************************
 *
 * File Name: Task_activateTask.c
 *
 * Author: Peter Samir
 *
 * Description: Test ActivateTask API
 *
 * Scenario: priorities of tasks task3,task2 and task1 are 3,2 and 1 respectively, task1 is auto start so task1 will start execution,
 *           task1 call ActivateTask to activate task2 ,ActivateTask triggers rescheduling since Task1 is preemptable and switch context to task2 ,
 *           task2 call ActivateTask to activate task3 ,no scheduling take place after activating task3 since task2 is NON-Preemptive.
 *	     	 breakpoint at the super loop in task2 to print the TCB of task3 to show that all events are cleared and the state is ready .
 *******************************************************************************/
#include "Os.h"
#include "scheduler.h"
#define TASK1_ID 0
#define TASK2_ID 1
#define TASK3_ID 2


void riscv_context_switch(void);



int inTaskMum=0;
StatusType act;






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
	/*@OSEK_TASK_1
	The system service StatusType ActivateTask (TaskType TaskID) shall be defined. */
	/* tested by calling the API according to the prototype in the specs */
	
	/*@OSEK_TASK_3 	
	In ActivateTask API: The operating system shall ensure that the task code is being executed from the first statement. */
	/*tested by switching to Task2 and start execution from the first instruction */
	
	/*@OSEK_TASK_5 	
	In ActivateTask API:Rescheduling shall take place only if called from a preemptable task. */
	/*tested by calling ActivateTask from a preemptable task so Rescheduling take place and switch to Task2*/
	ActivateTask(TASK2_ID);


for(;;)
  {


  }
}

void Task2 (void)
{
	/*@OSEK_TASK_2 	
	In ActivateTask API: The task TaskID shall be transferred from the suspended state into the ready state. */
	/*tested by printing the TCB of task3 after activation using Qemu that shows the state of the task is ready*/
	
	/*@OSEK_TASK_5 	
	In ActivateTask API:Rescheduling shall take place only if called from a preemptable task. */
	/*tested by calling ActivateTask from a NOn-preemptable task so NO Rescheduling take place and NO switching to TasK3*/

	/*@OSEK_TASK_7 	
	In ActivateTask API: When an extended task is transferred from suspended state into ready state all its events are cleared. */
	/*tested by printing the TCB of task3 after activation using Qemu that shows the events that we have set manually are cleared*/
	
	OsTask_TCBs[TASK3_ID].Events.OsEventMaskX=6; /*to make sure events will be cleared after calling activate task*/
	OsTask_TCBs[TASK3_ID].EventsWait.OsEventMaskX=7; /*to make sure eventsWait will be cleared after calling activate task*/
	act=ActivateTask(TASK3_ID);

  for(;;)
  {


  }
}
void Task3 (void)
{
  inTaskMum=3;
  for(;;)
  {


  }
}



