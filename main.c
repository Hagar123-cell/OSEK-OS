#include "Os.h"

uint32 ledOn = 0 , ledToggle = 0;

static BLUE_LED_ON(void) 
{ 
    ledOn = 1;
}
static BLUE_LED_TOGGLE(void) 
{ 
    ledToggle = 1;
}

void Task1 (void)
{
  for(;;)
  {
    BLUE_LED_ON();  
    for(uint32 i=0; i<1000; i++);
    TerminateTask(Task1);
  }
}

void Task2 (void)
{
  for(;;)
  {
    BLUE_LED_TOGGLE();
    for(uint32 i=0; i<1000; i++);
    ActivateTask(Task1);
  }
}

int main()
{
    StartOS(OSDEFAULTAPPMODE);
}