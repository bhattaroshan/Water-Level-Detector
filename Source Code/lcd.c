
#include"lcd.h"

void wait_till_busy()
{
 
 uint8_t status;

 DDRD&=0x0F;

 HIGH(PORTD,RW);
 LOW(PORTD,RS);

 do
  {
  	HIGH(PORTD,E);
   	_delay_us(1);

   	status=(PIND&0xF0);

   	LOW(PORTD,E);
   	_delay_us(1);
   	HIGH(PORTD,E);
	
	status|=((PIND&0xF0)>>4);

	LOW(PORTD,E);
	_delay_us(1);
  
  }while(status & 0x80);
	
	DDRD|=0xF0;
}

void Send(uint8_t cmd,uint8_t isdata)
{ 
 
	uint8_t temp;
 
 	wait_till_busy();

 	LOW(PORTD,RW);

 	if(isdata)
  		HIGH(PORTD,RS);
 	else
  		LOW(PORTD,RS);
 
 	HIGH(PORTD,E);
 	_delay_us(1);

 	temp=PORTD&0x0F;
 	temp|=(cmd&0xF0);
 	PORTD=temp;

 	LOW(PORTD,E);
 	_delay_us(1);
 	HIGH(PORTD,E);

 	temp=PORTD&0x0F;
 	temp|=((cmd&0x0F)<<4);
 	PORTD=temp;

 	LOW(PORTD,E);

}

void initLCD(uint8_t flag)
{
 	_delay_ms(30);				//Wait for stable power supply

	PORTD=0x00;					//Make all output low
	DDRD=0xFF;					//Make all line output
	
	Send(0b00000010,0);			//Notify 4 bit mode
	_delay_us(100);				//wait for sometime, BF cannot determine at this stage

	Send(0b00101000,0);  		//DB4=0 4 bit mode, DB3=1 lines>=2, DB2=0 5x7 display
	_delay_us(100);				//wait here for sometime no need to wait here after

	Send(0b00001100|flag,0);  	//DB4=1 Display Control DB3=1 
								//Display on DB2=1 Cursor on
								//DB0=1 Blink On
	
	_delay_ms(10);
	initLCDCustomChar();
	LCDGotoXY(0,0);
}

void LCDGotoXY(uint8_t x,uint8_t y)
{
  	uint8_t temp=0x80;

  	if(y==1)
   		temp=0xC0;
	else if(y==2)
		temp=0x94;
	else if(y==3)
		temp=0xD4;
	
	Send(temp+x,0);
}

void LCDWriteString(char *szText)
{
	while(*szText)
	 Send(*szText++,1); 
}

void LCDWriteInt(uint16_t nNum,uint8_t nCount)
{
  uint8_t array[5]={0},iPos=0;
  int8_t i;
  
  while(nNum)
   {
    array[iPos]=nNum%10;
	nNum/=10;
	iPos++;
   }
  
  while(nCount--!=iPos)
      Send('0',1);

  for(i=iPos-1;i>=0;i--)
    Send('0'+array[i],1);

}

void initLCDCustomChar()
{
 Send(64,0);
 Send(0b00001110,1);
 Send(0b00010001,1);
 Send(0b00010001,1);
 Send(0b00001110,1);
 Send(0b00000000,1);
 Send(0b00000000,1);
 Send(0b00000000,1);
 Send(0b00000000,1);
}

void LCDWriteCustomChar(uint8_t uType)
{
 Send(uType,1);
}
