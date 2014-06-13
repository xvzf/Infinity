#!/bin/bash

#/*
#The MIT License (MIT)
#
#Copyright (c) 2014 Matthias Riegler
#
#Permission is hereby granted, free of charge, to any person obtaining a copy of
#this software and associated documentation files (the "Software"), to deal in
#the Software without restriction, including without limitation the rights to
#use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
#the Software, and to permit persons to whom the Software is furnished to do so,
#subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in
#all copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#THE SOFTWARE.
# */ 


####                       ####
#    INFINITY BUILD SYSTEM    #
# (c) Matthias Riegler(2014)  #
####                       ####

#	Project defines

# Project configuration

export PROJECT_HOME=.

export AVR_PROJECT_SOURCES='infinity.cpp IMU.cpp communicate.cpp main.cpp sensors.cpp WS2812.cpp itg3200.cpp motors.cpp sensors_calibration.cpp adxl345.cpp light_ws2812.cpp mpu6050.cpp twi.cpp'
export AVR_PROJECT_HOME=.
export AVR_PROJECT_LINK_NAME=INFINITY.elf
export AVR_PROJECT_IHEX_NAME=$AVR_PROJECT_LINK_NAME.hex
export HOST_PROJECT_HOME=.
export HOST_PROJECT_PROCESSING_FILE=$HOST_PROJECT_HOME/src_host/show_orientation//show_orientation.pde

# Programs
export AVR_CPP=avr-c++
export AVR_LD=avr-ld
export AVR_OBJCOPY=avr-objcopy
export AVR_SIZE=avr-size
export AVRDUDE=avrdude
export PROCESSING=processing
export SSH=ssh
export SSHPASS=sshpass # can left unset then, you have to manually type password
export EDITOR=sublime 

# SSH
export SSH_PASSPHRASE=infinity
export SSH_COPTER_USER=root
export SSH_COPTER_IP=12.0.1.4

# AVR GCC
export AVR_MCU='atmega32u4'
export AVR_CPPFLAGS='-std=gnu++11 -O3'
export AVR_LDFLAGS='-fno-use-cxa-atexit'

# AVR Dude
export AVRDUDE_MMCU='m32u4'
export AVRDUDE_PROGRAMMER='stk500v2'
export AVRDUDE_PORT='/dev/ttyACM0'

#########

# Internal defines
export AVR_PROJECT_SRC_DIR=${AVR_PROJECT_HOME}/src_avr
export AVR_PROJECT_INC_DIR=${AVR_PROJECT_HOME}/inc_avr
export AVR_PROJECT_OUT_DIR=${AVR_PROJECT_HOME}/out_avr

# Internal variables

# Stylistic defines
red='\e[0;31m'
green='\e[0;32m'
blue='\e[0;34m'
NC='\e[0m'


#########

function clean() {
	rm -fR ./out*
}

