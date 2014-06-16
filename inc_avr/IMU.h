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


#ifndef IMU_H_
#define IMU_H_


#include "config.h"

#include "sensors.h"
#include <math.h>


class __IMU
{
public:
    __IMU();
    ~__IMU();

    void init();

    void calibrate();

    void update();
    void set_zero_point();


    float pitch, roll, yaw;
    float v_x, v_y, v_z;
    float v, mag_orientation;

private:

    __sensors sensors;

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
