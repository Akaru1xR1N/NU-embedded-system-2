#include<Wire.h>
#include <LiquidCrystal_I2C.h>
#include"DHT.h"

LiquidCrystal_I2C lcd(0x3F, 16, 2);
DHT dht(4, DHT11);

float DHTData[2]; // Humidity and Temperature

void setup() {
  Wire.begin(1);
  lcd.init();
  dht.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Humid    Temp");
  Serial.begin(9600);
}

void loop() {
  DHTData[0] = dht.readHumidity();
  DHTData[1] = dht.readTemperature();

  lcd.setCursor(1, 1);
  lcd.print(DHTData[0]);
  lcd.print("% ");
  lcd.print(DHTData[1]);
  lcd.print(" C");

  // Wire.requestFrom(2, 14);
  // Serial.println(Wire.available());
  // while (Wire.available()){
  //   char c = Wire.read();
  //   // Serial.print(c);
  // }
  Wire.beginTransmission(2);
  Wire.write("Hello World");
  Wire.write(256);
  Wire.endTransmission();

  delay(1000);
}
