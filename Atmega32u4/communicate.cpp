/*
 * communicate.cpp
 *
 * Created: 02.03.2014 14:20:46
 *  Author: Matthias Riegler
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