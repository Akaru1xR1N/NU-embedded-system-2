#include<SoftwareSerial.h>

SoftwareSerial btSerial(4,5);

char c;
String text;
bool stringComplete;

void setup(){
  Serial.begin(9600);
  while (!Serial);
  btSerial.begin(9600);
}

void loop(){
  if (Serial.available()){
    btSerial.write(Serial.read());
  }
  if (btSerial.available()){
    // Serial.write(btSerial.read());
    c = btSerial.read();
    text += c;
    stringComplete = false;
  }
  else if (!btSerial.available()) stringComplete = true;
  if (stringComplete) stringHandler();
}

void stringHandler(){
  Serial.print(text);
  text = "";
}