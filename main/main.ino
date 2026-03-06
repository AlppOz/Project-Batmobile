#include "config.h"
#include "functions.h"


volatile unsigned long right_pulse = 0;

//unsigned long right_pulse = 0;

//what are these?
char mode = 'S';
String msg = "";


void setup() {
  Serial.begin(115200);

  //pin intialization
  pinMode(Scream,OUTPUT);
  pinMode(Echo,INPUT);
  pinMode(leftPermission,OUTPUT);
  pinMode(rightPermission,OUTPUT);
  pinMode(leftForward,OUTPUT);
  pinMode(rightForward,OUTPUT);
  pinMode(leftReverse,OUTPUT);
  pinMode(rightReverse,OUTPUT);
  pinMode(LIR,INPUT);
  pinMode(RIR,INPUT);
  pinMode(CD_clock, OUTPUT);
  pinMode(CD_control, OUTPUT);
  pinMode(CD_data, INPUT);
  pinMode(reset_CD, OUTPUT);
  pinMode(hall_right, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hall_right), rightISR, FALLING);
  digitalWrite(reset_CD, HIGH);
  delay(10);
  digitalWrite(reset_CD, LOW);

  analogWrite(leftPermission, 0);
  analogWrite(rightPermission, 0);
}

void loop() {
  forward(50);
  delay(20000);
}