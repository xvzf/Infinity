/*
 * adxl345.cpp
 *
 * Created: 06.03.2014 15:11:44
 *  Author: Matthias Riegler
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

void __sensors::calc_acc_offset() {
	acc_avg_x =  (acc_avg_x + acc_tmp_x);
	acc_avg_y =  (acc_avg_y + acc_tmp_y);
	acc_avg_z =  (acc_avg_z + acc_tmp_z);
	
	if(offset_cntr == CALC_OFFSET) {
		offset_acc_x = acc_avg_x / float(offset_cntr);
		offset_acc_y = acc_avg_y / float(offset_cntr);
		offset_acc_z = acc_avg_z / float(offset_cntr); // -1 * ((acc_avg_y / float(offset_cntr)) - 9.81);
	}
}

#endif