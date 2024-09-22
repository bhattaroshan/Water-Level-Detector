
#include"temperature.h"

void initADC()
{
  ADMUX=(1<<REFS0)|(1<<REFS1);                       // For Aref=AVcc;
  ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128
}

uint16_t readADC(uint8_t ch)
{
   ADMUX&=0b11110000;
   ch=ch&0b00000111;
   ADMUX|=ch;

   ADCSRA|=(1<<ADSC);

   while(!(ADCSRA & (1<<ADIF)));

   ADCSRA|=(1<<ADIF);

   return(ADC);
}

uint8_t getTemperature()
{
 uint8_t temp;
 
 temp=readADC(ADC_TEMPERATURE_PIN);

 // 1023---2.56v
 // 1adc--- (2.56*1000)/1023 mV
 // temp adc -- 2.56*1000*temp)/(10230)

 return temp/4;

}
