#include "Os.h"

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
    TerminateTask();
  }
}

void Task2 (void)
{
  for(;;)
  {
    BLUE_LED_TOGGLE();
    for(uint32 i=0; i<1000; i++);
    ActivateTask(0);
  }
}

int main()
{
    StartOS(OSDEFAULTAPPMODE);
}