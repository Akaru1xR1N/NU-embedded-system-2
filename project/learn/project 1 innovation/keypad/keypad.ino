#include<Keypad.h>

char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[4] = {9, 8, 7, 6};
byte colPins[4] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

void setup(){
  Serial.begin(9600);
  Serial.println("Please Enter Key: ");
}

void loop(){
  char key = keypad.getKey();
  if (key != NO_KEY) Serial.println(key);
}