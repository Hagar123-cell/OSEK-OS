/******************************************************************************
 *
 * File Name: task_GetTaskID.c
 *
 * Author: Peter Samir
 *
 * Description: Test GetTaskID API
 *
 * Scenario: task1 is auto start and start execution ,task1 call GetTaskID
 *	     breakpoint at the super loop in task1 to show the return value of GetTaskID on successful execution is E_OK.
 *           and show the returned information which is the running task ID
 *******************************************************************************/
#include "Os.h"
#include "scheduler.h"
#define TASK1_ID 0



void riscv_context_switch(void);

StatusType stat;
TaskType ID=20; 


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

  	/*@OSEK_TASK_34
	The system service StatusType GetTaskID (TaskRefType TaskID) shall be defined. */
	/* tested by calling the API according to the prototype in the specs */


	/*@OSEK_TASK_35
	In GetTaskID API: Shall returns the information about the TaskID of the task which is currently running. */
	/*tested by printing the returned information through Qemu that shows the ID of the calling task which will be 0 */


	/*@OSEK_TASK_37
	In GetTaskID API: This function always returns E_OK.*/
	/*tested by printing the returned status through Qemu that shows the status is  E_OK  */
        stat = GetTaskID(&ID);

for(;;)
  {


  }
}





