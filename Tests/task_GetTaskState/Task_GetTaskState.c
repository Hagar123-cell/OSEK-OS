/******************************************************************************
 *
 * File Name: task_GetTaskState.c
 *
 * Author: David Samir
 *
 * Description: Test GetTaskState API
 *
 * Scenario: priorities of tasks task3,task2 and task1 are 3,2 and 1 respectively, task3 and task1 are auto start so task3 will start execution,
 *           task3 call GetTaskState 3 times to get the state of the 3 tasks then activate task3 2 times and call GetTaskState to show the state of  
 *	     task3 when it has multiple activtion.
 *	     breakpoint at the super loop in task3 to show the return value of GetTaskState on successful execution is E_OK,
 *	     the returned states after calling GetTaskState for the 3 tasks
 *******************************************************************************/
#include "Os.h"
#include "scheduler.h"
#define TASK1_ID 0
#define TASK2_ID 1
#define TASK3_ID 2


void riscv_context_switch(void);

TaskStateType state_of_task1;
TaskStateType state_of_task2;
TaskStateType state_of_task3;
TaskStateType state_of_task3_3;

StatusType stat;

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
	/*@OSEK_TASK_38
	The system service StatusType GetTaskState (TaskType TaskID, TaskStateRefType State) shall be defined.*/
	/* tested by calling the API according to the prototype in the specs */


	/*OSEK_TASK_39
	In GetTaskState API: The service shall return the state of a task (running, ready, waiting, suspended)
	at the time of calling GetTaskState. */
        /*tested by calling GetTaskState for 3 different tasks and print the returned state through Qemu*/

	/*@OSEK_TASK_40
	In GetTaskState API: When the service is called for a task, which is activated more than once,
	the state is set to running if any instance of the task is running. */
        /* tested by activating task3 which is the running task more than one time then call GetTaskState
        and print the returned state through Qemu */


	/*@OSEK_TASK_41
	In GetTaskState API: Possible return values in Standard mode is E_OK */
	/*tested by printing the status after calling GetTaskState */



  GetTaskState(TASK1_ID, &state_of_task1); /*Get the state of task1 which is ready since it's auto start task*/
  GetTaskState(TASK2_ID, &state_of_task2); /*Get the state of task2 which is suspened */
  stat=GetTaskState(TASK3_ID, &state_of_task3); /*Get the state of task3 which is running */

 ActivateTask(TASK3_ID);
 ActivateTask(TASK3_ID); /*multiple activation of task3 to test that the state is set to running if any instance of the task is running.  */
 
   GetTaskState(TASK3_ID, &state_of_task3_3); /*Get the state of task3 which is running and has multiple activation */
  for(;;)
  {


  }
}



