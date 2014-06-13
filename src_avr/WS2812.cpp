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

#include "WS2812.h"

WS2812::WS2812(uint16_t num_leds) {
	count_led = num_leds;
	
	pixels = (uint8_t*)malloc(count_led);
	
}


void WS2812::set_led_num(uint16_t num_leds) {
	count_led = num_leds;
	pixels = (uint8_t*)malloc(count_led);
}

cRGB WS2812::get_crgb_at(uint16_t index) {
	
	cRGB px_value;
	
	if(index < count_led) {
		
		uint16_t tmp;
		tmp = index * 3;
		
		px_value.g = pixels[tmp];
		px_value.r = pixels[tmp+1];
		px_value.b = pixels[tmp+2];
	}
	
	return px_value;
}

uint8_t WS2812::set_crgb_at(uint16_t index, cRGB px_value) {
	
	if(index < count_led) {
		
		uint16_t tmp;
		tmp = index * 3;
		
		pixels[tmp] = px_value.g;
		pixels[tmp+1] = px_value.r;
		pixels[tmp+2] = px_value.b;
		
		return 0;
	} 
	return 1;
}

void WS2812::sync() {
	*ws2812_port_reg |= pinMask; // Enable DDR
	ws2812_sendarray_mask(pixels,3*count_led,pinMask,(uint8_t*) ws2812_port,(uint8_t*) ws2812_port_reg );	
}

WS2812::~WS2812() {
	
	
}

void WS2812::setOutput(const volatile uint8_t* port, volatile uint8_t* reg, uint8_t pin) {
pinMask = (1<<pin);
ws2812_port = port;
ws2812_port_reg = reg;
}
