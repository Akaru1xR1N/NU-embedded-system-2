int LED_Pins[] = {4,5,6,7,8,9,10,11}; // กำหนด array ของ pin LED
int pinSW0 = 2; // กำหนดตัวแปรสำหรับ pin switch 0
int pinSW1 = 3; // กำหนดตัวแปรสำหรับ pin switch 1
int pinCount = 8; // กำหนดตัวแปรสำหรับเก็บจำนวนของ LED
int timer = 1000; // กำหนดตัวแปร timer สำหรับหน่วงเวลา

void setup() {
  for (int thisPin = 0;thisPin < pinCount; thisPin++){ // ลูปสำหรับประกาศขา pin เป็น output
    pinMode(LED_Pins[thisPin], OUTPUT); // ตั้งค่าให้ขา pin นั้นๆเป็น output
  }
  pinMode(pinSW0, INPUT_PULLUP); // ตั้งค่าให้ค่าในตัวแปร pinSW0 เป็น input
  pinMode(pinSW1, INPUT_PULLUP); // ตั้งค่าให้ค่าในตัวแปร pinSW1 เป็น input
}

void loop() {
  if (digitalRead(pinSW0) == LOW) LED_R_to_L(); // เมื่อ pinSW0 เป็น low เรียก function LED_R_to_L()
  else if (digitalRead(pinSW1) == LOW) LED_L_to_R(); // เมื่อ pinSW1 เป็น low เรียก function LED_L_to_R()
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





