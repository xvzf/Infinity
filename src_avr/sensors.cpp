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

#include <avr/interrupt.h>

__sensors::__sensors()
{
}

void __sensors::init()
{

    /* Init Status LED */ 
    DDRE |= (1 << STATUS_LED);

    /* TWI Init */
    twi_init();
    _delay_ms(5);

#ifdef __USE_ITG3200__
    init_itg3600();
#endif

    _delay_ms(5);

#ifdef __USE_ADXL345__
    init_adxl345();
#endif

    _delay_ms(5);

#ifdef __USE_MPU6050__
    init_mpu6050();
#endif

    /* Variables */
    gyro_avg_x_tmp = 0; gyro_avg_y_tmp = 0; gyro_avg_z_tmp = 0;
    acc_avg_x = 0; acc_avg_y = 0; acc_avg_z = 0;

}

void __sensors::calibrate()
{
    offset_cntr = 0;
    /* Calculate drift */
    while (offset_cntr <= CALC_OFFSET)
    {
        update_all();
        calc_gyro_offset();
        //calc_acc_offset();
        offset_cntr++;
        _delay_ms(5);
    }
}

__sensors::~__sensors()
{

}


/*gather all sensor data*/
void __sensors::update_all()
{
    /* Toggle Status LED */
    PORTE |= (1 << STATUS_LED);

#ifdef __USE_ITG3200__
    update_data_itg3600();
#endif
#ifdef __USE_ADXL345__
    update_data_adxl345();
#endif
#ifdef __USE_MPU6050__
    update_data_mpu6050();
#endif
    /* Toggle Status LED */
    PORTE &=  ~(1 << STATUS_LED);
}

