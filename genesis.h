/*
 * Copyright (c) 2012 Sergio Azevedo
 *
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * Sega Genesis Controller library for Arduino.
 *
 * Using insights into the communication between the controller and the console found
 * at http://pinouts.ru/Game/genesiscontroller_pinout.shtml
 *
 * The 74HC157 controller supports 2 to 6V VCC, so it is possible to use with more recent 3.3V systems.
 *
 * This controller has a 9 pin D-SUB interface:
 *      Pin	 Name (Select=GND)	 Name (Select=+5V)
 *      1	 Up	                 Up
 *      2	 Down	                 Down
 *      3	 Gnd / Left
 *      4	 Gnd / Right
 *      5	 VCC	                 VCC
 *      6	 Button A	         Button B
 *      7	 Select	                 Select
 *      8	 Ground	                 Ground
 *      9	 Start	                 Button C
 *
 * Pin 7 (Select) is a digital input that defines which is the meaning of the output for pins 6 and 9.
 *
 */

#ifndef __GENESIS_H__
#define __GENESIS_H__

// The arduino core isn't loaded at this point, so we must force load sooner
#include "arduino.h"

int sgcPin1 = 2;
int sgcPin2 = 3;
int sgcPin3 = 4;
int sgcPin4 = 5;

int sgcPin6 = 6;
int sgcPin9 = 7;

int sgcPin7 = 9;

/*
 * Initialization of the genesis controller related pins on Arduino
 * Must be called on void setup()
 */
void initGenesis()
{
  pinMode(sgcPin1, INPUT);
  pinMode(sgcPin2, INPUT);
  pinMode(sgcPin3, INPUT);
  pinMode(sgcPin4, INPUT);
  pinMode(sgcPin6, INPUT);
  pinMode(sgcPin9, INPUT);
  
  pinMode(sgcPin7, OUTPUT);
}

/*
 * Reads all the inputs from the controller
 */
void getGenesisState(byte *up, byte *down, byte *left, byte *right, byte *a, byte *b, byte *c, byte *start)
{
  digitalWrite(sgcPin7, LOW);
  
  *a = !digitalRead(sgcPin6);
  *start = !digitalRead(sgcPin9);
  
  digitalWrite(sgcPin7, HIGH);
  
  *b = !digitalRead(sgcPin6);
  *c = !digitalRead(sgcPin9);
  *up = !digitalRead(sgcPin1);
  *down = !digitalRead(sgcPin2);
  *left = !digitalRead(sgcPin3);
  *right = !digitalRead(sgcPin4);
}

#endif
