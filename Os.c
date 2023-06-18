#include "Os.h"
void StartOS(OSDEFAULTAPPMODE)
{
	OsSched_schedulerInit();
	OsTask_taskInit(OsTaskConfig);
	Interrupt_init();
	Alarm_init();
	Resource_init();
}