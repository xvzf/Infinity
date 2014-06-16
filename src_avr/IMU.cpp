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


#include "IMU.h"

#define IMU_PI 3.14f

__IMU::__IMU()
{

}

__IMU::~__IMU()
{

}

void __IMU::init() {
    angle_x_tmp = 0.00f;
    angle_y_tmp = 0.00f;
    angle_z_tmp = 0.00f;
}

void __IMU::calibrate() {
    sensors.calibrate();
}

void __IMU::set_zero_point()
{
    update();
    angle_x_zero = angle_x_tmp;
    angle_y_zero = angle_y_tmp;
    angle_z_zero = angle_z_tmp;
}

void __IMU::update()
{
    /* Get Sensor values */
    sensors.update_all();

#ifdef __USE_COMPLEMENTARY__
    complementary_filter();
#endif
}


#ifdef __USE_COMPLEMENTARY__
void __IMU::atan2_calc_angle_acc()
{

    /* Calculate angle with tan() function; radiants -> degrees */
    angle_x_acc = (atan2f(sensors.acc_y, sensors.acc_z) * 180) / IMU_PI;
    angle_y_acc = (atan2f(sensors.acc_x, sensors.acc_z) * 180) / IMU_PI;

}


float __IMU::normalize_acc_vector()
{
    return sqrtf(((sensors.acc_x * sensors.acc_x) + (sensors.acc_y * sensors.acc_y) + (sensors.acc_z * sensors.acc_z)));
}

void __IMU::integ_calc_angle_gyro()
{
    delta_angle_x_gyro = sensors.gyro_x * UPDATE_INTERVALL;
    delta_angle_y_gyro = sensors.gyro_y * UPDATE_INTERVALL;
    delta_angle_z_gyro = sensors.gyro_z * UPDATE_INTERVALL;
}

void __IMU::complementary_filter()
{

    atan2_calc_angle_acc();
    integ_calc_angle_gyro();

    angle_x_tmp += delta_angle_x_gyro;
    angle_y_tmp += delta_angle_y_gyro;
    angle_z_tmp += delta_angle_z_gyro;

    if ( normalize_acc_vector() < COMPLEMENTARY_MAX_ACC_NORMALIZED)
    {
        angle_x_tmp = ( angle_x_tmp * (1 - COMPLEMENTARY_ACC_INFLUENCE) ) + ( angle_x_acc * REVERSE_ACC_X * COMPLEMENTARY_ACC_INFLUENCE );
        angle_y_tmp = ( angle_y_tmp * (1 - COMPLEMENTARY_ACC_INFLUENCE) ) + ( angle_y_acc * REVERSE_ACC_Y * COMPLEMENTARY_ACC_INFLUENCE );
    }

    pitch = angle_x_tmp - angle_x_zero;
    roll = angle_y_tmp - angle_y_zero;
    yaw = angle_z_tmp - angle_z_zero;
}

#endif
