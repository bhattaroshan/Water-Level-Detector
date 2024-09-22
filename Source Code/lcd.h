
#include"defination.h"

#define DEGREE 0

#define RS PD0
#define RW PD1
#define E  PD2

#define HIGH(PORT,PIN) PORT|=(1<<PIN)
#define LOW(PORT,PIN) PORT&=~(1<<PIN)

#define LCDClear() Send(1,0)

void wait_till_busy();
void Send(uint8_t cmd,uint8_t isdata);
void initLCD(uint8_t flag);
void LCDGotoXY(uint8_t x,uint8_t y);
void LCDWriteString(char *szText);
void LCDWriteInt(uint16_t nNum,uint8_t nCount);
void initLCDCustomChar();
void LCDWriteCustomChar(uint8_t uType);
