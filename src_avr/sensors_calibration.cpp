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


#include "sensors.h"

void __sensors::calc_gyro_offset()
{
    gyro_avg_x_tmp =  (gyro_avg_x_tmp + gyro_x);
    gyro_avg_y_tmp =  (gyro_avg_y_tmp + gyro_y);
    gyro_avg_z_tmp =  (gyro_avg_z_tmp + gyro_z);

    if ( offset_cntr == CALC_OFFSET)
    {
        offset_gyro_x = gyro_avg_x_tmp / float(offset_cntr);
        offset_gyro_y = gyro_avg_y_tmp / float(offset_cntr);
        offset_gyro_z = gyro_avg_z_tmp / float(offset_cntr);
    }
}

void __sensors::calc_acc_offset()
{
    acc_avg_x += acc_tmp_x;
    acc_avg_y += acc_tmp_y;
    acc_avg_z += acc_tmp_z;

    acc_avg_x /= 2;
    acc_avg_y /= 2;
    acc_avg_z /= 2;

    offset_acc_x = acc_avg_x;
    offset_acc_y = acc_avg_y;
    offset_acc_z = acc_avg_z - 9.81f;
}
