/*
 * motors.h
 *
 * Created: 16.02.2014 10:57:42
 *  Author: Matthias Riegler
 */ 
#ifndef MOTORS_H_
#define MOTORS_H_

/*
 *		Motor Values from 0 to 500
 *
 *	ESC configured to accept 1450 to 2000 in this case
 *	Running Engines: 1500
 *
 *
 */
#define min_cmd 1450
#define max_cmd 2000
#define start_cmd 1500



#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define MFRONT_L COM3A1 // PB5 
#define MFRONT_R COM1A1 // PB6 
#define MBACK_L  COM1C1 // PB7 
#define MBACK_R  COM1B1 // PC6 


class __motors {
public:
	__motors();
	~__motors();	
	
	void init_esc();
	void start_engines();
	void soft_stop_engines();
	void emergency_stop_engines();
	void update();
	
	uint16_t FRONT_L;
	uint16_t FRONT_R;
	uint16_t BACK_L;
	uint16_t BACK_R; 
	
private: 
	
};



#endif /* MOTORS_H_ */