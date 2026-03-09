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

  analogWrite(leftPermission, 0);
  analogWrite(rightPermission, 0);
}

int right = 200;
int left = 200;
void loop() {
  forward(50);
  delay(20000);
  //int left_pulse = left_pulse_count();
  //Serial.print(left_pulse);
  //Serial.print("  ");
  //Serial.print(right_pulse);
  //Serial.println("");

  /*
  client = server.available (); //read in current command from client
  if (client){
    msg = client.readString();
    if (msg != ("") || msg[1] == 'F' || msg[1]=='S'){
      mode = msg[0];
    }
    if (msg[1]=='+') {
      if(msg[2]=='L') left += 5;
    }
    else right += 5;
    if (msg[1]=='-') {
      if(msg[2]=='L') left -= 5;
    }
    else right -= 5;
  }

  if(mode == 'F'){
    if (!Bogie()){
      while(Right_Error()){
        Step_Left();
      }
      while(Left_Error()){
        Step_Right();
      }
      
      Mush(200,left,right);
    }
  }
  
  */
  
}