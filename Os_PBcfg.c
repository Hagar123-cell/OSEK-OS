#include "Os.h"

#define no_of_tasks 2
#define STACKSIZE 240

uint32 task1Stack [STACKSIZE];
uint32 task2Stack [STACKSIZE];

void Task1 (void);
void Task2 (void);

typedef struct Task_ConfigType
{
	OsTask tasksConfig[no_of_tasks];
} Task_ConfigType;

const Task_ConfigType Task_Configuration = {
    { task1Stack,STACKSIZE,Task1,EXTENDED,0,2,FULL,0,TRUE},
	{ task2Stack,STACKSIZE,Task2,EXTENDED,0,1,FULL,0,TRUE}
};

