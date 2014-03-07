/*
* light weight WS2812 lib V2.1 - Arduino support - Edited for Project Infinity
*
* Controls WS2811/WS2812/WS2812B RGB-LEDs
* Author: Matthias Riegler
*
* Mar 07 2014: Added Arduino and C++ Library
*
* License: GNU GPL v2 (see License.txt)
*/

#ifndef WS2812_H_
#define WS2812_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#ifndef F_CPU
#define  F_CPU 16000000UL
#endif
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef ARDUINO
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif
#endif

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
	
	#ifndef ARDUINO
	void setOutput(const volatile uint8_t* port, volatile uint8_t* reg, uint8_t pin);
	#else
	void setOutput(uint8_t pin);
	#endif
	
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