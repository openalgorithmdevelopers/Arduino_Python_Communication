/*  
  Bit pattern for transmission #
  from left to right
  First Bit: Information type
  Second Bit: Information type
  Third Bit: Information type
  000 for button
  010 for IMU
  111 or 224 for Joystick X
  110 or 192 for Joystick Y
  Others are reserved

  If Joystick: 
  Fourth - Eight Bit: Value of Joystick
*/

int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
byte mapX = 0;
byte mapY = 0;

void setup() {
 Serial.begin(9600);
   pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 

}

void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  /*
    mapX = map(xPosition, 0, 1023, -512, 31);
    mapY = map(yPosition, 0, 1023, -512, 512);
  */
  mapX = map(xPosition, 0, 1023, 0, 31);
  mapY = map(yPosition, 0, 1023, 0, 31);

  sendJoyStickX(mapX);
  sendJoyStickY(mapY);

  //Serial.println(mapX);
  //Serial.println(mapY);
  
  delay(100);
//  Serial.println("data from HC 05");
}

void sendJoyStickX(int mapX){
  byte flagBit = 224;
  Serial.println(flagBit|mapX); // ensure that mapX dont have top 3 MSB set
}

void sendJoyStickY(int mapY){
  byte flagBit = 192;
  Serial.println(flagBit|mapY); // ensure that mapX dont have top 3 MSB set
}
