/*
 * IMU.cpp
 *
 * Created: 07.03.2014 17:13:34
 *  Author: Matthias Riegler
 */ 

#include "IMU.h"

#define IMU_PI 3.14f
#define COMPLEMENTARY_MAX_ACC_NORMALIZED 12.00f // 12 m/s^2

__IMU::__IMU() {
	angle_x_tmp = 0.00f;
	angle_y_tmp = 0.00f;
	angle_z_tmp = 0.00f;
}

__IMU::~__IMU() {
	
	
}

void __IMU::set_zero_point() {
	update();
	angle_x_zero = angle_x_tmp;
	angle_y_zero = angle_y_tmp;
	angle_z_zero = angle_z_tmp;
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


float __IMU::normalize_acc_vector() {
	return sqrtf(((acc_x*acc_x) + (acc_y*acc_y) + (acc_z*acc_z)));
}

void __IMU::integ_calc_angle_gyro() {
	delta_angle_x_gyro = gyro_x * UPDATE_INTERVALL;
	delta_angle_y_gyro = gyro_y * UPDATE_INTERVALL;
	delta_angle_z_gyro = gyro_z * UPDATE_INTERVALL;
}

void __IMU::complementary_filter() {
	
	atan2_calc_angle_acc();
	integ_calc_angle_gyro();
	
	angle_x_tmp += delta_angle_x_gyro;
	angle_y_tmp += delta_angle_y_gyro;
	angle_z_tmp += delta_angle_z_gyro;
	
	if( normalize_acc_vector() < COMPLEMENTARY_MAX_ACC_NORMALIZED) {
		angle_x_tmp = ( angle_x_tmp * (1-COMPLEMENTARY_ACC_INFLUENCE) ) + ( angle_x_acc * REVERSE_ACC_X * COMPLEMENTARY_ACC_INFLUENCE ); 
		angle_y_tmp = ( angle_y_tmp * (1-COMPLEMENTARY_ACC_INFLUENCE) ) + ( angle_y_acc * REVERSE_ACC_Y * COMPLEMENTARY_ACC_INFLUENCE );
	}
	
	pitch = angle_x_tmp - angle_x_zero;
	roll = angle_y_tmp - angle_y_zero;
	yaw = angle_z_tmp - angle_z_zero;
}

#endif