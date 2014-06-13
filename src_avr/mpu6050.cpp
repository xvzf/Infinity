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
#include "mpu6050.h"

#ifdef __USE_MPU6050__

void __sensors::init_mpu6050() {
	
	/* Wake up device */
	twi_start(MPU6050_ADDR, TWI_WRITE);
	twi_write(MPU6050_POWER_MGR1);
	twi_write(0x00);
	twi_stop();
	_delay_ms(10);
	
	// 256Hz Low Pass Filter
	twi_start(MPU6050_ADDR, TWI_WRITE);
	twi_write(MPU6050_DLPF);
	twi_write(0x00);
	twi_stop();
	_delay_ms(10);
	
	// 2000°/s
	twi_start(MPU6050_ADDR, TWI_WRITE);
	twi_write(MPU6050_GYRO_RANGE);
	twi_write(0x18);
	twi_stop();
	_delay_ms(10);
	
	// +/- 8G
	twi_start(MPU6050_ADDR, TWI_WRITE);
	twi_write(MPU6050_ACC_RANGE);
	twi_write(0x10);
	twi_stop();	
	_delay_ms(10);

}


void __sensors::update_data_mpu6050() {
	
	
	
}

#endif
