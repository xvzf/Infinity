Infinity
========

Project Infinity ACC - Another Copter Control


Project Infinity is a Quadrocopter-Controller
As hardware, an ITG3200 Gyroscope, an ADXL345 Accelerometer and a not yet specified magnometer will be used. These sensors in combination with a powerfull Raspberry Pi as "controll unit for operation tasks" and an Atmega32u4 as "stabilisation unit".
Controlling commands will be Send via WiFi to the Raspberry Pi, wich will evaluate the arriving data and send it on to the Atmega. The Raspberry Pi will provide a live video stream in low quality over WiFi while recording it in FullHD 1080p on a USB Stick or the SD Card.
The Software for the Raspberry Pi and the Ground Station will be developed in Python. The Software for the AtMega will be developed in C++ with AVR Studio 6.

A Forum-Thread on the building process of the Quadrotor System can be found at FPV-Community (http://fpv-community.de/showthread.php?42075-Project-Infinity-Ein-etwas-anderer-Quadrocopter) - but in german.

Pictures can be found in my Dropbox-folder: https://www.dropbox.com/sh/alv8mfxikzrpoa2/QitDAq15Sq
