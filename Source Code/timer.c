
#include"timer.h"

/*
 Don't use the variable until you know what they are for
*/

uint16_t overflowCounter=0;
volatile uint16_t nSecond=0,nFeedTime=0;


void startTimer()
{
 TCCR0=(1<<CS00);   //prescalar 1
 TIMSK=(1<<TOIE0);	//overflow interrupt enable

 sei();
}

uint16_t getFanTime()
{
 return nSecond;
}

uint16_t getFeedTime()
{
 return nFeedTime;
}

void resetFanTime()
{
 nSecond=0;
}

void resetFeedTime()
{
 nFeedTime=0;
}

ISR(TIMER0_OVF_vect) //TIMER0 overflow interrupt routine
{
 overflowCounter++;

 if(overflowCounter>31250) //this is only for 8Mhz
  {
   overflowCounter=0;
   nSecond++;
   nFeedTime++;
  }
}
