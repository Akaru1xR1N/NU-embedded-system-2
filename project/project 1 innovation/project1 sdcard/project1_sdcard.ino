#include<SPI.h>
#include<SD.h>
#include<Wire.h>

File myFile;
const int chipSelect = 4;

String header;
String content;
char separatorChar = '&';
String usernameAndPassword = "";
bool sendFlag = false;

int led = 5;

void setup() {
  pinMode(led, OUTPUT);
  Wire.begin(3);
  Serial.begin(9600);
}

void loop() {
  if (analogRead(A0) <= 50){
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
  sdcard();
  if (sendFlag){
    Wire.beginTransmission(1);
    Wire.write(String("sdcard" + String(separatorChar) + usernameAndPassword).c_str());
    Wire.endTransmission();
    Serial.println("Sending data");
    sendFlag = false;
  }
  delay(500);
}

void sdcard(){
  sendFlag = false;
  pinMode(SS, OUTPUT);
  
  if (!SD.begin(chipSelect)) return;

  if (!SD.exists("password.txt")) return;

  myFile = SD.open("password.txt", FILE_READ);
  char c;
  usernameAndPassword = "";
  if (myFile){
    while (myFile.available()){
      c = myFile.read();
      usernameAndPassword = String(usernameAndPassword + String(c));
    }
    myFile.close();
  }
  else return;
  Serial.println(usernameAndPassword);
  sendFlag = true;
  Serial.println(usernameAndPassword);
}

void sendData(String data){
  Wire.beginTransmission(1);
  Wire.write(String("sdcard" + String(separatorChar) + data).c_str());
  Wire.endTransmission();
}