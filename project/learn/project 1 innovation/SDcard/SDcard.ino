#include<SPI.h>
#include<SD.h>

File myFile;
const int chipSelect = 4;

void setup(){
  Serial.begin(9600);
  Serial.println("Initializing SD card ...");
  pinMode(SS, OUTPUT);

  if (!SD.begin(chipSelect)){
    Serial.println("Initialzation failed!");
    return ;
  }
  Serial.println("Initialization done.");

  if (SD.exists("test.txt")) SD.remove("test.txt");
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile){
    myFile.println("1, 2, 3");
    myFile.close();
  }
  else Serial.println("error opening test.txt");

  myFile = SD.open("test.txt", FILE_READ);
  if (myFile){
    while (myFile.available()){
      Serial.write(myFile.read());
    }
    myFile.close();
  }
  else Serial.println("error opening test.txt");
}

void loop(){

}