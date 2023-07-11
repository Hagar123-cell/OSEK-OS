#include "Os_PBcfg.h"

uint32 task1Stack [STACKSIZE];
uint32 task2Stack [STACKSIZE];
uint32 task3Stack [STACKSIZE];
uint32 task4Stack [STACKSIZE];
uint32 task5Stack [STACKSIZE];


const  Task_ConfigType Task_Configuration = {
     task1Stack,STACKSIZE,Task1,EXTENDED,0,6,FULL,0,TRUE,
	 task2Stack,STACKSIZE,Task2,EXTENDED,0,2,NON,0,FALSE,
	 task3Stack,STACKSIZE,Task3,EXTENDED,0,3,FULL,0,FALSE,
	 task4Stack,STACKSIZE,Task4,BASIC,3,4,FULL,0,FALSE,
	 task5Stack,STACKSIZE,Task5,BASIC,2,5,FULL,0,FALSE
};

