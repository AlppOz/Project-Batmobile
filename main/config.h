#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Pin Assignments
const int LIR = 10; //left IR
const int RIR = 7; //right IR
const int Scream = 8;
const int Echo = 9;
const int leftPermission = 5;
const int rightPermission = 6;
const int leftForward = 4;
const int leftReverse = 3;
const int rightForward = A0;
const int rightReverse = A1;
//right wheel hall sensor gets the interrupt method
const int hall_right = 12; //dont use pin 13
//left wheel hall sensor gets the CD4040/4021 system
const int reset_CD = A5; //connected to pin 11 (reset pin) of CD4040
const int CD_control = A4; //connected to pin 9 (P/S control) of CD4021
const int CD_clock = A3; //connected to pin 10 (clock) of CD4021
const int CD_data = A2; //connected to pin 3 (Q8) of CD4021

const float hall_const = 5.0;//cm per pulse constant

//intial mode for buggy until told otherwise (Oguz Note: What are these?)
extern char mode;
extern String msg;

extern volatile unsigned long right_pulse;
//extern unsigned long right_pulse;
//extern int lastRightState;

#endif