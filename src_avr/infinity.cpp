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

#include "infinity.h"


__IMU imu;
__motors motors;
WS2812 led;

void init_quadcopter()
{
    led.blue();
    motors.init_esc();
    led.initializing();
    //motors.start_engines();
    led.red();
    imu.init();
    imu.calibrate();

    init_timer0_10ms();
    /* Wait one second */
    _delay_ms(1000);
    imu.set_zero_point();
    led.green();

    motors.soft_start_engines();
    _delay_ms(1000);
    _delay_ms(1000);
    motors.soft_stop_engines();
}


void main_quadcopter()
{
    while(1) {


    }
}


void all10_quadcopter()
{
    imu.update();
}


void init_timer0_10ms()
{
    TCCR0A |= (1 << WGM01); // Set CTC Mode
    OCR0A = 156; // 16 Mhz; Prescalor 1024 ==> Counts every 0.00064s ==> 0.01 / 0.0064 = 156.25 ==> OCR0A = 156
    TIMSK0 |= (1 << OCIE0A); // Set ISR COMPA
    sei(); // Enable globale interupts
    TCCR0B |= (1 << CS02) | (1 << CS00); // set Prescaler
}
