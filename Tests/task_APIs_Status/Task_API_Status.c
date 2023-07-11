/*this test is used to check standard and extended errors in task management API 
as follow :
ActivateTask:
Standard: • No error, E_OK
	  • Too many task activations of <TaskID>, E_OS_LIMIT
Extended: • Task <TaskID> is invalid, E_OS_ID

TerminateTask:
Standard: No return to call level
Extended: • Task still occupies resources, E_OS_RESOURCE
          • Call at interrupt level, E_OS_CALLEVEL
          
ChainTask:
Standard: • No return to call level
	  • Too many task activations of <TaskID>, E_OS_LIMIT
Extended: • Task <TaskID> is invalid, E_OS_ID
	  • Calling task still occupies resources, E_OS_RESOURCE
       	  • Call at interrupt level, E_OS_CALLEVEL
       	  
Schedule:
Standard: • No error, E_OK
Extended: • Call at interrupt level, E_OS_CALLEVEL
	  • Calling task occupies resources, E_OS_RESOURCE     	  

GetTaskState:
Standard: • No error, E_OK
Extended: • Task <TaskID> is invalid, E_OS_ID
*/

#include "Os.h"
#include "scheduler.h"
#define TASK1_ID 0
#define TASK2_ID 1
#define TASK3_ID 2
#define TASK4_ID 3
#define TASK5_ID 4
#define NOT_VALID_ID 10

void riscv_context_switch(void);


void test_ActivateTask_errors(void);
void test_TerminateTask_errors(void);
void test_ChainTask_errors(void);
void test_Schedule_errors(void);
void test_GetTaskState_errors(void);

int inTaskMum=0;
StatusType act[8];
StatusType ter[2];
StatusType chain[5];
StatusType sched[2];





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

test_ActivateTask_errors();
test_TerminateTask_errors();
test_ChainTask_errors();
test_Schedule_errors();
test_GetTaskState_errors();
for(;;)
  {


  }
}

