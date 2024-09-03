int LED_Pins[] = {4,5,6,7,8,9,10,11}; // กำหนด array ของ pin LED
int pinSW0 = 2; // กำหนดตัวแปรสำหรับ pin switch 0
int pinSW1 = 3; // กำหนดตัวแปรสำหรับ pin switch 1
int pinCount = 8; // กำหนดตัวแปรสำหรับเก็บจำนวนของ LED
int timer = 1000; // กำหนดตัวแปร timer สำหรับหน่วงเวลา
int LED_LtoR_Flg = 1; // flag สำหรับทำให้ LED วิ่งจากซ้ายไปขวา
int LED_Current = 0; // กำหนดตัวแปรสำหรับ LED ปัจจุบัน

void setup(){
  for (int thisPin = 0; thisPin < pinCount; thisPin++){ // ลูปสำหรับประกาศขา pin เป็น output
    pinMode(LED_Pins[thisPin], OUTPUT); // ตั้งค่าให้ขา pin นั้นๆเป็น output
  }
  pinMode(pinSW0, INPUT_PULLUP); // ตั้งค่าให้ค่าในตัวแปร pinSW0 เป็น input
  pinMode(pinSW1, INPUT_PULLUP); // ตั้งค่าให้ค่าในตัวแปร pinSW1 เป็น input

  attachInterrupt(digitalPinToInterrupt(pinSW0), isr_EX0, FALLING); // สร้างอินเทอรัพที่พิน pinSW0 ให้ทำฟังก์ชัน isr_EX0 เมื่อเกิดขาลง
  attachInterrupt(digitalPinToInterrupt(pinSW1), isr_EX1, FALLING); // สร้างอินเทอรัพที่พิน pinSW0 ให้ทำฟังก์ชัน isr_EX1 เมื่อเกิดขาลง
}

void loop(){
  LED_Running(LED_Lto_R_Flg); // เรียกใช้ฟังก์ชั่น LED_Running
}

void isr_EX0(){ // function สำหรับ interrupt
  LED_LtoR_Flg = 1; // กำหนดให้ตัวแปร LED_LtoR_Flg เท่ากับ 1
}

void isr_EX1(){ // function สำหรับ interrupt
  LED_LtoR_Flg = -1; // กำหนดให้ตัวแปร LED_LtoR_Flg เท่ากับ -1
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
}



