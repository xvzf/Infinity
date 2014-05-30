/*
The MIT License (MIT)

Copyright (c) 2014 Matthias Riegler

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
 */

import processing.serial.*;

Serial myPort;  // Create object from Serial class

float angle_x = 0;
float angle_y = 0;
float angle_z = 0;

byte[] inBuffer = new byte[30]; // this is the number of chars on each line from the Arduino (including /r/n)


final int VIEW_SIZE_X = 640, VIEW_SIZE_Y = 480;


void setup() 
{
  size(VIEW_SIZE_X, VIEW_SIZE_Y, P3D);
  myPort = new Serial(this, "COM7", 115200);    
  delay(100);
  myPort.clear();
}




void readSensors() {
  if (myPort.available() >= 18) {
    String inputString = myPort.readStringUntil((int) '\n');
    if (inputString != null && inputString.length() > 0) {
      String [] inputStringArr = split(inputString, ";");
      angle_x = (PI/180) * float(inputStringArr[0]);
      angle_y = (PI/180) * float(inputStringArr[1]);
      angle_z = (PI/180) * float(inputStringArr[2]);
    }
  }
}



void buildBoxShape() {
  //box(60, 10, 40);
  noStroke();
  beginShape(QUADS);

  //Z+ (to the drawing area)
  fill(#888888);
  vertex(-30, -5, 20);
  vertex(30, -5, 20);
  vertex(30, 5, 20);
  vertex(-30, 5, 20);

  //Z-
  fill(#888888);
  vertex(-30, -5, -20);
  vertex(30, -5, -20);
  vertex(30, 5, -20);
  vertex(-30, 5, -20);

  //X-
  fill(#999999);
  vertex(-30, -5, -20);
  vertex(-30, -5, 20);
  vertex(-30, 5, 20);
  vertex(-30, 5, -20);

  //X+
  fill(#999999);
  vertex(30, -5, -20);
  vertex(30, -5, 20);
  vertex(30, 5, 20);
  vertex(30, 5, -20);

  //Y-
  fill(#ffffff);
  vertex(-30, -5, -20);
  vertex(30, -5, -20);
  vertex(30, -5, 20);
  vertex(-30, -5, 20);

  //Y+
  fill(#ffffff);
  vertex(-30, 5, -20);
  vertex(30, 5, -20);
  vertex(30, 5, 20);
  vertex(-30, 5, 20);

  endShape();
}


void drawCube() {  
  pushMatrix();
  translate((VIEW_SIZE_X / 2), (VIEW_SIZE_Y / 2 ), 0);
  scale(4, 4, 4);

  rotateX(angle_y);
  rotateZ(angle_x);
  rotateY(angle_z);

  buildBoxShape();

  popMatrix();
}


void draw() {  
  readSensors();

  background(#555555);


  drawCube();
}

