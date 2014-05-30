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
