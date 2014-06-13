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



#ifndef ADXL325_H_
#define ADXL325_H_

/* === Configuration === */
//#define __ADXL345_USE_APPROX__ // Uncomment if you doesn't want to assume, 1g equals 10 N/kg

/*
			
	To calculate the Acceleration, you can just simply play with a linear function 
								ƒ(x) = mx + b
				m is the scaling factor, it can be calculated by (32/2^13)*9.81 
					-32 stands for the +-16 g, that means 32 times the 
					-Gravity Constant on Earth (Don't think they use the Dead Star Gravity
					-Constant like it can be found in the Android SDK^^ 
					
					-2^13 is the 13-Bit ADC Resolution, so we use the Full Data Range the Sensor
					-is able to output.
				x is the RAW Accelerometer value
				b is the offset
				
				for our case, m is (32/2^13)*9.81 ~= 0.0383 
 */


/* ADXL345 specific defines */
#define ADXL345_ADDR 0x53
#define ADXL345_RANGE16G 0x03
#define ADXL345_FULLRANGE 1 
#define ADXL345_DATA_START 0x32
#define ADXL345_1G_9_81_ms2 0.0383f
#define ADXL345_1G_10_ms2 0.04f
#ifdef __ADXL345_USE_APPROX__ 
#define ADXL345_SCALING ADXL345_1G_10_ms2
#else
#define ADXL345_SCALING ADXL345_1G_9_81_ms2
#endif


#endif /* ADXL325_H_ */
