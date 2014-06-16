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

#ifndef CONFIG_H_
#define CONFIG_H_


/* ======== AVR ======== */
#define F_CPU 16000000UL

/* ======== Sensors ======== */
#define  CALC_OFFSET 800
#define STATUS_LED PE6
#define __USE_ITG3200__
#define __USE_ADXL345__
//#define __USE_MPU6050__

/* ======= IMU ======= */
#define UPDATE_INTERVALL 0.01
#define  __USE_COMPLEMENTARY__
#define COMPLEMENTARY_MAX_ACC_NORMALIZED 12.00f // 12 m/s^2


/* ======== Communicate ======== */
#define UART_BAUD 115200
#define COMMUNICATE_UART_REC_BUFFER 50


/* ======== Motors ======== */
/*
 *      Motor Values from 0 to 500
 *
 *  ESC configured to accept 1450 to 2000 in this case
 *  Running Engines: 1500
 *
 *
 */
#define min_cmd 1450
#define max_cmd 2000
#define start_cmd 1500

#define MFRONT_L COM3A1 // PB5 
#define MFRONT_R COM1A1 // PB6 
#define MBACK_L  COM1C1 // PB7 
#define MBACK_R  COM1B1 // PC6 

/* ======= define resolve ======= */
#ifdef __USE_COMPLEMENTARY__
/* Complementary Filter Settings */
#define COMPLEMENTARY_ACC_INFLUENCE 0.02 // 2 Percent - Have to be tuned!
#define REVERSE_ACC_X 1 // 1 for no reverse
#define REVERSE_ACC_Y -1 // 1 for no reverse
#endif


#endif /* CONFIG_H_ */
