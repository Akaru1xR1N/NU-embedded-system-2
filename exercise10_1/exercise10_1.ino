int LED_Pins[] = {4,5,6,7,8,9,10,11}; // กำหนด array ของ pin LED
int pinCount = 8; // กำหนดตัวแปรสำหรับเก็บจำนวนของ LED
int timer = 1000; // กำหนดตัวแปร timer สำหรับหน่วงเวลา
int LED_LtoR_Flg = 1; // flag สำหรับทำให้ LED วิ่งจากซ้ายไปขวา
int LED_Current = 0; // กำหนดตัวแปรสำหรับ LED ปัจจุบัน

char terminateChar = 'x'; // กำหนดตัวแปรสำหรับข้อความสำหรับจบการรับอักขระ

String inputString = ""; // กำหนดตัวแปรสำหรับรับข้อความ
bool stringComplete = false; // กำหนดตัวแปรสำหรับเช็คว่าข้อความนั้นเสร็จสมบูรณ์หรือไม่

void setup(){
  Serial.begin(9600); // กำหนด baud rate ของการส่งข้อมูลแบบ serial communication
  inputString.reserve(200); // กำหนดให้ตัวแปร inputString รอรับข้อความสำหรับ 200 อักขระ

  for (int thisPin = 0; thisPin < pinCount; thisPin++){ // ลูปสำหรับประกาศขา pin เป็น output
    pinMode(LED_Pins[thisPin], OUTPUT); // ตั้งค่าให้ขา pin นั้นๆเป็น output
  }
}

void loop(){
  LED_Running(LED_Lto_R_Flg); // เรียกใช้ฟังก์ชั่น LED_Running

  if (stringComplete){ // ถ้าตัวแปร stringComplete เป็นจริง
    Serial.println(inputString); // ส่งค่า inputString ผ่านทางการสื่อสารอนุกรม
    serialDataProcess(inputString); // เรียกใช้ฟังก์ชัน serialDataProcess

    inputString = ""; // กำหนดให้ตัวแปร inputString เป็น ข้อความว่างเปล่า
    stringComplete = false; // กำหนดให้ตัวแปร stringComplete เป็น false
  }
}

void serialEvent(){ // function serialEvent
  while (Serial.available()){ // เมื่อค่าของจำนวนอักขระมากกว่า 0
    char inChar = (char)Serial.read(); // กำหนดให้ตัวแปร inChar เท่ากับ อักขระที่อ่านจากการสื่อสารอนุกรม
    inputString += inChar; // เพิ่ม inChar เข้าไปที่ inputString

    if (inChar == terminateChar){ // ถ้า inChar เท่ากับ terminateChar
      stringComplete = true; // กำหนดให้ตัวแปร stringComplete เป็น true
    }
  }
}

void serialDataProcess(String data){ // function serialDataProcess
  data.replace(String(terminateChar), ""); // แทนที่อักขระที่อยู่ในตัวแปร data จากอักขระที่อยู่ในตัวแปร terminateChar เป็นข้อความว่างเปล่า
  data.replace(String('\n'), ""); // แทนที่อักขระที่อยู่ในตัวแปร data จากอักขระสำหรับขึ้นบรรทัดใหม่ เป็นข้อความว่างเปล่า
  Serial.println(data); // ส่งข้อความที่อยู่ในตัวแปร data ผ่านทางการสื่อสารอนุกรม
  if (data == "A"){ // ถ้า data เท่ากับ A
    LED_LtoR_Flg = 1; // กำหนดให้ LED_LtoR_Flg เป็น 1
  }
  else if (data == "B"){ // ถ้า data เท่ากับ B
    LED_LtoR_Flg = -1; // กำหนดให้ LED_LtoR_Flg เป็น -1
  }
  else if (data == "C"){ // ถ้า data เท่ากับ C
    LED_LtoR_Flg = 0; // กำหนดให้ LED_LtoR_Flg เป็น 0
  }
}

void LED_Running(int _LED_LtoR_Flg){ // function สำหรับทำให้ไฟวิ่ง
  for (int thisPin = 0; thisPin < pinCount; thisPin++){ // ลูปไล่ค่าจาก LED น้อยไปมาก
    digitalWrite(LED_Pins[thisPin], LOW); // ตั้งค่าให้ขา pin นั้นๆเป็น low
  }
  digitalWrite(LED_Pins[LED_Current], HIGH); // ตั้งค่าให้ขา pin ที่ LED_Current เป็น high
  delay(timer); // หน่วงเวลา

  if (_LED_LtoR_Flg == 1){ // ถ้า _LED_LtoR_Flg เป็น 1
    LED_Current = LED_Current+1; // LED_Current + 1
    LED_Current = LED_Current%8; // LED_Current % 8
  }
  else if (_LED_LtoR_Flg == -1){ // ถ้า _LED_LtoR_Flg เป็น -1
    LED_Current = LED_Current-1; // LED_Current - 1
    if (LED_Current < 0) {LED_Current = 7;} // ถ้า LED_Current น้อยกว่า 0 LED_Current = 7
  }
  else if (_LED_LtoR_Flg == 0){ // ถ้า _LED_LtoR_Flg เป็น 0
    return;
  }
}



