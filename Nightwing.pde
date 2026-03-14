import processing.net.*;
Client myClient;
String data, mode;
String lastData = "";

int startX = 300;
int startY = 200;
int startW = 200;
int startH = 100;
int stopX = 300;
int stopY = 400;
int stopW = 200;
int stopH = 100;

void button( String btn, int x, int y,int w,int h, int r ,int g ,int b){
  rectMode(CENTER);
  stroke(255);
  fill(r,g,b);
  rect(x,y,w,h);
  fill(0,0,0);
  textSize(25);
  textAlign(CENTER);
  text(btn,x,y,w,h);
}

boolean hovering(int x,int y,int w,int h){
  return mouseX > x - (w/2) && mouseX < x+(w/2) && mouseY>y-(h/2) && mouseY < y + (h/2);
}


void setup(){
  windowTitle("Alfred");
  size(1000,500);
  mode = "Stop";
  myClient = new Client(this,"192.168.4.1",5200);
  println("I hear you Oracle");
  myClient.write("Gotham Needs You\n");
}

void draw(){
  background(200);
  
  // Update: Read until newline and check length to prevent empty strings from wiping the display
  data = myClient.readStringUntil('\n'); 
  if(data != null){ 
    String trimmedData = data.trim();
    if(trimmedData.length() > 0){
      lastData = trimmedData;
      print("Status: ");
      println(lastData);
    }
  }

  // Always display the last known status
  fill(0);
  textSize(20);
  textAlign(LEFT);
  text("Status: " + lastData, 650, 150);

  button("Start",startX,startY,startW,startH,0,255,0);
  button("Stop",stopX,stopY,stopW,stopH,255,0,0);
  button("+R",850,300,50,50,0,255,0);
  button("+L",750,300,50,50,0,255,0);
  button("-R",850,400,50,50,255,0,0);
  button("-L",750,400,50,50,255,0,0);
  
  if (mousePressed){
    if (hovering(startX,startY,startW,startH)){
      myClient.write("Forward\n");
    }
    if (hovering(stopX,stopY,stopW,stopH)){
      myClient.write("Stop\n");
    }
    if (hovering(850,300,50,50)){
      myClient.write("+R\n");
    }
    if (hovering(750,300,50,50)){
      myClient.write("+L\n");
    }
    if (hovering(850,400,50,50)){
      myClient.write("-R\n");
    }
    if (hovering(750,400,50,50)){
      myClient.write("-L\n");
    }
  }
}
