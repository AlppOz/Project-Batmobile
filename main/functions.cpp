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

  unsigned int left_power_new, right_power_new;

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

  while (left_pulse < pulse_all || right_pulse < pulse_all) {
    left_pulse = left_pulse_count();
    //checkRightEncoder();
    //right_pulse already exists as volatile;

    noInterrupts();
    current_right = right_pulse;
    interrupts();

    if (left_pulse > current_right) {
      //diff = left_pulse - right_pulse;
      left_power_new= left_power - (increm * diff);
      right_power_new = right_power + (increm * diff);
      analogWrite(leftPermission,left_power_new);
      analogWrite(rightPermission,right_power_new);
    }
    else if (current_right > left_pulse) {
      //diff = right_pulse - left_pulse;
      left_power_new = left_power + (increm * diff);
      right_power_new = right_power - (increm * diff);
      analogWrite(leftPermission,left_power_new);
      analogWrite(rightPermission,right_power_new);
    }
    else {
      analogWrite(leftPermission,left_power);
      analogWrite(rightPermission,right_power);
    }

    
    
  }

  Serial.print(left_pulse);
  Serial.print("   ");
  Serial.print(right_pulse);
  Serial.println("");
  //stopping the motors
  digitalWrite(leftForward,LOW);
  digitalWrite(rightForward,LOW);
  analogWrite(leftPermission,0);
  analogWrite(rightPermission,0);
}

