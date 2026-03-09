#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include "config.h"

void forward(float cm); //drives the car forwards a specified amount of distance

byte shiftIn(int myDataPin, int myClockPin);

byte left_pulse_count(); //returns left wheel pulse

void rightISR(); //increments the right wheel pulse whenever called (at attachinterrupt). Use right_pulse for current value

//void checkRightEncoder();

// Two function for the basics of turning right or left for set time
void spinRight(int duration);
void spinLeft(int duration);

//Small step procedure for adjustments prompted by IR sensors
void Step_Right();
void Step_Left();

// Funtions which return true if the buggy detects it has crossed the line
bool Left_Error(); //crossed the line coming from the left
bool Right_Error(); //crossed the line coming from the right

//Basic function for buggy to drive forward for duration
void Mush(int duration, int left, int right);

//returns true if an object closer than the safe distance
bool Bogie(int Safe_Distance = 30);
#endif