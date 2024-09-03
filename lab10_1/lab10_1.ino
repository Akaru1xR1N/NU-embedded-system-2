int LED_Pins[] = {4,5,6,7,8,9,10,11}; // กำหนด array ของ pin LED
int pinSW0 = 2; // กำหนดตัวแปรสำหรับ pin switch 0
int pinCount = 8; // กำหนดตัวแปรสำหรับเก็บจำนวนของ LED
int timer = 1000; // กำหนดตัวแปร timer สำหรับหน่วงเวลา

void setup(){
  Serial.begin(9600); // กำหนด baud rate ของการส่งข้อมูลแบบ serial communication
  for (int thisPin = 0; thisPin < pinCount; thisPin++){ // ลูปสำหรับประกาศขา pin เป็น output
    pinMode(LED_Pins[thisPin], OUTPUT); // ตั้งค่าให้ขา pin นั้นๆเป็น output
  }
  pinMode(pinSW0, INPUT_PULLUP); // ตั้งค่าให้ค่าในตัวแปร pinSW0 เป็น input
  attachInterrupt(digitalPinToInterrupt(pinSW0), isr_EX0, FALLING); // สร้างอินเทอรัพที่พิน pinSW0 ให้ทำฟังก์ชัน isr_EX0 เมื่อเกิดขาลง
}

void loop(){
  LED_R_to_L(); // เรียกใช้ฟังก์ชั่น LED_R_to_L()
}

void isr_EX0(){
  Serial.println("Hello World"); // ส่งข้อความว่า Hello World ผ่าน serial communication
}

void LED_R_to_L(){ // function LED_R_to_L
  for (int thisPin = 0; thisPin < pinCount; thisPin++){ // ลูปไล่ค่าจาก LED น้อยไปมาก
    digitalWrite(LED_Pins[thisPin], HIGH); // ตั้งค่าให้ขา pin นั้นๆเป็น high
    delay(timer); // หน่วงเวลา
    digitalWrite(LED_Pins[thisPin], LOW); // ตั้งค่าให้ขา pin นั้นๆเป็น low
  }
}




