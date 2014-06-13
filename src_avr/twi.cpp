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



#include "twi.h"

uint8_t twi_init() {
	
	/* Set TWI Bitrate */
	
	TWBR = ((F_CPU/TWI_SPEED)-16)/2;
	if(TWBR < 11) return TWI_ERROR;
	
	return TWI_SUCCESS;
}

uint8_t twi_start(uint8_t addr, uint8_t twi_type) {
	uint8_t twi_state;
	
	/* Send START condition */
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	/* Wait till completed */
	while(!(TWCR & (1<<TWINT)));
	
	/* Get TWI State */
	twi_state = TWSR & 0xF8;
	if((twi_state != TWI_START) && (twi_state != TWI_REP_START)) return TWI_ERROR;
	
	/* Send device address */
	TWDR = (addr<<1) + twi_type;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	/* Wait for complete and ACK/NACK */
	while(!(TWCR & (1<<TWINT)));
	
	/* Get state */
	twi_state = TWSR & 0xF8;
	
	if ((twi_state != TWI_MTX_ADR_ACK) && (twi_state != TWI_MRX_ADR_ACK)) return TWI_ERROR;

	return TWI_SUCCESS;
}

void twi_stop() {
	/* Send STOP */
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	
	/* Wait..... */
	while (TWCR & (1<<TWINT));
}

uint8_t twi_write(uint8_t byte) {
	uint8_t twi_state;
	
	/* Send data */
	TWDR = byte;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	/* Wait till complete */
	while(!(TWCR & (1<<TWINT)));
	
	/* Check Status register */
	twi_state = TWSR & 0xF8;
	if(twi_state != TWI_MTX_DATA_ACK) return TWI_ERROR;
	
	return TWI_SUCCESS;
}

uint8_t twi_read_ack() {
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR & (1<<TWINT)));

	return TWDR;
}

uint8_t twi_read_nack() {
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
	return TWDR;
}
