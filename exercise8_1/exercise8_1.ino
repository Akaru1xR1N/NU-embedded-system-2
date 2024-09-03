int count = 0; // ประกาศตัวแปร count เป็น 0
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
    Serial.println("Thanadej"); // ส่งข้อความว่า Thanadej ผ่าน serial communication
    delay(100); // หน่วงเวลา 0.1 วินาที
  }
  if (SW1_Value == LOW){ // ถ้า SW1_Value เป็น LOW
    Serial.println("64362609"); // ส่งข้อความว่า 64362609 ผ่าน serial communication
    delay(100); // หน่วงเวลา 0.1 วินาที
  }

  count = count + 1; // เพิ่มค่า count 1
  if (count >= 1000) count = 0; // ถ้าค่าในตัวแปร count มากกว่าเท่ากับ 1000 กำหนดให้ count = 0
  delay(100); // หน่วงเวลา 0.1 วินาที
}



