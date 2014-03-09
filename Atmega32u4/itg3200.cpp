/*
 * itg3200.cpp
 *
 * Created: 06.03.2014 15:10:40
 *  Author: Matthias Riegler
 */ 

#include "sensors.h"

#ifdef __USE_ITG3200__

/* initialize ITG3600*/
void __sensors::init_itg3600() {
	
	/* Power Management */
	/*
	twi_start(ITG3200_ADDR,TWI_WRITE);
	twi_write(0x3E); twi_write(0x80);
	twi_stop();
	_delay_ms(10);
	*/
	
	twi_start(ITG3200_ADDR, TWI_WRITE);
	twi_write(0x15); twi_write(0x00);
	twi_stop();
	_delay_ms(10);
	
	/* Low Pass Filter */
	twi_start(ITG3200_ADDR,TWI_WRITE);
	twi_write(0x16); 
	//twi_write(0x18 + ITG3200_DLPF);
	twi_write(0x18);
	twi_stop();
	_delay_ms(10);
	
	/* Power Management */
	twi_start(ITG3200_ADDR,TWI_WRITE);
	twi_write(0x3E); twi_write(0x01); //twi_write(0x03);
	twi_stop();
	_delay_ms(10);
}

/*get data from ITG3600*/
void __sensors::update_data_itg3600() {
	
	
	twi_start(ITG3200_ADDR,TWI_WRITE);
	
	twi_write(ITG3200_TMP_H);
	
	gyro_error = twi_start(ITG3200_ADDR,TWI_READ);
	
	itg3200_buffer[0] = twi_read_ack();
	itg3200_buffer[1] = twi_read_ack();
	itg3200_buffer[2] = twi_read_ack();
	itg3200_buffer[3] = twi_read_ack();
	itg3200_buffer[4] = twi_read_ack();
	itg3200_buffer[5] = twi_read_ack();
	itg3200_buffer[6] = twi_read_ack();
	itg3200_buffer[7] = twi_read_nack();
	
	gyro_temp = (((itg3200_buffer[0] << 8 | itg3200_buffer[1]) + ITG3200_TEMP_OFFSET) /ITG3200_TEMP_SENSITIVITY) + ITG3200_TEMP_OFFSET_CELSIUS ;
	
	gyro_x = ((itg3200_buffer[2] << 8 | itg3200_buffer[3]) / ITG3200_SENSITIVITY) - offset_gyro_x;
	gyro_y = ((itg3200_buffer[4] << 8 | itg3200_buffer[5]) / ITG3200_SENSITIVITY) - offset_gyro_y;
	gyro_z = ((itg3200_buffer[6] << 8 | itg3200_buffer[7]) / ITG3200_SENSITIVITY) - offset_gyro_z;
	
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
#endif
