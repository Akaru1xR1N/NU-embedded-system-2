#include<Wire.h>
#include<Keypad.h>

char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[4] = {11,10,9,8};
byte colPins[4] = {7,6,5,4};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

String header;
String content;
char separatorChar = '&';
String password;
int sound = 2;

void setup() {
  // reset switch 3
  pinMode(3, INPUT_PULLUP);
  pinMode(sound, OUTPUT);
  digitalWrite(sound, HIGH);
  attachInterrupt(digitalPinToInterrupt(3), ISR_reset, FALLING);

  Wire.begin(2);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  if (header == "requestPassword"){
    getPassword();
    clearPrevPacket();
    Wire.beginTransmission(1);
    Wire.write(String("responsePassword" + String(separatorChar) + password).c_str());
    Wire.endTransmission();
  }
  if (header == "reset"){
    sendResetMessage();
    clearPrevPacket();
  }
  if (header == "beepstart"){
    digitalWrite(sound, LOW);
    clearPrevPacket();
  }
  if (header == "beepstop"){
    digitalWrite(sound, HIGH);
    clearPrevPacket();
  }
}

void ISR_reset(){
  header = "reset";
}

void sendResetMessage(){
  header = "";
  Wire.beginTransmission(1);
  Wire.write(String("reset" + String(separatorChar) + "None").c_str());
  Wire.endTransmission();
}

void getPassword(){
  password = "";
  while (true){
    char key = keypad.getKey();
    if (key == NO_KEY) continue;
    if (key == '#') break;
    password = String(password + String(key));
  }
}

void receiveEvent(){
  header = "";
  content = "";
  bool contentFlag = false;
  while (Wire.available()){
    char c = Wire.read();
    if (c == separatorChar) {
      contentFlag = true;
      continue;
    }
    if (!contentFlag) header = String(header + String(c));
    else content = String(content + String(c));
  }
  Serial.print("Header: ");
  Serial.println(header);
  Serial.print("Content: ");
  Serial.println(content);
}

void clearPrevPacket(){
  header = "";
  content = "";
}
