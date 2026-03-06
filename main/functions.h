#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include "config.h"

void forward(float cm); //drives the car forwards a specified amount of distance

byte left_pulse_count(); //returns left wheel pulse

void rightISR(); //increments the right wheel pulse whenever called (at attachinterrupt). Use right_pulse for current value

//void checkRightEncoder();

#endif