#include "config.h"
#include "functions.h"


// Define and initialize the WiFi variables here
char ssid[] = "Gotham";
char pass[] = "Bruce_Wayne";
int status = WL_IDLE_STATUS;
WiFiServer server(5200);
WiFiClient client;

volatile unsigned long right_pulse = 0;
volatile unsigned long right_duration = 0;

volatile bool hadObject = false;

//unsigned long right_pulse = 0;

//what are these?
char mode = 'S';
String msg = "";

//PID Global
double err;
double correction;
double setpoint = 0;
PID pid_f(&err, &correction, &setpoint, Kp, Ki, Kd, DIRECT);


void setup() {
  Serial.begin(115200);

  //Wifi Network configuration
  Serial.print("Network␣named:␣"); // Starting an access point
  Serial.println(ssid);
  status = WiFi.beginAP(ssid, pass);
  Serial.println("Network␣started");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP␣Address:␣");
  Serial.println(ip);
  server.begin();
  
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

  pid_f.SetMode(AUTOMATIC);
  pid_f.SetSampleTime(10);
  pid_f.SetOutputLimits(-60, 60);

  analogWrite(leftPermission, 0);
  analogWrite(rightPermission, 0);
}


int right = 100;
int left = 125;
String last_printed_state = ""; // Replaces stop_message to prevent spam
char command = 'q';
String num;
float value;
int distance;

void loop() {
  /*
  WiFiClient newClient = server.available();

  if (newClient) {
    client = newClient;  // only overwrite when there's actually a new connection
  }

  if (client && client.connected()) {
    if (client.available()) { //only try to read when there's data
      msg = client.readStringUntil('\n'); 
      msg.trim();
      if (msg!= "STOP") {
        command = msg.charAt(0);
        num = msg.substring(2);
        value = num.toFloat();
      }
    }

    if (command == 'F') {
      for(int i = 0; i < value/5; i++) {
        forward(5);
        distance += 5;
        client.print("DIST:");
        client.println(distance);
        command = 'q';
      }
      client.println("DONE");
    }
  }
  if (command == 'L'){
    spinLeft(1000);
    client.println("DONE");
    command = 'q';
  }

  if (command == 'R'){
    spinRight(1000);
    client.println("DONE");
    command = 'q';
  }
  */
  forward(200, left, right);
  delay(2000);
/* Bronze challenge remains
  WiFiClient newClient = server.available(); 
  if (newClient) {
    client = newClient;  // only overwrite when there's actually a new connection
  }

  if (client && client.connected()) {
    if (client.available()) { //only try to read when there's data
      msg = client.readStringUntil('\n'); 
      msg.trim();

      if (msg == "Forward") mode = 'F';
      else if (msg == "Stop") mode = 'S';
      else if (msg == "+L") left += 5;
      else if (msg == "-L") left -= 5;
      else if (msg == "+R") right += 5;
      else if (msg == "-R") right -= 5;
    }
  }
  String current_state = ""; // Track what is happening right now

  if (mode == 'F') {
    current_state = "Going Forward"; //default

    if (!Bogie()) {
      if (hadObject) {
        current_state = "Object Removed";
        hadObject = false;
      }
      
      if (Right_Error()) {
        while (Right_Error()) {
          Step_Left();
        }
        current_state = "Adjusting Left";
      }
      
      else if (Left_Error()) {
        while (Left_Error()) {
          Step_Right();
        }
        current_state = "Adjusting Right";
      }
      
      Mush(200, left, right);
    } 
    else {
      current_state = "Object in path";
      hadObject = true;
    }
  } 
  else {
    current_state = "Stopped";
  }

  // Only send a message if it is different from the last one we sent
  if (current_state != "" && current_state != last_printed_state) {
    if (client && client.connected()) {
      client.println(current_state);
    }
    last_printed_state = current_state; 
  }
*/
}