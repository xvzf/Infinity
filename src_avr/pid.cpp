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
THE SOFTWARE. */


#include "pid.h"

simplePID::simplePID(float P,float I ,float D) {
	float e_last = 0;
	float e_sum = 0;

}

simplePID::~simplePID() {

}  

void simplePID::set_value(float val) {
	this->value_actually = val;
}

void simplePID::set_tobe(float val) {
	this->value_tobe = val;
}

float simplePID::update() {

	/* Calculate difference */
	dif = value_actually - value_tobe;

	dif_sum += dif;

	/* proportional regulator */
	float yP = Kp * dif;

	/* integral regulator */
	float yI = Ki * UPDATE_INTERVALL * dif_sum;
	
	/* differential regulator */
	float yD = Kd * ((dif-dif_last)/UPDATE_INTERVALL);

	/* Update variable values */
	dif_last =dif;

	return (yP + yI + yD);
}