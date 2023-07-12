#include "Os_PBcfg.h"

uint32 task1Stack [STACKSIZE];
uint32 task2Stack [STACKSIZE];
uint32 task3Stack [STACKSIZE];


const  Task_ConfigType Task_Configuration = {
     task1Stack,STACKSIZE,Task1,BASIC,0,1,NON,0,TRUE,
	 task2Stack,STACKSIZE,Task2,EXTENDED,0,2,NON,0,FALSE,
	 task3Stack,STACKSIZE,Task3,BASIC,5,3,NON,0,TRUE
};

