
#ifdef F_CPU
#undef F_CPU
#endif

/* CLOCK FREQUENCY */

#define F_CPU 8000000UL 

#define CONCAT(a,b) a##b
#define DDR(a)		CONCAT(DDR,a)
#define PORT(a)		CONCAT(PORT,a)
#define PIN(a)		CONCAT(PIN,a)

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"port.h"


/* Do not change this three settings */

#define WATERLEVEL_DDR		   DDR(WATERLEVEL_ADDR)
#define WATERLEVEL_PORT		   PORT(WATERLEVEL_ADDR)
#define WATERLEVEL_PIN		   PIN(WATERLEVEL_ADDR)

#define WATERMOTOR_DDR		   DDR(WATERMOTOR_ADDR)
#define WATERMOTOR_PORT		   PORT(WATERMOTOR_ADDR)
#define WATERMOTOR_PIN		   PIN(WATERMOTOR_ADDR)

#define EXHAUSTMOTOR_DDR	   DDR(EXHAUSTMOTOR_ADDR)
#define EXHAUSTMOTOR_PORT	   PORT(EXHAUSTMOTOR_ADDR)
#define EXHAUSTMOTOR_PIN	   PIN(EXHAUSTMOTOR_ADDR)

#define FEEDMOTOR_DDR		   DDR(FEEDMOTOR_ADDR)
#define FEEDMOTOR_PORT		   PORT(FEEDMOTOR_ADDR)
#define FEEDMOTOR_PIN		   PIN(FEEDMOTOR_ADDR)

#define HEATER_DDR			   DDR(HEATER_ADDR)			
#define HEATER_PORT			   PORT(HEATER_ADDR)
#define HEATER_PIN			   PIN(HEATER_ADDR)

#define BUZZER_DDR			   DDR(BUZZER_ADDR)
#define BUZZER_PORT			   PORT(BUZZER_ADDR)
#define BUZZER_PIN			   PIN(BUZZER_ADDR)

#define LDR_DDR				   DDR(LDR_ADDR)
#define LDR_PORT			   PORT(LDR_ADDR)
#define LDR_PIN				   PIN(LDR_ADDR)

