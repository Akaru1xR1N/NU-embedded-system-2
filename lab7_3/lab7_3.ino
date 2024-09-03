int LED_Pins[] = {4,5,6,7,8,9,10,11}; // กำหนด array ของ pin LED
int pinSW0 = 2; // กำหนดตัวแปรสำหรับ pin switch 0
int pinSW1 = 3; // กำหนดตัวแปรสำหรับ pin switch 1
int valueSW0 = 1; // ตัวแปรสำหรับเก็บค่าจาก switch 0
int valueSW1 = 1; // ตัวแปรสำหรับเก็บค่าจาก switch 1
int stateSW0 = 0; // กำหนดตัวแปร stateSW0 แทน state ของ switch 0
int stateSW1 = 0; // กำหนดตัวแปร stateSW1 แทน state ของ switch 1
int pinCount = 8; // กำหนดตัวแปรสำหรับเก็บจำนวนของ LED
int timer = 1000; // กำหนดตัวแปร timer สำหรับหน่วงเวลา

void setup() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++){ // ลูปสำหรับประกาศขา pin เป็น output
    pinMode(LED_Pins[thisPin], OUTPUT); // ตั้งค่าให้ขา pin นั้นๆเป็น output
  }
  pinMode(pinSW0, INPUT_PULLUP); // ตั้งค่าให้ค่าในตัวแปร pinSW0 เป็น input
  pinMode(pinSW1, INPUT_PULLUP); // ตั้งค่าให้ค่าในตัวแปร pinSW1 เป็น input
}

void loop() {
  valueSW0 = digitalRead(pinSW0); // อ่านค่าจาก pinSW0 และเก็บไว้ที่ valueSW0
  valueSW1 = digitalRead(pinSW1); // อ่านค่าจาก pinSW1 และเก็บไว้ที่ valueSW1

  if ((stateSW0 == 0) && (valueSW0 == LOW)) stateSW0 = 1; // เมื่อ stateSW0 เป็น 0 และ ค่าของ valueSW0 เป็น low ตั้งค่าให้ stateSW0 = 1
  else if ((stateSW0 == 1) && (valueSW0 == LOW)) stateSW0 = 0; // เมื่อ stateSW0 เป็น 1 และ ค่าของ valueSW0 เป็น low ตั้งค่าให้ stateSW0 = 0
  if ((stateSW1 == 0) && (valueSW1 == LOW)) stateSW1 = 1; // เมื่อ stateSW1 เป็น 0 และ ค่าของ valueSW1 เป็น low ตั้งค่าให้ stateSW1 = 1
  else if ((stateSW1 == 1) && (valueSW1 == LOW)) stateSW1 = 0; // เมื่อ stateSW1 เป็น 1 และ ค่าของ valueSW1 เป็น low ตั้งค่าให้ stateSW1 = 0
  if (stateSW0 == 1){ // ถ้า stateSW0 = 1
    if (stateSW1 == 0) LED_R_to_L(); // ถ้า stateSW1 = 0 เรียก function LED_R_to_L()
    else LED_L_to_R(); // ถ้า stateSW1 != 0 เรียก function LED_L_to_R()
  }
}

void LED_R_to_L(){ // function LED_R_to_L
  for (int thisPin = 0; thisPin < pinCount; thisPin++){ // ลูปไล่ค่าจาก LED น้อยไปมาก
    digitalWrite(LED_Pins[thisPin], HIGH); // ตั้งค่าให้ขา pin นั้นๆเป็น high
    delay(timer); // หน่วงเวลา
    digitalWrite(LED_Pins[thisPin], LOW); // ตั้งค่าให้ขา pin นั้นๆเป็น low
  }
}

void LED_L_to_R(){ // function LED_L_to_R
  for (int thisPin = pinCount-1; thisPin >= 0; thisPin--){ // ลูปไล่ค่าจาก LED มากไปน้อย
    digitalWrite(LED_Pins[thisPin], HIGH); // ตั้งค่าให้ขา pin นั้นๆเป็น high
    delay(timer); // หน่วงเวลา
    digitalWrite(LED_Pins[thisPin], LOW); // ตั้งค่าให้ขา pin นั้นๆเป็น low
  }
}








