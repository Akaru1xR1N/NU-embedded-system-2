#include"DHT.h"
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
DHT dht(5, DHT11);
SoftwareSerial btSerial(8, 9);

class Handler{
  private:
    String state; // state = {CLOSE, START_VERIFICATION, VERIFICATION, OPEN}
    uint8_t selector;
    uint8_t nameCount;
    String nameResult;
    String userPassword;
    bool getData = false;
    bool requestFlag = false;
    bool passwordFlag = false;
    bool serialFlag = false;
    bool bluetoothFlag = false;
    bool testFlag = false;
    char c;

    void sendBluetoothData(String packet){
      // send some data via bluetooth channel
      btSerial.write(packet.c_str());
    }

    void recvBluetoothData(){
      // receive some data via bluetooth channel
      header = "";
      content = "";
      bool contentFlag = false;
      while (btSerial.available()){
        c = btSerial.read();
        if (c == separatorChar) {
          contentFlag = true;
          continue;
        }
        if (!contentFlag) header = String(header + String(c));
        else content = String(content + String(c));
      }
    }

    bool btPing(){
      // ping via bluetooth channel
      testFlag = false;
      for (uint8_t i = 0; i < 3; i++){
        sendBluetoothData(createPacket("btPing", String(i)));
        delay(250);
        recvBluetoothData();
        delay(250);
        if (header == "btPong"){
          clearPrevPacket();
          testFlag = true;
          return true;
        }
        Serial.print("Header: ");
        Serial.println(header);
        Serial.print("Content: ");
        Serial.println(content);
      }
      testFlag = true;
      return false;
    }

    void sendSerialData(String packet){
      // send some data via serial communication port
      Serial.println(packet);
    }

    void recvSerialData(){
      // receive some data via serial communication port
      header = "";
      content = "";
      bool contentFlag = false;
      while (Serial.available()){
        c = Serial.read();
        if (c == separatorChar) {
          contentFlag = true;
          continue;
        }
        if (!contentFlag) header = String(header + String(c));
        else content = String(content + String(c));
      }
    }

    bool serialPing(){
      // ping via serial communication port
      testFlag = false;
      for (uint8_t i = 0; i < 3; i++){
        sendSerialData(createPacket("serialPing", String(i)));
        delay(250);
        recvSerialData();
        delay(250);
        if (header == "serialPong"){
          clearPrevPacket();
          testFlag = true;
          return true;
        }
      }
      testFlag = true;
      return false;
    }
    
    void testConnection(){
      serialFlag = false;
      bluetoothFlag = false;
      testFlag = false;
      while (!testFlag) {
        if (serialPing()) serialFlag = true;
      }
      clearPrevPacket();
      testFlag = false;
      while (!testFlag){
        if (btPing()) bluetoothFlag = true;
      }
      clearPrevPacket();
    }
    
    void showDHTData(){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Current Hum&Tmp.");
      lcd.setCursor(0, 1);
      lcd.print(dht.readHumidity());
      lcd.print(" %  ");
      lcd.print(dht.readTemperature());
      lcd.print(" C");
    }

    void showInitInfo(){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Press start but");
      lcd.setCursor(0, 1);
      lcd.print("ton to continue..");
    }

    void showName(String selectName){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("user : ");
      lcd.print(selector+1);
      lcd.setCursor(0, 1);
      lcd.print(selectName);
    }

    String createPacket(String header, String content, char separator='&'){
      return String(header + String(separator) + content).c_str();
    }

    void clearPrevPacket(){
      header = "";
      content = "";
    }

    void getUserInputPassword(){
      userPassword = "";
      requestFlag = false;
      if (!requestFlag){
        String packet = createPacket("requestPassword", "None");
        Serial.println(packet);

        Wire.beginTransmission(2);
        Wire.write(packet.c_str());
        Wire.endTransmission();
        requestFlag = !requestFlag;
      }
      passwordFlag = false;
      while (!passwordFlag){
        if (header != "responsePassword") continue;
        else if (header == "responsePassword") {
          userPassword = content;
          clearPrevPacket();
          passwordFlag = true;
        }
      }
    }

