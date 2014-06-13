/*
The MIT License (MIT)

Copyright (c) 2014 Matthias Riegler

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */ 



#include "sensors.h"


#ifdef __USE_ADXL345__

void __sensors::init_adxl345() {
	
	/* Configure range */
	twi_start(ADXL345_ADDR, TWI_WRITE);
	uint8_t range = ADXL345_RANGE16G | (ADXL345_FULLRANGE<<3); // Enable full Range -> 13-Bit ADC Resolution
	twi_write(0x31); twi_write(range);
	_delay_ms(10);
	
	/* Power register */
	twi_start(ADXL345_ADDR, TWI_WRITE);
	twi_write(0x2D); twi_write(0x00); // disable
	_delay_ms(10);
	twi_start(ADXL345_ADDR, TWI_WRITE);
	twi_write(0x2D); twi_write(0x16); // stand by
	_delay_ms(10);
	twi_start(ADXL345_ADDR, TWI_WRITE);
	twi_write(0x2D); twi_write(0x08); // enable
	_delay_ms(40);
	
	twi_stop();	
}

void __sensors::update_data_adxl345() {
		
	/* Reading into buffer with help of ACK doesn't seem to work, so the manual methode, 
	   should be fast enough, if anybody knows a solution - I'm happy to hear from you :) */	
	
	/* Read data */ 
	int16_t temp; // temp buffer
	// X
	twi_start(ADXL345_ADDR , TWI_WRITE);
	twi_write(0x32);
	twi_start(ADXL345_ADDR , TWI_READ);
	acc_tmp_x = twi_read_nack();
	twi_start(ADXL345_ADDR , TWI_WRITE);
	twi_write(0x32+1);
	twi_start(ADXL345_ADDR , TWI_READ);
	temp = twi_read_nack();
	acc_tmp_x += (temp<<8);
	
	// Y
	twi_start(ADXL345_ADDR , TWI_WRITE);
	twi_write(0x34);
	twi_start(ADXL345_ADDR , TWI_READ);
	acc_tmp_y = twi_read_nack();
	twi_start(ADXL345_ADDR , TWI_WRITE);
	twi_write(0x34+1);
	twi_start(ADXL345_ADDR , TWI_READ);
	temp = twi_read_nack();
	acc_tmp_y += (temp<<8);
		
	// Z
	twi_start(ADXL345_ADDR , TWI_WRITE);
	twi_write(0x36);
	twi_start(ADXL345_ADDR , TWI_READ);
	acc_tmp_z = twi_read_nack();
	twi_start(ADXL345_ADDR , TWI_WRITE);
	twi_write(0x36+1);
	twi_start(ADXL345_ADDR , TWI_READ);
	temp = twi_read_nack();
	acc_tmp_z += (temp<<8);
	twi_stop();
	
	/* Convert to m/s^2 */ 
	acc_x = (acc_tmp_x * ADXL345_SCALING) - offset_acc_x;
	acc_y = (acc_tmp_y * ADXL345_SCALING) - offset_acc_y;
	acc_z = (acc_tmp_z * ADXL345_SCALING) - offset_acc_z;
}
#endif
