bool SW0_Value; // ประกาศตัวแปร SW0_Value เป็นตัวแปรสำหรับรับ input
bool SW1_Value; // ประกาศตัวแปร SW1_Value เป็นตัวแปรสำหรับรับ input

void setup() {
  pinMode(10, INPUT); // ตั้งค่า pin 10 เป็น input
  pinMode(11, INPUT); // ตั้งค่า pin 11 เป็น input
  Serial.begin(9600); // กำหนด baud rate ของการส่งข้อมูลแบบ serial communication
}

void loop() {
  SW0_Value = digitalRead(10); // อ่านค่าจาก pin 10 เก็บไว้ในตัวแปร SW0_Value
  SW1_Value = digitalRead(11); // อ่านค่าจาก pin 11 เก็บไว้ในตัวแปร SW1_Value
  if (SW0_Value == LOW){ // ถ้า SW0_Value เป็น LOW
    Serial.print("SW1 is "); // ส่งข้อความว่า SW1 is  ผ่าน serial communication
    Serial.println(SW1_Value); // ส่งค่าที่อยู่ในตัวแปร SW1_value และขึ้นบรรทัดใหม่
    delay(500); // หน่วงเวลา 0.5 วินาที
  }
}



