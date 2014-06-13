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

#ifndef SENSORS_H_
#define SENSORS_H_

#include "config.h"

#define SENSORS_ERROR TWI_ERROR
#define SENSORS_SUCCESS TWI_SUCCESS

#include <avr/io.h>
#include <util/delay.h>
#include "twi.h"

#ifdef __USE_ITG3200__
#include "itg3200.h"
#endif

#ifdef __USE_ADXL345__
#include "adxl345.h"
#endif



class __sensors {
public:
	__sensors();
	~__sensors();
	
	void init();
	
	void calibrate();
	void update_all();
	
	uint8_t gyro_error;
	float gyro_x, gyro_y, gyro_z, gyro_temp;
	float acc_x, acc_y, acc_z;
	
private:

	/*Sensors*/
	
	/* ITG3200 */
	#ifdef __USE_ITG3200__
	void init_itg3600();
	void update_data_itg3600();
	uint8_t itg3200_buffer[8];
	#endif
	
	/* ADXL345 */
	#ifdef __USE_ADXL345__
	void init_adxl345();
	void update_data_adxl345();
	uint8_t adxl345_buffer[6];
	#endif
	
	
	/* MPU6050 */
	#ifdef __USE_MPU6050__
	void init_mpu6050();
	void update_data_mpu6050();
	uint8_t buffer[14];
	#endif
	
	/* MISC */
	uint32_t offset_cntr;
	
	/* ACC */
	float offset_acc_x, offset_acc_y, offset_acc_z, acc_avg_x, acc_avg_y, acc_avg_z;
	int16_t acc_tmp_x, acc_tmp_y, acc_tmp_z;
	void calc_acc_offset();
	
	/* Gyro */
	void calc_gyro_offset();
	float offset_gyro_y, offset_gyro_x, offset_gyro_z, gyro_avg_x_tmp, gyro_avg_y_tmp, gyro_avg_z_tmp;
	
};




#endif /* SENSORS_H_ */
