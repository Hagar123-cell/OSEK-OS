#include "timer.h"
#include "Alarm.h"
void timer_init(void)
{
	           
	SET_BIT(CNRTR,2);          // select mode
	SET_BIT(CNRTR,3);         /* select suitable prescalar
                            */
	CLR_BIT(CNRTR,4);
	return void;
}
void Enable_timer()
{
	SET_BIT(CNRTR,1);   
	/***********enable timer***************/
	return void;
}
void Disable_timer(void)
{
	
	CLR_BIT(CNRTR,1);
	/***********disable timer***************/
	return void;

}
}
void ISR(void)
{
	IncementCounter();
	return void;

}



