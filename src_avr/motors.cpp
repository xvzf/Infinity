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


#include "motors.h"

__motors::__motors()
{

    // Set motor pins as output
    DDRB |= ( (1 << PB5) | (1 << PB6) | (1 << PB7) );
    DDRC |= (1 << PC6);

    /* === Parts of the MultiWii Source-Code, see multiwii.com === */

    /*Setup Timer 1*/
    TCCR1A |= (1 << WGM11); // phase correct mode & no prescaler
    TCCR1A &= ~(1 << WGM10);
    TCCR1B &= ~(1 << WGM12) &  ~(1 << CS11) & ~(1 << CS12);
    TCCR1B |= (1 << WGM13) | (1 << CS10);
    ICR1   |= 0x3FFF; // TOP to 16383;

    /*Setup Timer 3*/

    TCCR3A |= (1 << WGM31); // phase correct mode & no prescaler
    TCCR3A &= ~(1 << WGM30);
    TCCR3B &= ~(1 << WGM32) &  ~(1 << CS31) & ~(1 << CS32);
    TCCR3B |= (1 << WGM33) | (1 << CS30);
    ICR3   |= 0x3FFF; // TOP to 16383;


    /*Associate Motor Pins*/
    TCCR1A |= (1 << MBACK_R); // connect pin MBACK_R to timer 1 channel B
    TCCR1A |= (1 << MFRONT_R); // connect pin MFRONT_R to timer 1 channel A
    TCCR1A |= (1 << MBACK_L); // connect pin MBACK_L to timer 1 channel C
    TCCR3A |= (1 << MFRONT_L); // connect pin MFRONT_L to timer 3 channel A

}

__motors::~__motors()
{

}

void __motors::update()
{
    // Motor front left
    OCR3A = ((FRONT_L << 4) - 16000) + 128;
    // Motor front right
    OCR1A = ((FRONT_R << 4) - 16000) + 128;
    // Motor back left
    OCR1C = ((BACK_L << 4) - 16000) + 128;
    // Motor back right
    OCR1B = ((BACK_R << 4) - 16000) + 128;
}

void __motors::init_esc()
{

    BACK_L = max_cmd;
    BACK_R = max_cmd;
    FRONT_L = max_cmd;
    FRONT_R = max_cmd;
    update();

    _delay_ms(1500);

    BACK_L = min_cmd;
    BACK_R = min_cmd;
    FRONT_L = min_cmd;
    FRONT_R = min_cmd;
    update();

    _delay_ms(1000);
    _delay_ms(1000);
    _delay_ms(1000);
    _delay_ms(1000);
}

void __motors::soft_start_engines()
{
    /* motor front right*/
    FRONT_R = start_cmd;
    update();
    _delay_ms(500);

    /* motor back left*/
    BACK_L = start_cmd;
    update();
    _delay_ms(500);

    /* motor front left*/
    FRONT_L = start_cmd;
    update();
    _delay_ms(500);

    /* motor back right */
    BACK_R = start_cmd;
    update();
    _delay_ms(500);
}

void __motors::soft_stop_engines()
{
    /* motor front right*/
    FRONT_R = min_cmd;
    update();
    _delay_ms(500);

    /* motor back left*/
    BACK_L = min_cmd;
    update();
    _delay_ms(500);

    /* motor front left*/
    FRONT_L = min_cmd;
    update();
    _delay_ms(500);

    /* motor back right */
    BACK_R = min_cmd;
    update();
    _delay_ms(500);
}

void __motors::emergency_stop_engines()
{
    /* motor front right*/
    BACK_L = min_cmd;
    BACK_R = min_cmd;
    FRONT_L = min_cmd;
    FRONT_R = min_cmd;
    update();
}
