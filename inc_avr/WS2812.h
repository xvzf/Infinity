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


#ifndef WS2812_H_
#define WS2812_H_

#include "config.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

struct cRGB { uint8_t g; uint8_t r; uint8_t b; };

class WS2812 {
public: 
	WS2812(uint16_t num_led);
	WS2812() { 
		count_led = 1;	
		pixels = (uint8_t*)malloc(count_led);
		setOutput(&PORTC,&DDRC,7); // PortC7
	};
	
	void set_led_num(uint16_t num_leds);
	~WS2812();
	
	void setOutput(const volatile uint8_t* port, volatile uint8_t* reg, uint8_t pin);
	
	cRGB get_crgb_at(uint16_t index);
	uint8_t set_crgb_at(uint16_t index, cRGB px_value);
	void sync();
	
	/* Status LED functions */
	/* G R B */
	void clear() { set_crgb_at(0, cRGB{0,0,0});sync();};
	void red() { set_crgb_at(0, cRGB{0,255,0});sync();};
	void green() { set_crgb_at(0, cRGB{255,0,0});sync();};
	void blue() { set_crgb_at(0, cRGB{0,0,255});sync();};
	void allert() { set_crgb_at(0, cRGB{255,0,255});sync();};
	void okay() {set_crgb_at(0, cRGB{255,0,0});sync();};
	void error() {set_crgb_at(0, cRGB{0,255,0});sync();};
	void initializing() {set_crgb_at(0, cRGB{255,0,255});sync();};
private:
	uint16_t count_led;
	uint8_t *pixels;
	
	void ws2812_sendarray_mask(uint8_t *array,uint16_t length, uint8_t pinmask,uint8_t *port, uint8_t *portreg);

	const volatile uint8_t *ws2812_port;
	volatile uint8_t *ws2812_port_reg;
	uint8_t pinMask; 
};



#endif /* WS2812_H_ */
