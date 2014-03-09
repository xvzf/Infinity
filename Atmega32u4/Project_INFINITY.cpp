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

#include "motors.h"
#include "IMU.h"
#include "communicate.h"

#include "WS2812.h"



void init_timer0_10ms() {
	TCCR0A |= (1<<WGM01); // Set CTC Mode
	OCR0A = 156; // 16 Mhz; Prescalor 1024 ==> Counts every 0.00064s ==> 0.01 / 0.0064 = 156.25 ==> OCR0A = 156
	TIMSK0 |= (1 << OCIE0A); // Set ISR COMPA 
	sei(); // Enable globale interupts
	TCCR0B |= (1<<CS02) | (1<<CS00); // set Prescaler 
}

__IMU sensors;


int main(void)
{
	WS2812 LED;
	
	LED.blue();
	
	__communicate communicate;
	__motors motors;
	motors.init_esc();
		
	LED.initializing();
	//motors.start_engines();
	LED.red();
	sensors.init();
	sensors.calibrate();
	LED.green();
	
	init_timer0_10ms();
	
    while(1)
    {	
		communicate.putfloat(sensors.pitch);communicate.putchar(',');
		communicate.putfloat(sensors.roll);communicate.putchar(',');
		communicate.putfloat(sensors.yaw);communicate.putchar('\n');
		_delay_ms(25);
    }
}


/* 100Hz update intervall */
ISR(TIMER0_COMPA_vect) {
	sensors.update();
}