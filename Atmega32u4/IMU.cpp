/*
 * IMU.cpp
 *
 * Created: 07.03.2014 17:13:34
 *  Author: Matthias Riegler
 */ 

#include "IMU.h"

#define IMU_PI 3.14f


__IMU::__IMU() {
		
}

__IMU::~__IMU() {
	
	
}


void __IMU::update() {
	/* Get Sensor values */
	update_all();
	
	#ifdef __USE_COMPLEMENTARY__
	complementary_filter();
	#endif
}


#ifdef __USE_COMPLEMENTARY__
void __IMU::atan2_calc_angle_acc() {
	
	/* Calculate angle with tan() function; radiants -> degrees */
	angle_x_acc = (atan2f(acc_y, acc_z) * 180) / IMU_PI;
	angle_y_acc = (atan2f(acc_x, acc_z) * 180) / IMU_PI;
	
}

void __IMU::integ_calc_angle_gyro() {
	delta_angle_x_gyro = gyro_x * UPDATE_INTERVALL;
	delta_angle_y_gyro = gyro_y * UPDATE_INTERVALL;
	delta_angle_z_gyro = gyro_z * UPDATE_INTERVALL;
}

void __IMU::complementary_filter() {
	atan2_calc_angle_acc();
	integ_calc_angle_gyro();
	
	angle_x += delta_angle_x_gyro;
	angle_y += delta_angle_y_gyro;
	angle_z += delta_angle_z_gyro;
	
	
	angle_x = ( angle_x * (1-COMPLEMENTARY_ACC_INFLUENCE) ) + ( angle_x_acc * REVERSE_ACC_X * COMPLEMENTARY_ACC_INFLUENCE ); 
	angle_y = ( angle_y * (1-COMPLEMENTARY_ACC_INFLUENCE) ) + ( angle_y_acc * REVERSE_ACC_Y * COMPLEMENTARY_ACC_INFLUENCE );

	pitch = angle_x;
	roll = angle_y;
	yaw = angle_z;
}

#endif