function avr_init() {
	mkdir -p ${AVR_PROJECT_OUT_DIR}	 	
	rm -Rf ${AVR_PROJECT_OUT_DIR}/*
	mkdir -p ${AVR_PROJECT_OUT_DIR}/linked
	mkdir -p ${AVR_PROJECT_OUT_DIR}/ihex	
}

function avr_compile() {
	for i in $AVR_PROJECT_SOURCES;	do
		$AVR_CPP -c $AVR_CPPFLAGS -mmcu=$AVR_MCU -I$PROJECT_HOME -I$AVR_PROJECT_INC_DIR $AVR_PROJECT_SRC_DIR/$i -o ${AVR_PROJECT_OUT_DIR}/${i}.o
		if [[ $? -eq 0 ]];	then			
			echo -e "AVR: $i: $green Compiled successfully $NC"
		else
			echo -e "AVR: $i: $red FAILED, see log above! $NC"
			exit
		fi 
	done
}

function avr_link() {
	$AVR_CPP -mmcu=$AVR_MCU $AVR_PROJECT_OUT_DIR/*.o -o $AVR_PROJECT_OUT_DIR/linked/$AVR_PROJECT_LINK_NAME

	if [[ $? -eq 0 ]];	then			
		echo -e "AVR: $AVR_PROJECT_LINK_NAME: $green Linked successfully $NC"
	else
		echo -e "AVR: $AVR_PROJECT_LINK_NAME: $red FAILED, see log above! $NC"
		exit
	fi 
}

function avr_to_ihex() {
	$AVR_OBJCOPY -j .text -j .data -O ihex $AVR_PROJECT_OUT_DIR/linked/$AVR_PROJECT_LINK_NAME $AVR_PROJECT_OUT_DIR/ihex/$AVR_PROJECT_IHEX_NAME
	if [[ $? -eq 0 ]];	then			
		echo -e "AVR: $AVR_PROJECT_IHEX_NAME: $green Converted successfully to ihex $NC"
	else
		echo -e "AVR: $AVR_PROJECT_IHEX_NAME: $red FAILED, see log above! $NC"
		exit
	fi
}

function avr_build() {
	echo -e "$red AVR: Init build directory..... $NC"
	avr_init
	echo -e "$red AVR: Compiling..... $NC"
	avr_compile
	echo -e "$red AVR: Linking..... $NC"
	avr_link
	echo -e "$red AVR: Converting to ihex..... $NC"
	avr_to_ihex
}

function avr_flash() {
	$AVRDUDE -p $AVRDUDE_MMCU -P $AVRDUDE_PORT -c $AVRDUDE_PROGRAMMER -u -U flash:w:$PROJECT_OUT_DIR/ihex/$PROJECT_IHEX_NAME
	if [[ $? -eq 0 ]];	then			
		echo -e "AVR: $AVRDUDE: $green Uploaded successfully $NC"
	else
		echo -e "AVR: $AVRDUDE: $red FAILED, see log above! $NC"
		exit
	fi
}

function avr_info() {
	echo -e "  == AVR USAGE INFO =="
	$AVR_SIZE $AVR_PROJECT_OUT_DIR/linked/$AVR_PROJECT_LINK_NAME
	echo -e "  ==                =="
}

function code_stats() {
	CPP_CODE=$(($(( find ./ -name '*.cpp' -print0 | xargs -0 cat ) | wc -l)+$(( find ./ -name '*.h' -print0 | xargs -0 cat ) | wc -l)))
	BASH_CODE=$(( find ./ -name '*.sh' -print0 | xargs -0 cat ) | wc -l)
	PROCESSING_CODE=$(( find ./ -name '*.pde' -print0 | xargs -0 cat ) | wc -l)
	PYTHON_CODE=$(( find ./ -name '*.py' -print0 | xargs -0 cat ) | wc -l)
	
	TOTAL=$(($CPP_CODE+$BASH_CODE+$PROCESSING_CODE+$PYTHON_CODE))
	echo
	echo -e "$red\tTotal lines of C/C++ code: $CPP_CODE$NC"
	echo -e "$red\tTotal lines of BASH code: $BASH_CODE$NC"
	echo -e "$red\tTotal lines of Processing code: $PROCESSING_CODE$NC"
	echo -e "$red\tTotal lines of PYTHON code: $PYTHON_CODE$NC"
	echo
	echo -e "$red Total: $TOTAL$NC"	
}

function init() {
	avr_init
}

function __info() {
	avr_info
}

function build() {
	avr_build
	__info
}

function compile() {
	avr_compile
}

function launch() {
	$PROCESSING $HOST_PROJECT_PROCESSING_FILE > /dev/null
}

function __install() {
	avr_flash
}

function __uninstall() {
	echo Not implemented yet
}

function __help() {
	echo -e "Available commands:"
	echo -e "\tshow_license: SHOW THE PROJECT LICENSE!!"
	echo -e "\tbuild: build the complete source tree"
	echo -e "\tcompile: just compile the complete source tree"
	echo -e "\tflash: upload to uC, please call 'build' first"
	echo -e "\tinstall: Installs project, please call 'build' first"
	echo -e "\tclean: Clean up the build directory"
	echo -e "\tall: Build and install"
	echo -e "\tstats: Shows Linex of Code"
	echo -e "\tssh_copter: Virtual shell on copter"
	echo -e "\tlaunch_host: Launches Host"
	echo -e "\tibs-shell: open developer shell"
	echo -e "\tedit: edit project files"
	echo -e "\thelp: show this issue"
}

function devloop() { 
	
	if [[ "$var" == "build" ]]; then			
		build 
		exit
	fi

	if [[ "$var" == "compile" ]]; then			
		init
		compile
		exit
	fi

	if [[ "$var" == "flash" ]]; then			
		avr_flash
		exit
	fi


	if [[ "$var" == "install" ]]; then			
		__install
		exit
	fi

	if [[ "$var" == "all" ]]; then			
		build 
		__install
		exit
	fi

	if [[ "$var" == "clean" ]]; 	then			
		clean
		echo -e "$red Cleaned up $NC"
		exit
	fi

	if [[ "$var" == "stats" ]]; 	then			
		clean
		echo -e "$red Code statistics: $NC"
		code_stats
		exit
	fi

	if [[ "$var" == "launch_host" ]]; 	then			
		launch
		exit
	fi

	if [[ "$var" == "edit" ]]; 	then			
		$EDITOR ./src*/*.cpp ./inc*/*.h ./ibs.sh ./config.h > /dev/null&
		exit
	fi
	
	if [[ "$var" == "ssh_copter" ]]; 	then			
		clean
		$SSHPASS -p $SSH_PASSPHRASE $SSH $SSH_COPTER_USER@$SSH_COPTER_IP
		exit
	fi
	
	if [[ "$var" == "show_license" ]]; 	then			
		clean
		echo -e "$red"	
		more LICENSE	
		echo -e "$NC"
		exit
	fi

	if [[ "$var" == "help" ]]; 	then			
		__help
		exit
	fi	

	if [[ "$var" == "clear" ]]; 	then			
		clear
		exit
	fi	
	
	echo -e "$red"
	echo "command not recognized, try help"
	echo -e "$NC"
}

###


### Info about the program
echo -e "$blue"
clear
echo -e "\t\t####                       ####"
echo -e "\t\t#    INFINITY BUILD SYSTEM    #"
echo -e "\t\t# (c) Matthias Riegler(2014)  #"
echo -e "\t\t####                       ####"

echo -e "$NC"

if [[ "$1" == "ibs-shell" ]]; then			
	while true
	do

		echo -n "<infinity-$USER>#"
		read input

		if [[ "$input" == "update" ]]; then			
			git pull
			exit
		fi

		if [[ "$input" == "exit" ]]; then			
			exit
		fi

		./ibs.sh $input
	
		done
	exit
fi

if [[ -z "$1" ]]; then
	echo -e "$blue" 
	__help
	echo -e "$NC"
	exit
fi

var=$1
devloop

