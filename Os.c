#include "Os.h"
#include "scheduler.h"
get_using_tasks x;

void StartOS(AppModeType mode)
{
	OsSched_schedulerInit();
	OsTask_taskInit();
#ifndef TEST	
	Alarm_init();
	Resource_init(x);
	Interrupt_init();
#endif 
	Ossched_StartScheduler();
}

void ShutdownOS(StatusType status)
{
#ifndef TEST
  DISABLE_INTERRUPTS();
#endif 
  /* Kill all tasks */
  for(uint32 tcbIdx = 0; tcbIdx <= OSTASK_NUMBER_OF_TASKS; tcbIdx++)
  {
    OsSched_RunningToSuspended();
  }
  for(;;);
}
