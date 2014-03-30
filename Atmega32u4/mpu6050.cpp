/*
 * mpu6050.cpp
 *
 * Created: 28.03.2014 13:12:47
 *  Author: Matthias
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