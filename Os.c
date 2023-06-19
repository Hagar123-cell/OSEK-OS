#include "Os.h"

get_using_tasks x;

void StartOS(AppModeType mode)
{
	OsSched_schedulerInit();
	OsTask_taskInit(OsTask * OsTaskConfig);
	Alarm_init();
	Resource_init(x);
	Interrupt_init();
}

void ShutdownOS(void)
{
  DISABLE_INTERRUPTS();

  /* Kill all tasks */
  for(uint32 tcbIdx = 0; tcbIdx <= OSTASK_NUMBER_OF_TASKS; tcbIdx++)
  {
    OsSched_RunningToSuspended();
  }
  for(;;);
}