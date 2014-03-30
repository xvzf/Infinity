/*
 * sensors.h
 *
 * Created: 09.02.2014 12:54:57
 *  Author: Matthias Riegler
 */ 


#ifndef SENSORS_H_
#define SENSORS_H_

#define SENSORS_ERROR TWI_ERROR
#define SENSORS_SUCCESS TWI_SUCCESS


#define  CALC_OFFSET 800 
#define STATUS_LED PE6


#define __USE_ITG3200__
#define __USE_ADXL345__

/*
#define __USE_MPU6050__
*/

#define F_CPU 16000000UL
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