#include<Wire.h>

void setup() {
  Wire.begin(2);
  Serial.begin(9600);
  // Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

// void requestEvent(){
//   Wire.write("Hello Bright.\n");
// }

void receiveEvent(){
  while (Wire.available() > 1){
    char c = Wire.read();
    Serial.print(c);
  }
  int x = Wire.read();
  Serial.print(": ");
  Serial.println(x);
}