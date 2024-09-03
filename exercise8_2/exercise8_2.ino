int count = 0; // ประกาศตัวแปร count เป็น 0
bool SW0_Value; // ประกาศตัวแปร SW0_Value เป็นตัวแปรสำหรับรับ input
bool SW1_Value; // ประกาศตัวแปร SW1_Value เป็นตัวแปรสำหรับรับ input
bool SW2_Value; // ประกาศตัวแปร SW2_Value เป็นตัวแปรสำหรับรับ input
bool SW3_Value; // ประกาศตัวแปร SW3_Value เป็นตัวแปรสำหรับรับ input

void setup() {
  pinMode(2, INPUT); // ตั้งค่า pin 2 เป็น input
  pinMode(3, INPUT); // ตั้งค่า pin 3 เป็น input
  pinMode(10, INPUT); // ตั้งค่า pin 10 เป็น input
  pinMode(11, INPUT); // ตั้งค่า pin 11 เป็น input
  Serial.begin(9600); // กำหนด baud rate ของการส่งข้อมูลแบบ serial communication
}

void loop() {
  SW0_Value = digitalRead(10); // อ่านค่าจาก pin 10 เก็บไว้ในตัวแปร SW0_Value
  SW1_Value = digitalRead(11); // อ่านค่าจาก pin 11 เก็บไว้ในตัวแปร SW1_Value
  SW2_Value = digitalRead(2); // อ่านค่าจาก pin 2 เก็บไว้ในตัวแปร SW2_Value
  SW3_Value = digitalRead(3); // อ่านค่าจาก pin 3 เก็บไว้ในตัวแปร SW3_Value

  if (!SW0_Value + !SW1_Value + !SW2_Value + !SW3_Value >= 2){ // ถ้าค่าของ switch เป็น low มากกว่า 2 
    Serial.println("SOS"); // ส่งข้อความว่า SOS ผ่าน serial communication
    delay(100); // หน่วงเวลา 0.1 วินาที
  }

  count = count + 1; // เพิ่มค่า count 1
  if (count >= 1000) count = 0; // ถ้าค่าในตัวแปร count มากกว่าเท่ากับ 1000 กำหนดให้ count = 0
  delay(100); // หน่วงเวลา 0.1 วินาที
}



