/*
 * Project_INFINITY.cpp
 *
 * Created: 09.02.2014 12:52:13
 *  Author: Matthias Riegler
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


#include "motors.h"
#include "sensors.h"
#include "communicate.h"


int main(void)
{
	__communicate communicate;
	__motors motors;
	__sensors sensors;
	
	sensors.update_all();
	
    while(1)
    {
		sensors.update_all();	
		communicate.putstring("Gyro Temp:"); communicate.putfloat(sensors.gyro_temp); communicate.putstring("°C\n");
		communicate.putstring("ACC X:"); communicate.putfloat(sensors.acc_x); communicate.putchar('\n');
		communicate.putstring("ACC Y:"); communicate.putfloat(sensors.acc_y); communicate.putchar('\n');
		communicate.putstring("ACC Z:"); communicate.putfloat(sensors.acc_z); communicate.putchar('\n');
		communicate.putstring("Gyro X:"); communicate.putfloat(sensors.gyro_x); communicate.putchar('\n');
		communicate.putstring("Gyro Y:"); communicate.putfloat(sensors.gyro_y); communicate.putchar('\n');
		communicate.putstring("Gyro Z:"); communicate.putfloat(sensors.gyro_z); communicate.putchar('\n');
		communicate.putchar('\n');
		communicate.putchar('\n');
		communicate.putchar('\n');
		communicate.putchar('\n');
		communicate.putchar('\n');
		communicate.putchar('\n');
		communicate.putchar('\n');
		_delay_ms(80);
    }
}

