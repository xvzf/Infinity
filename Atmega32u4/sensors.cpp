/*
 * sensors.cpp
 *
 * Created: 09.02.2014 12:54:45
 *  Author: Matthias Riegler
 */ 

#include "sensors.h"

#include <avr/interrupt.h>

__sensors::__sensors() {
}

void __sensors::init() {
	
	/* Init Status LED */
	DDRE |= (1<<STATUS_LED);
	
	/* TWI Init */
	twi_init();
	_delay_ms(5);
	
	#ifdef __USE_ITG3200__
	init_itg3600();
	#endif
	
	#ifdef __USE_ADXL345__
	init_adxl345();
	#endif
	
	/* Variables */
	gyro_avg_x_tmp = 0; gyro_avg_y_tmp = 0; gyro_avg_z_tmp = 0;
	acc_avg_x = 0; acc_avg_y = 0; acc_avg_z = 0;
	
}

void __sensors::calibrate() {
	offset_cntr = 0;
	/* Calculate drift */
	while(offset_cntr <= CALC_OFFSET) {
		update_all();
		calc_gyro_offset();
		//calc_acc_offset();
		offset_cntr++;
		_delay_ms(5);
	}
}

__sensors::~__sensors() {
	
}


/*gather all sensor data*/
void __sensors::update_all() {
	/* Toggle Status LED */
	PORTE |= (1<<STATUS_LED);
	
	#ifdef __USE_ITG3200__
	update_data_itg3600();
	#endif
	
	#ifdef __USE_ADXL345__
	update_data_adxl345();
	#endif
	
	
	/* Toggle Status LED */
	PORTE &=  ~(1<<STATUS_LED);
}

