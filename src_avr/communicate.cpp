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

#include "communicate.h"

#include <stdlib.h>

#include <avr/interrupt.h>


/*  Set to 1 if String is received completely */
volatile uint8_t uart_str_rec_complete = 0;
/* Counts the total number of received characters */
volatile uint8_t uart_str_rec_count = 0;
/* FIFO Buffer to store the received chars */
volatile char buffer[COMMUNICATE_UART_REC_BUFFER + 1] = "";

uart_cmd received_command;
uint8_t readyfornewcommand = 1; /* 1 if ready */


__communicate::__communicate() {
	
	/* Baud Rate */
	/*
	UBRR1H = UBRR_VAL >> 8;
	UBRR1L = UBRR_VAL & 0xFF;
	*/

	lastcommand = &received_command;

	/* 16-bit register available */
	UBRR1 = UBRR_VAL; 
	
	/* TX & RX Enable */
	UCSR1B |= (1<<TXEN1);
	UCSR1B |= (1<<RXEN1);


	/* Enable Rx interrupt */
	UCSR1B |= (1<<RXCIE1);
	
	/* Asynchrone 8N1 */
	UCSR1C |= (1<<USBS1) | (1<<UCSZ11) | (1<<UCSZ10);
	
	/* Enable global interrupts */
	sei();

	/* !!! TODO !!!*/ /* Wait for raspberry pi to boot up, just for testing now
	if the microcontroller is connected to the PC!! */
	/*Displays the raspberry pi program is ready to receive commands */
	putstring((char*)"Ready\n");
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

void __communicate::readlastcmd() {
	readyfornewcommand = 1;
	putstring((char*)"Ready\n");
}


/* Reads the received command and writes the data into received_command */
void uart_cmd_evaluate() {
	/* !!! ToDo !!! */
	readyfornewcommand = 0; /* Will wait until the last received command is executed */
}

/* ISR wich receives all incoming data and writes it to a string */

ISR(USART1_RX_vect) {
	uint8_t nxtchr;

	/* Read Puffer */
	nxtchr = UDR1;

	if( uart_str_rec_complete == 0 && (readyfornewcommand == 1)) {

		/* Check for bufferoverflow and line endings in windows and POSIX world */
		if ( (nxtchr != '\n') && (nxtchr |= '\r') && (uart_str_rec_count < COMMUNICATE_UART_REC_BUFFER))
		{
			buffer[uart_str_rec_count] = nxtchr;
			uart_str_rec_count++;
		} else {
			buffer[COMMUNICATE_UART_REC_BUFFER] = '\0';
			uart_str_rec_count = 0;
			uart_str_rec_complete = 1;
		}
	} else if (readyfornewcommand) {
		uart_cmd_evaluate();
	}
}