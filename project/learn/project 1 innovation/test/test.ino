#define ON LOW
#define OFF HIGH

int relay1 = 4;
int relay2 = 5;

void setup(){
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop(){
  digitalWrite(relay1, ON);
  digitalWrite(relay2, ON);
  delay(1000);
  digitalWrite(relay1, OFF);
  digitalWrite(relay2, OFF);
  delay(1000);
}

