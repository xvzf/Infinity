/*
 * IMU.h
 *
 * Created: 07.03.2014 17:12:14
 *  Author: Matthias Riegler
 *
 *	The IMU for this project will be based on the complementary filter
 *
 */ 


#ifndef IMU_H_
#define IMU_H_

#include "sensors.h"
#include <math.h>


/* 100 Hz Update intervall, needed to calculate gyro angle */
#define UPDATE_INTERVALL 0.01 

/* === Complementary Filter === */
#define  __USE_COMPLEMENTARY__ // Uncomment to enable Complementary Filter
#ifdef __USE_COMPLEMENTARY__
/* Complementary Filter Settings */
#define COMPLEMENTARY_ACC_INFLUENCE 0.02 // 2 Percent - Have to be tuned!
#define REVERSE_ACC_X 1 // 1 for no reverse
#define REVERSE_ACC_Y -1 // 1 for no reverse
#endif

class __IMU: public __sensors {
public:
	__IMU();
	~__IMU();	
	void update();
	void set_zero_point();
	
	
	float pitch, roll, yaw;
	float v_x, v_y, v_z;
	float v, mag_orientation;

private:
	#ifdef __USE_COMPLEMENTARY__
	float angle_x_acc, angle_y_acc;
	float delta_angle_x_gyro, delta_angle_y_gyro, delta_angle_z_gyro;
	float angle_x_zero, angle_y_zero, angle_z_zero;
	float angle_x_tmp, angle_y_tmp, angle_z_tmp;
	void complementary_filter();
	void atan2_calc_angle_acc();
	void integ_calc_angle_gyro();
	float normalize_acc_vector();
	#endif
};




#endif /* IMU_H_ */