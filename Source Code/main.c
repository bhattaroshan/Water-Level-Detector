
/********************************************************/
/*														*/
/*													    */
/*		   PLEASE USE PORT.H FOR CONFIGURATION		    */
/*														*/
/*														*/
/********************************************************/

#include"defination.h"
#include"temperature.h"
#include"lcd.h"
#include"timer.h"
#include"waterlevel.h"

int main()
{
 
 
 uint8_t  iTemp;
 uint8_t  iExhaustFanOn=0;
 uint8_t  iFeedMotorOn=0;
 uint16_t iFeedVarier=300;

 /******************************************************/
 /*												   	   */
 /*					  INITIALIZATION				   */	
 /*													   */
 /******************************************************/

 _delay_ms(20);  	//wait for some voltage jerks

 HEATER_DDR|=(1<<HEATER_PIN_NUMBER);
 HEATER_PORT&=~(1<<HEATER_PIN_NUMBER);

 WATERLEVEL_DDR&=~((1<<WATERLEVEL_UP_SENSOR)|(1<<WATERLEVEL_DOWN_SENSOR));
 WATERLEVEL_PORT|=(1<<WATERLEVEL_UP_SENSOR)|(1<<WATERLEVEL_DOWN_SENSOR); 
 
 WATERMOTOR_DDR|=(1<<WATERMOTOR_PIN_NUMBER);
 WATERMOTOR_PORT&=~(1<<WATERMOTOR_PIN_NUMBER);

 EXHAUSTMOTOR_DDR|=(1<<EXHAUSTMOTOR_PIN_NUMBER);
 EXHAUSTMOTOR_PORT&=~(1<<EXHAUSTMOTOR_PIN_NUMBER);
 
 FEEDMOTOR_DDR|=(1<<FEEDMOTOR_PIN_NUMBER);
 FEEDMOTOR_PORT&=~(1<<FEEDMOTOR_PIN_NUMBER);
 
 BUZZER_DDR|=(1<<BUZZER_PIN_NUMBER);
 BUZZER_PORT|=(1<<BUZZER_PIN_NUMBER);
 
 LDR_DDR&=~(1<<LDR_PIN_NUMBER);
 LDR_PORT&=~(1<<LDR_PIN_NUMBER);

 initADC(); 	 	//init ADC
 initLCD(0);		//InitLCD
 _delay_ms(50);  	//wait for ADC and LCD warmup
 LCDClear();

 startTimer();	 	//start timer0

 //NEVER ENDING LOOPING

 while(1)
  {
   
   /******************************************************/
   /*												   	 */
   /*					  LIGHT    						 */	
   /*													 */
   /******************************************************/

	if(LDR_PIN&(1<<LDR_PIN_NUMBER))
	 {
	  BUZZER_PORT|=(1<<BUZZER_PIN_NUMBER);	  
	 }
   else
     {
	  BUZZER_PORT&=~(1<<BUZZER_PIN_NUMBER);	  
	 }

   /******************************************************/
   /*												   	 */
   /*					  TEMPERATURE					 */	
   /*													 */
   /******************************************************/

   iTemp=getTemperature(); //temperature in celcius
   LCDGotoXY(0,0);
   LCDWriteString("Temperature:");
   LCDWriteInt(iTemp,2);
   LCDWriteCustomChar(DEGREE);
   LCDWriteString("C");





   /******************************************************/
   /*												   	 */
   /*						HEATER						 */	
   /*													 */
   /******************************************************/

   if(iTemp>0 && iTemp<36)
    {
	 //heater on...
	 HEATER_PORT|=(1<<HEATER_PIN_NUMBER);
	}
   else
    {
	 //heater off...
	 HEATER_PORT&=~(1<<HEATER_PIN_NUMBER);
	}

   /******************************************************/
   /*												   	 */
   /*					WATER TANK						 */	
   /*													 */
   /******************************************************/
	
	if(isWaterEmpty())
	 {
	  //start the water motor
	  WATERMOTOR_PORT|=(1<<WATERMOTOR_PIN_NUMBER);
	 }
	else if(isWaterFull())
	 {
	  //stop the water motor
	  WATERMOTOR_PORT&=~(1<<WATERMOTOR_PIN_NUMBER);
	 }


   /******************************************************/
   /*												   	 */
   /*				EXHAUST FAN							 */	
   /*													 */
   /******************************************************/

   if(getFanTime()>=600 && iExhaustFanOn==0) //10 minute past
    {

	 //start the fan motor
	 EXHAUSTMOTOR_PORT|=(1<<EXHAUSTMOTOR_PIN_NUMBER);

	 iExhaustFanOn=1;    //need to be off now
	 resetFanTime();    //reset fan timer
	}
   else if(getFanTime()>=60 && iExhaustFanOn==1) //1 minute past
    {
		 
	 //stop the fan motor
	 EXHAUSTMOTOR_PORT&=~(1<<EXHAUSTMOTOR_PIN_NUMBER);

	 iExhaustFanOn=0;
	 resetFanTime();  //reset fan timer
	}
   
   
   /******************************************************/
   /*												   	 */
   /*				    FEED MOTOR						 */	
   /*													 */
   /******************************************************/


   if(getFeedTime()>=iFeedVarier && iFeedMotorOn==0) //5 min or 3 sec
    {
	 
	 FEEDMOTOR_PORT|=(1<<FEEDMOTOR_PIN_NUMBER);
	 
	 iFeedMotorOn=1;
	 resetFeedTime();
     
	 if(iFeedVarier==300)
	  iFeedVarier=1; //switch back to 1 sec
	 else
	  iFeedVarier=300; //switch back to 5 min
	}

   else if(getFeedTime()>=1 && iFeedMotorOn==1) //1 sec on
    {
	 
	 FEEDMOTOR_PORT&=~(1<<FEEDMOTOR_PIN_NUMBER);

	 iFeedMotorOn=0;
	 resetFeedTime();
	}

  }

 return 0;
}
