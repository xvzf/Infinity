/*
 * sensors.cpp
 *
 * Created: 09.02.2014 12:54:45
 *  Author: Matthias Riegler
 */ 

#include "sensors.h"


__sensors::__sensors() {
	
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

void __sensors::calc_gyro_offset() {
	gyro_avg_x_tmp =  (gyro_avg_x_tmp + gyro_x);
	gyro_avg_y_tmp =  (gyro_avg_y_tmp + gyro_y);
	gyro_avg_z_tmp =  (gyro_avg_z_tmp + gyro_z);
	
	if( offset_cntr == CALC_OFFSET) {
		offset_gyro_x = gyro_avg_x_tmp / float(offset_cntr);
		offset_gyro_y = gyro_avg_y_tmp / float(offset_cntr);
		offset_gyro_z = gyro_avg_z_tmp / float(offset_cntr);
	}
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


 