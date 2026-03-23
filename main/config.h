#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#include <PID_v1.h>

// Imports and Variable for Wifi Communication
#include "WiFiS3.h"
extern char ssid[];
extern char pass[];
extern int status;
extern WiFiServer server;
extern WiFiClient client;

// Pin Assignments
const int MICROBIT = 2;
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

const float hall_const = 5.1; //cm per pulse constant for right. The slides claim 8 pulses is 20.4 but testing showed 4 pulses is 20.
//for the left encoder, it increments pulses by 2, but even then the inbetween pulses are trash. 
//I mean this: a full revolution is a pulse of 4. So revolution wise, it goes up 4, 8, 12, 16,.. 
//And you would expect inbetween revolutions (2, 6, 10,..) to be half way, they're not. Most of the time they are 3/4 for some reason but its generally unreliable
//so actual information wise, we are dealing with very low resolution on the left side. We already lost half the resolution due to the increment by 2 thing. With this now, we lose another half on top of that. Yay
//the right doesn't have this problem. But since the corrective logic is based on comparing the two pulses, what use is there of a pulse of 1 or 2 or 3 for example in the right wheel.
//const float hall_const_left = 10.0; //for left with the hardcoded shiftIn

const float wait_per_angle = 8.33;

//intial mode for buggy until told otherwise (Oguz Note: What are these?)
extern char mode;
extern String msg;

extern volatile unsigned long right_pulse;
extern volatile unsigned long right_duration;

extern volatile bool hadObject;
//extern unsigned long right_pulse;
//extern int lastRightState;

//PID stuff
extern PID pid_r, pid_l;
extern double err_r, err_l;
extern double correction_r, correction_l;
extern double setpoint;
//fine tune the PID parameters
const double Kp_r = 20;
const double Ki_r = 0.1;
const double Kd_r =  0.0;

const double Kp_l = 3;
const double Ki_l = 0.0;
const double Kd_l =  0.0;

extern float current_speed;

#endif