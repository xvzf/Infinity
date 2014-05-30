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

#include "communicate.h"

#include <stdlib.h>

__communicate::__communicate() {
	
	/* Baud Rate */
	/*
	UBRR1H = UBRR_VAL >> 8;
	UBRR1L = UBRR_VAL & 0xFF;
	*/
	UBRR1 = UBRR_VAL;
	
	/* TX & RX Enable */
	UCSR1B |= (1<<TXEN1);
	UCSR1B |= (1<<RXEN1);
	
	
	/* Asynchrone 8N1 */
	UCSR1C |= (1<<USBS1) | (1<<UCSZ11) | (1<<UCSZ10);
	
}


__communicate::~__communicate() {
	
		
}

void __communicate::putbyte(uint8_t toput) {
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = toput;
}

void __communicate::putchar(int8_t toput) {
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = toput;
}

void __communicate::putstring(char* string) {
	while(*string) {
		putchar(*string);
		string++;
	}
}

void __communicate::putunsignedvalue(uint32_t toput) {
	char string[12];
	putstring(ultoa(toput,string,10));
}

void __communicate::putvalue(int32_t toput) {
	char string[12];
	putstring(ltoa(toput,string,10));
}

void __communicate::putfloat(float toput) {
	char string[12];
	putstring(dtostrf(toput,7,3,string));
}
