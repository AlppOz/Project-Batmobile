#include "functions.h"

byte left_pulse_count() {
  digitalWrite(CD_control, 1);   // load parallel data from CD4040
  delayMicroseconds(5);
  digitalWrite(CD_control, 0);    // switch to serial shift mode
  return shiftIn(CD_data, CD_clock, MSBFIRST);
}


void rightISR() {
  const unsigned int CAN = 5000;
  static unsigned long lastPulse = 0;
  unsigned long now = micros();
  if (now - lastPulse > CAN) {  // ignore pulses less than 5ms apart
    right_pulse++;
    lastPulse = now;
  }
}


/* earlier adoptation of the rightISR. The most basic case.
void rightISR() {
  right_pulse++;
}
*/


void forward(float cm) {
  unsigned int left_power = 100; //out of 255
  unsigned int right_power = 100;
  unsigned int increm = 10;

  unsigned int left_power_new = left_power;
  unsigned int right_power_new = right_power;

  unsigned int pulse_all = cm / hall_const;
  //add pulse rem method. I.e what if we need 8.8 pulses, it needs to register 0.8 * hall_const for the remaining distance somehow
  
  //the great reset
  digitalWrite(reset_CD, HIGH);
  delay(10);
  digitalWrite(reset_CD, LOW);
  unsigned int left_pulse = 0;

  noInterrupts();
  right_pulse = 0;
  interrupts();

  //starting the motors
  digitalWrite(leftForward,HIGH);
  digitalWrite(rightForward,HIGH);
  digitalWrite(leftReverse,LOW);
  digitalWrite(rightReverse,LOW);

  int diff = 1;
  unsigned long current_right;
  bool left_done = 0;
  bool right_done = 0;

  while (left_done == 0 || right_done == 0) {
    left_pulse = left_pulse_count();
    //checkRightEncoder();
    //right_pulse already exists as volatile;

    noInterrupts();
    current_right = right_pulse;
    interrupts();

    //break individually logic
    if (left_pulse >= pulse_all && left_done == 0) {
      for (int i = left_power; i >= 0; i--) { //loop for smooth transition to a full stop not an abrupt one
        analogWrite(leftPermission, i);
        delay(1);
      }
      left_done = 1;
    }
    if (current_right >= pulse_all && right_done == 0) {
      for (int i = left_power; i >= 0; i--) {
        analogWrite(rightPermission,0);
        delay(1);
      }
      right_done = 1;
    }

    if (left_done == 0 && right_done == 0) {
      if (left_pulse > current_right) { //whenever left pulse changes, the first signal has information. A brand new pulse of 2 is truly a 2. And if it is greater than the right's 1 for example, needs correction
        left_power_new= left_power - (increm * diff);
        right_power_new = right_power + (increm * diff);
        analogWrite(leftPermission,left_power_new);
        analogWrite(rightPermission,right_power_new);
      }
      diff = abs((int)left_pulse - (int)current_right);
      if (left_pulse < current_right && diff >= 2) { //the resolution of the left pulse is two, whereas right's is one. So a difference of 1 bears no informational significance
        left_power_new = left_power + (increm * diff);
        right_power_new = right_power - (increm * diff);
        analogWrite(leftPermission,left_power_new);
        analogWrite(rightPermission,right_power_new);
      }
      else {
        analogWrite(leftPermission,left_power_new);
        analogWrite(rightPermission,right_power_new);
      }
    }
    /*
    Serial.print(left_pulse);
    Serial.print(" ");
    Serial.print(left_power_new);
    Serial.print("   ");
    Serial.print(right_pulse);
    Serial.print(" ");
    Serial.print(right_power_new);
    Serial.println("");
    */
  }

  
  //stopping the motors for sure this time
  digitalWrite(leftForward,LOW);
  digitalWrite(rightForward,LOW);
  analogWrite(leftPermission,0);
  analogWrite(rightPermission,0);
}

void spinRight(int duration){
  analogWrite(leftPermission,120); //give left motor power of 120/255
  analogWrite(rightPermission,0); //spinning right only so right motor gets 0 power
  digitalWrite(leftForward,HIGH); //enable forward motion
  digitalWrite(leftReverse,LOW); //disable backwards motion
  delay(duration);
  digitalWrite(leftForward,LOW); //disable forward motion after set time
  analogWrite(leftPermission,0); //stop left motor
}

void spinLeft(int duration){
  analogWrite(rightPermission,100);
  analogWrite(leftPermission,0);
  digitalWrite(rightForward,HIGH);
  digitalWrite(rightReverse,LOW);
  delay(duration);
  digitalWrite(rightForward,LOW);
  analogWrite(rightPermission,0);
}

void Step_Right(){
  spinRight(25);
  client.println("Adjusting Course Right");
}

void Step_Left(){
  spinLeft(25);
  client.println("Adjusting Course Left");
}

bool Left_Error(){
  if(digitalRead(LIR)== LOW){
    return true;

  }
  return false;
}

bool Right_Error(){
  if(digitalRead(RIR)==LOW){
    return true;

  }
  return false;
}

void Mush(int duration, int left, int right){
  analogWrite(leftPermission,left);
  analogWrite(rightPermission,right);


  digitalWrite(leftForward,HIGH);
  digitalWrite(rightForward,HIGH);
  digitalWrite(leftReverse,LOW);
  digitalWrite(rightReverse,LOW);
  

  client.println("Going Forward");
  delay(duration);

  digitalWrite(leftForward,LOW);
  digitalWrite(rightForward,LOW);
  analogWrite(leftPermission,0);
  analogWrite(rightPermission,0);
}

bool Bogie(int Safe_Distance){
  long duration; //if needed for outside the function, we just pass by reference
  int distance;

  digitalWrite(Scream,LOW);
  delayMicroseconds(2);

  digitalWrite(Scream,HIGH);
  delayMicroseconds(10);
  digitalWrite(Scream,LOW);

  duration = pulseIn(Echo,HIGH);
  distance = duration/58;

  if(distance < Safe_Distance) {
    client.println("Obstacle in Path");
    hadObject = true;
    return true;
  }
  if (hadObject)client.println("Object Removed");
  hadObject = false;
  return false;
}
