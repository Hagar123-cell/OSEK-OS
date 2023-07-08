#include "Os.h"
#define TASK1_ID 0
#define TASK2_ID 1

uint32 ledOn = 0 , ledToggle = 0;

static void BLUE_LED_ON(void) 
{ 
    ledOn = 1;
}
static void BLUE_LED_TOGGLE(void) 
{ 
    ledToggle = 1;
}

void Task1 (void)
{
  for(;;)
  {
    BLUE_LED_ON();  
    for(uint32 i=0; i<1000; i++);
    ActivateTask(TASK2_ID);
  }
}

void Task2 (void)
{
  for(;;)
  {
    BLUE_LED_TOGGLE();
    for(uint32 i=0; i<1000; i++);
    TerminateTask();
  }
}

int main()
{
    StartOS(OSDEFAULTAPPMODE);
}
