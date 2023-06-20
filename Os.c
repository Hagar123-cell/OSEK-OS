#include "Os.h"
#include "schedule.h"
get_using_tasks x;

void StartOS(AppModeType mode)
{
	OsSched_schedulerInit();
	OsTask_taskInit();
	Alarm_init();
	Resource_init(x);
	Interrupt_init();
	Ossched_StartScheduler();
}

void ShutdownOS(StatusType status)
{
  DISABLE_INTERRUPTS();

  /* Kill all tasks */
  for(uint32 tcbIdx = 0; tcbIdx <= OSTASK_NUMBER_OF_TASKS; tcbIdx++)
  {
    OsSched_RunningToSuspended();
  }
  for(;;);
}