    void invalidPassword(){
      // make sound noise
      Wire.beginTransmission(2);
      Wire.write(String("beepstart" + String(separatorChar) + "None").c_str());
      Wire.endTransmission();

      delay(5000);
      Wire.beginTransmission(2);
      Wire.write(String("beepstop" + String(separatorChar) + "None").c_str());
      Wire.endTransmission();
      setState("CLOSE");
    }

    void openDoor(){
      while (analogRead(A0) < 200){
        Serial.println(analogRead(A0));
        digitalWrite(motor1, HIGH);
        digitalWrite(motor2, LOW);
      }
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
      uint8_t open = 0;
      while (open <= 20){
        if (getDistance() <= satisfiedRange){
          open = 0;
        }
        else {
          open++;
        }
        delay(250);
      }
    }

    void closeDoor(){
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, HIGH);
      delay(500);
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
    }

  public:
    uint8_t startSW = 2;
    uint8_t selectSW = 6;
    uint8_t trigger = 7;
    uint8_t echo = 4;
    uint8_t motor1 = 10;
    uint8_t motor2 = 11;
    uint8_t en = 12;
    uint8_t sound = 13;
    uint8_t satisfiedRange = 70;
    char separatorChar = '&';
    String header;
    String content;

    void setState(String newState){
      state = newState;
    }

    String getState(){
      return state;
    }

    void setDataValue(bool newBool){
      getData = newBool;
    }

    bool getDataValue(){
      return getData;
    }

    void setPassword(String pwd){
      userPassword = pwd;
    }

    uint8_t increaseSelectorValue(){
      if (++selector >= nameCount) selector = 0;
      return selector;
    }
    
    void initState(){
      showDHTData();
      delay(1500);
      if (state != "CLOSE") return;
      showInitInfo();
      delay(1500);
    }

    void startVerificationState(){
      String data;
      testConnection();
      if (serialFlag){
        for (uint8_t i = 0; i < 3; i++){
          sendSerialData(createPacket("getUsernameSer", String(i)));
          delay(250);
          clearPrevPacket();
          recvSerialData();
          delay(250);
          if (header == "getUsernameResultSer"){
            Serial.println("START ---------FROM ARDUINO----------");
            Serial.print("Header: ");
            Serial.println(header);
            Serial.print("Content: ");
            Serial.println(content);
            Serial.println("END   ---------FROM ARDUINO----------");
            data = content;
            clearPrevPacket();
            break;
          }
        }
      }
      else if (bluetoothFlag) {
        for (uint8_t i = 0; i < 3; i++){
          sendBluetoothData(createPacket("getUsernameBT", String(i)));
          delay(250);
          clearPrevPacket();
          recvBluetoothData();
          delay(250);
          if (header == "getUsernameResultBT"){
            Serial.println("START ---------FROM ARDUINO----------");
            Serial.print("Header: ");
            Serial.println(header);
            Serial.print("Content: ");
            Serial.println(content);
            Serial.println("END   ---------FROM ARDUINO----------");
            data = content;
            clearPrevPacket();
            break;
          }
        }
      }
      else {
        // error cannot use serial communication and bluetooth
        // do something here to handle with error

        // solution
        // show info to lcd then waiting for user press reset button
        // to go to initState
      }
        // "OWNER&akarui"
        // String data = "OWNER&akarui&Rin"; // get the data from bluetooth or serial communication
        // String data = OWNER$akarui;

        // START ----------------------------------- SPLIT NAME FROM PLAIN DATA -----------------------------------
        setDataValue(false);
        nameCount = 1;
        selector = 0;
        uint8_t indexForSeparatorIndex = 0;
        uint32_t strlen = data.length();

        // find name count
        for (uint32_t i = 0; i < strlen; i++){
          if (data[i] == '$') nameCount += 1;
        }

        uint32_t separatorIndex[nameCount-1];
        // find seperator index
        for (uint32_t i = 0; i < strlen; i++){
          if (data[i] == '$') separatorIndex[indexForSeparatorIndex++] = i;
        }

        String name[nameCount];
        // store the name to name array
        for (uint8_t i = 0; i < nameCount; i++){
          if (i == 0) name[i] = data.substring(0, separatorIndex[i]);
          else if (i == nameCount-1) name[i] = data.substring(separatorIndex[i-1]+1, strlen);
          else name[i] = data.substring(separatorIndex[i-1]+1, separatorIndex[i]);
        }
        // END   ----------------------------------- SPLIT NAME FROM PLAIN DATA -----------------------------------
        setDataValue(true);
        showName(name[0]);
        while (true){
          if (digitalRead(selectSW) == LOW){
            showName(name[increaseSelectorValue()]);
          }
          nameResult = name[selector];
          if (state != "START_VERIFICATION") break;
          delay(100);
        }
    }

    void verificationState(){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter ");
      lcd.print(nameResult);
      lcd.print("'s");
      lcd.setCursor(0, 1);
      lcd.print("Password...");
      // send nameResult as username and add password after add separatorChar
      getUserInputPassword();
      Serial.print("Password: ");
      Serial.println(userPassword);
      testConnection();
      if (serialFlag){
        for (uint8_t i = 0; i < 3; i++){
          sendSerialData(createPacket("checkUsernamePasswordSer", String(nameResult + "&" + userPassword)));
          delay(250);
          clearPrevPacket();
          recvSerialData();
          delay(250);
          if (header == "checkUsernamePasswordResultSer"){
            Serial.println("START ---------FROM ARDUINO----------");
            Serial.print("Header: ");
            Serial.println(header);
            Serial.print("Content: ");
            Serial.println(content);
            Serial.println("END   ---------FROM ARDUINO----------");
            if (content == "True" || content.substring(0, 4) == "True"){
              setState("OPEN");
              clearPrevPacket();
              return;
            }
            else {
              clearPrevPacket();
              invalidPassword();
              return;
            }
          }
        }
      }
      else if (bluetoothFlag){
        for (uint8_t i = 0; i < 3; i++){
          sendBluetoothData(createPacket("checkUsernamePasswordBT", String(nameResult + "&" + userPassword)));
          delay(250);
          clearPrevPacket();
          recvBluetoothData();
          delay(250);
          if (header == "checkUsernamePasswordResultBT"){
            Serial.println("START ---------FROM ARDUINO----------");
            Serial.print("Header: ");
            Serial.println(header);
            Serial.print("Content: ");
            Serial.println(content);
            Serial.println("END   ---------FROM ARDUINO----------");
            if (content == "True"){
              setState("OPEN");
              clearPrevPacket();
              return;
            }
            else {
              clearPrevPacket();
              invalidPassword();
              return;
            }
          }
        }
      }
      else {
        // error cannot use serial communication and bluetooth
        // do something here to handle with error

        // solution
        // show info to lcd then waiting for user press reset button
        // to go to initState
      }
    }

    void SDCard(){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Using SD card");
      lcd.setCursor(0, 1);
      lcd.print("waiting...");

      userPassword.replace('$', '&');
      
      testConnection();
      if (serialFlag){
        for (uint8_t i = 0; i < 3; i++){
          sendSerialData(createPacket("checkUsernamePasswordSer", String(userPassword)));
          delay(250);
          clearPrevPacket();
          recvSerialData();
          delay(250);
          if (header == "checkUsernamePasswordResultSer"){
            Serial.println("START ---------FROM ARDUINO----------");
            Serial.print("Header: ");
            Serial.println(header);
            Serial.print("Content: ");
            Serial.println(content);
            Serial.println("END   ---------FROM ARDUINO----------");
            if (content == "True" || content.substring(0, 4) == "True"){
              setState("OPEN");
              clearPrevPacket();
              return;
            }
            else {
              clearPrevPacket();
              invalidPassword();
              return;
            }
          }
        }
      }
      else if (bluetoothFlag){
        for (uint8_t i = 0; i < 3; i++){
          sendBluetoothData(createPacket("checkUsernamePasswordBT", String(userPassword)));
          delay(250);
          clearPrevPacket();
          recvBluetoothData();
          delay(250);
          if (header == "checkUsernamePasswordResultBT"){
            Serial.println("START ---------FROM ARDUINO----------");
            Serial.print("Header: ");
            Serial.println(header);
            Serial.print("Content: ");
            Serial.println(content);
            Serial.println("END   ---------FROM ARDUINO----------");
            if (content == "True"){
              setState("OPEN");
              clearPrevPacket();
              return;
            }
            else {
              clearPrevPacket();
              invalidPassword();
              return;
            }
          }
        }
      }
      else {
        // error cannot use serial communication and bluetooth
        // do something here to handle with error

        // solution
        // show info to lcd then waiting for user press reset button
        // to go to initState
        clearPrevPacket();
        setState("CLOSE");
      }
    }

    void openState(){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The door is");
      lcd.setCursor(0, 1);
      lcd.print("OPENING...");

      openDoor();

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The door is");
      lcd.setCursor(0, 1);
      lcd.print("CLOSING...");

      closeDoor();
      setState("CLOSE");
    }

    uint16_t getDistance(){
      long duration, cm;
      pinMode(echo, OUTPUT);
      digitalWrite(echo, HIGH);
      delayMicroseconds(5);
      digitalWrite(echo, LOW);
      pinMode(trigger, INPUT);
      duration = pulseIn(trigger, HIGH);
      cm = duration / 29 / 2;
      return cm;
    }
};

