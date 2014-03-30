/*
 * Project_INFINITY.cpp
 *
 * Created: 09.02.2014 12:52:13
 *  Author: Matthias Riegler
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>


#include "motors.h"
#include "IMU.h"
#include "WS2812.h"


void init_timer0_10ms();
void init_quadcopter();


__IMU sensors;
__motors motors;
WS2812 LED;



int main(void)
{	
	
	init_quadcopter();
	
    while(1)
    {		
    }
}


/* 100Hz update intervall */
ISR(TIMER0_COMPA_vect) {
	sensors.update();
}

void init_quadcopter() {
	LED.blue();
	motors.init_esc();
	LED.initializing();
	//motors.start_engines();
	LED.red();
	sensors.init();
	sensors.calibrate();
	init_uart();
	init_timer0_10ms();
	/* Wait one second */
	_delay_ms(1000);/*
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);
	_delay_ms(100);*/
	sensors.set_zero_point();
	LED.green();
}

void init_timer0_10ms() {
	TCCR0A |= (1<<WGM01); // Set CTC Mode
	OCR0A = 156; // 16 Mhz; Prescalor 1024 ==> Counts every 0.00064s ==> 0.01 / 0.0064 = 156.25 ==> OCR0A = 156
	TIMSK0 |= (1 << OCIE0A); // Set ISR COMPA
	sei(); // Enable globale interupts
	TCCR0B |= (1<<CS02) | (1<<CS00); // set Prescaler
}
