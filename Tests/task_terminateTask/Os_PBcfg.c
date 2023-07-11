#include "Os_PBcfg.h"

uint32 task1Stack [STACKSIZE];
uint32 task2Stack [STACKSIZE];
uint32 IdleTaskStack [STACKSIZE];



const  Task_ConfigType Task_Configuration = {
     task1Stack,STACKSIZE,Task1,BASIC,4,1,FULL,0,TRUE,
     task2Stack,STACKSIZE,Task2,EXTENDED,0,2,NON,0,TRUE,
     IdleTaskStack,STACKSIZE,IdleTask,BASIC,0,0,FULL,0,TRUE
	 
};