Handler handler;

String currentState;

void setup() {
  pinMode(handler.startSW, INPUT_PULLUP);
  pinMode(handler.selectSW, INPUT_PULLUP);
  pinMode(handler.motor1, OUTPUT);
  pinMode(handler.motor2, OUTPUT);
  pinMode(handler.sound, OUTPUT);
  pinMode(handler.en, OUTPUT);
  digitalWrite(handler.en, HIGH);
  attachInterrupt(digitalPinToInterrupt(handler.startSW), startVerification, FALLING);

  Serial.begin(9600);
  btSerial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  Wire.begin(1);
  Wire.onReceive(receiveEvent);

  Serial.println("From setup");

  handler.setState("CLOSE");
}

void loop() {
  currentState = handler.getState();

  if (currentState == "CLOSE") handler.initState();
  if (currentState == "START_VERIFICATION") handler.startVerificationState();
  if (currentState == "VERIFICATION") handler.verificationState();
  if (currentState == "OPEN") handler.openState();
  if (currentState == "SDCARD") handler.SDCard();
  delay(250);
}

void startVerification(){
  if (handler.getDistance() <= handler.satisfiedRange && handler.getState() == "CLOSE") handler.setState("START_VERIFICATION");
  else if (handler.getDataValue() && handler.getState() == "START_VERIFICATION") handler.setState("VERIFICATION");
}

void(* resetFunc) (void) = 0;

void receiveEvent(){
  handler.header = "";
  handler.content = "";
  bool contentFlag = false;
  char c;
  while (Wire.available()){
    c = Wire.read();
    if (c == handler.separatorChar) {
      contentFlag = true;
      continue;
    }
    // Serial.write(c);
    if (!contentFlag) handler.header = String(handler.header + String(c));
    else handler.content = String(handler.content + String(c));
  }
  Serial.print("Header: ");
  Serial.println(handler.header);
  Serial.print("Content: ");
  Serial.println(handler.content);
  if (handler.header == "sdcard"){
    Serial.println(handler.content);
    handler.setState("SDCARD");
    handler.setPassword(handler.content);
    return;
  }
  if (handler.header == "reset"){
    resetFunc();
  }
}
