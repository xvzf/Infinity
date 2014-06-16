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

/* Orientated by the Teensy UART Library - see https://www.pjrc.com/teensy/uart.html */

#include "communicate.h"

#include <stdlib.h>

__uart::__uart()
{

}

__uart::~__uart()
{

}

void __uart::init() {
	uart_init();
}

void __uart::print(char c)
{
    uart_putchar(c);
}

void __uart::print(char *string)
{
    while (*string)
    {
        print(*string);
        string++;
    }
}

void __uart::print(float toput)
{
    char buffer[10];

    dtostrf( toput, 6, 3, buffer);

    this->print((char *)buffer);
}

void __uart::print(int16_t toput)
{

    char buffer[7];

    itoa( toput, buffer, 10 );

    this->print((char *)buffer);
}


void __uart::print(int32_t toput)
{

    char buffer[12];

    ltoa( toput, buffer, 10 );

    this->print((char *)buffer);
}

uint8_t __uart::available()
{
    return uart_available();
}

char __uart::get()
{
    return uart_getchar();
}