void Task2 (void)
{
  inTaskMum=2;
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
void Task4 (void)
{
  inTaskMum=4;
  for(;;)
  {


  }
}

void Task5 (void)
{
  inTaskMum=4;
  for(;;)
  {


  }
}



void test_ActivateTask_errors(void)
{
/* @OSEK_TASK_6 	
In ActivateTask API: If other than E_OK is returned the activation is ignored. */
 
 
	act[0]=ActivateTask(TASK2_ID);  /*successful activation of Extended task*/
	
	/* @OSEK_TASK_8 	
	In ActivateTask API: Possible return values in Standard mode are: E_OK if no errors E_OS_LIMIT if too many task activations of TaskID. */
	act[1]=ActivateTask(TASK2_ID);  /*return E_OS_LIMIT since the Extended task can't have multiple  activated  */  
					

	act[2]=ActivateTask(TASK4_ID);  /*successful activation of Basic task*/  
	act[3]=ActivateTask(TASK4_ID);  /* increment activation count to 1   */
	act[4]=ActivateTask(TASK4_ID);	/* increment activation count to 2   */
	act[5]=ActivateTask(TASK4_ID);  /* increment activation count to 3   */
	
	/* @OSEK_TASK_8 	
	In ActivateTask API: Possible return values in Standard mode are: E_OK if no errors E_OS_LIMIT if too many task activations of TaskID. */
	act[6]=ActivateTask(TASK4_ID);  /*return E_OS_LIMIT since this basic task can't be activated more than 3 times which is maximum activation for this task */


	/*@OSEK_TASK_9 	
	In ActivateTask API: Added possible return values in Extended mode is: E_OS_ID if the Task TaskID is invalid. */
	act[7]=ActivateTask(NOT_VALID_ID);  /*return E_OS_ID since the ID is invalid */

}

/*##################################################################################################*/
	/*TerminateTask*/

void test_TerminateTask_errors(void)
{
/*@OSEK_TASK_14 	
In TerminateTask API: If the version with extended status is used, the service returns in case of error, and provides a status which can be evaluated in the application. */


	OsTask_TCBs[TASK1_ID].Resources=5;/*assign Resource to a task manually before calling TerminateTask()*/
	
	/*@OSEK_TASK_17
	In TerminateTask API: Possibly return values in Extended mode are E_OS_RESOURCE if the Task still occupies resources, or E_OS_CALLEVEL if called at interrupt level.*/
	ter[0]=TerminateTask(); /*return E_OS_RESOURCE since task can't terminate if it's still occuping resources*/                  
	OsTask_TCBs[TASK1_ID].Resources=0;/*release Resources manaully*/
	
	
	OS_SET_CALL_LEVEL(ISR2_LEVEL);    /*set call level to ISR2_LEVEL*/
	/*@OSEK_TASK_17
	In TerminateTask API: Possibly return values in Extended mode are E_OS_RESOURCE if the Task still occupies resources, or E_OS_CALLEVEL if called at interrupt level.*/
	ter[1]=TerminateTask();	/*return E_OS_CALLEVEL since this API called only from task level*/	  			
	OS_SET_CALL_LEVEL(TASK_LEVEL);  /*set call level to TASK_LEVEL*/

}
/*##################################################################################################*/
void test_ChainTask_errors(void)
{
	/*@OSEK_TASK_28 	
	In ChainTask API: Added possible return values in Extended mode are:E_OS_ID if the TaskID is invalid,
	or E_OS_RESOURCE if the calling task still occupies resources, or 
        E_OS_CALLEVEL if call at interrupt level. */
	chain[0]=ChainTask(NOT_VALID_ID);    /*return E_OS_ID since the ID is invalid */      




	OsTask_TCBs[TASK1_ID].Resources=2; /*assign Resource to a task manually before calling ChainTask*/
	/*@OSEK_TASK_28 	
	In ChainTask API: Added possible return values in Extended mode are:E_OS_ID if the TaskID is invalid,
	or E_OS_RESOURCE if the calling task still occupies resources, or 
        E_OS_CALLEVEL if call at interrupt level. */
	chain[1]=ChainTask(TASK3_ID);       /*return E_OS_RESOURCE since task can't terminate if it's still occuping resources*/              
	OsTask_TCBs[TASK1_ID].Resources=0; /*release Resources manaully*/



	OS_SET_CALL_LEVEL(ISR2_LEVEL); /*set call level to ISR2_LEVEL*/
	/*@OSEK_TASK_28 	
	In ChainTask API: Added possible return values in Extended mode are:E_OS_ID if the TaskID is invalid,
	or E_OS_RESOURCE if the calling task still occupies resources, or 
        E_OS_CALLEVEL if call at interrupt level. */
	chain[2]=ChainTask(TASK3_ID); 	/*return E_OS_CALLEVEL since this API called only from task level*/				
	OS_SET_CALL_LEVEL(TASK_LEVEL);/*set call level to TASK_LEVEL*/

	/*@OSEK_TASK_26 	
	In ChainTask API: If E_OS_LIMIT is returned the activation is ignored. */
	/*@OSEK_TASK_27
	In ChainTask API: Possible return values in Standard mode are no returns if no errors E_OS_LIMIT if too many task activations of TaskID.*/ 
	chain[3]=ChainTask(TASK2_ID);  /*return E_OS_LIMIT since the Extended task can't have multiple  activated  */   

	/*@OSEK_TASK_26 	
	In ChainTask API: If E_OS_LIMIT is returned the activation is ignored. */
	/*@OSEK_TASK_27
	In ChainTask API: Possible return values in Standard mode are no returns if no errors E_OS_LIMIT if too many task activations of TaskID.*/ 
	chain[4]=ChainTask(TASK4_ID);    /*return E_OS_LIMIT since this basic task can't be activated more than 3 times which is maximum activation for this task */
}

/*##################################################################################################*/
void test_Schedule_errors(void)
{

	OsTask_TCBs[TASK1_ID].Resources=3;/*assign Resource to a task manually before calling Schedule()*/
	/*@OSEK_TASK_33 	
	In Schedule API: Extra possible return values in Extended mode are: 
	E_OS_CALLEVEL if call at interrupt level, or E_OS_RESOURCE if the calling task occupies resources. */
	sched[0]=Schedule();               /*return E_OS_RESOURCE since task can't call Schedule() if it's still occuping resources*/  
	OsTask_TCBs[TASK1_ID].Resources=0;/*release Resources manaully*/



	OS_SET_CALL_LEVEL(ISR2_LEVEL); /*set call level to ISR2_LEVEL*/
	/*@OSEK_TASK_33 	
	In Schedule API: Extra possible return values in Extended mode are: 
	E_OS_CALLEVEL if call at interrupt level, or E_OS_RESOURCE if the calling task occupies resources. */
	sched[1]=Schedule(); 	       /*return E_OS_CALLEVEL since this API called only from task level*/
	OS_SET_CALL_LEVEL(TASK_LEVEL);/*set call level to TASK_LEVEL*/
}

/*##################################################################################################*/
void test_GetTaskState_errors(void)
{
	TaskStateType stat;
	/*@OSEK_TASK_42 	
	In GetTaskState API: Extra possible return values in Extended mode is E_OS_ID if the Task TaskID is invalid. */
	act[7]=GetTaskState(NOT_VALID_ID, &stat);  /*return E_OS_ID since the ID is invalid */ 
}




