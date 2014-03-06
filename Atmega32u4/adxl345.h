/*
 * adxl325.h
 *
 * Created: 03.03.2014 12:15:36
 *  Author: Matthias Riegler
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