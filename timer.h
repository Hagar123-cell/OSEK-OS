#ifndef TIMER_H

#define TIMER_H_INCLUDED

#define CNTR        (*((volatile unsigned long *)0x00010000))
#define CMPR        (*((volatile unsigned long *)0x00010004))
#define CNTRR       (*((volatile unsigned long *)0x00010008))
#define INTERRUPT   (*((volatile unsigned long *)0x000100012))


#define SET_BIT(reg,bit)    reg|=(1<<bit)
#define CLR_BIT(reg,bit)    reg&=(~(1<<bit))


/*
	Function Name        : timer_init
	Function Returns     : void
	Function Arguments   : void
	Function Description : initialize the timer info ex: enable / disable, count down or up and so on.
*/

void timer_init(void);

/*
	Function Name        : compare
	Function Returns     : void
	Function Arguments   : void
	Function Description : fire an interrupt when the counter reach to the input value.
*/
void compare(int compare_value);


#endif // TIMER_H
