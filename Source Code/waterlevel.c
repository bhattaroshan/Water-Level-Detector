
#include"waterlevel.h"


uint8_t isWaterEmpty()
{
 if(!(WATERLEVEL_PIN & (1<<WATERLEVEL_DOWN_SENSOR)) && 
    !(WATERLEVEL_PIN & (1<<WATERLEVEL_UP_SENSOR)))
	return 1;
 
 return 0;
}

uint8_t isWaterFull()
{
 if((WATERLEVEL_PIN & (1<<WATERLEVEL_DOWN_SENSOR)) &&
    (WATERLEVEL_PIN & (1<<WATERLEVEL_UP_SENSOR)))
	return 1;

 return 0;
}
