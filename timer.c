#include "timer.h"
#include "alarm.h"
void timer_init(void)
{
	SET_BIT(CNRTR,1);           //enable timer
	SET_BIT(CNRTR,2);          // select mode
	SET_BIT(CNRTR,3);         /* select suitable prescalar
                            */
	CLR_BIT(CNRTR,4);
	return void;
}
void compare(int compare_value)
{
    if(compare_value == CNT)
    {
        INTERRUPT = 1;
    }
    else
    {
        //no thing
    }

}
void ISR(void)
{
	IncementCounter();
	return void;

}



