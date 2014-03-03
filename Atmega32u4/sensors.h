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
#define __USE_ADXL325__


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "twi.h"

#ifdef __USE_ITG3200__
#include "itg3200.h"
#endif

#ifdef __USE_ADXL325__
#include "adxl3245.h"
#endif



class __sensors {
public:
	__sensors();
	~__sensors();
	void update_all();
	
	uint8_t gyro_error;
	float gyro_x, gyro_y, gyro_z, gyro_temp;
	
	
private:

	/*Sensors*/
	#ifdef __USE_ITG3200__
	void init_itg3600();
	void update_data_itg3600();
	uint8_t itg3200_buffer[8];
	#endif
	
	
	/* Gyro */
	void calc_gyro_drift();
	float offset_gyro_y, offset_gyro_x, offset_gyro_z, gyro_avg_x_tmp, gyro_avg_y_tmp, gyro_avg_z_tmp;
	uint32_t offset_cntr;
};




#endif /* SENSORS_H_ */