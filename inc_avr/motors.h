/*
The MIT License (MIT)

Copyright (c) 2014 Matthias Riegler

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
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
