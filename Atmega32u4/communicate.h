/*
 * communicate.h
 *
 * Created: 02.03.2014 14:21:04
 *  Author: Matthias Riegler
 */ 


#ifndef COMMUNICATE_H_
#define COMMUNICATE_H_

#include <avr/io.h>

#define F_CPU 16000000UL

#define UART_BAUD 115200

#define UBRR_VAL ((F_CPU + UART_BAUD*8) / (UART_BAUD*16)-1)


class __communicate {
public: 
	__communicate();
	~__communicate();	
	void putchar(int8_t toput);
	void putbyte(uint8_t toput);
	void putstring(char* string);
	void putvalue(int32_t toput);
	void putunsignedvalue(uint32_t toput);
	void putfloat(float toput);
	
};




#endif /* COMMUNICATE_H_ */