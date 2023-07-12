#include "Os_PBcfg.h"

uint32 task1Stack [STACKSIZE];



const  Task_ConfigType Task_Configuration = {
     task1Stack,STACKSIZE,Task1,EXTENDED,0,1,NON,0,TRUE
};

