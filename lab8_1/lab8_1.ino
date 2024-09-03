int count = 0; // ประกาศตัวแปร count เป็น 0

void setup() {
  Serial.begin(9600); // กำหนด baud rate ของการส่งข้อมูลแบบ serial communication
}

void loop() {
  Serial.print("Hello World "); // ส่งข้อความว่า Hello World ผ่าน serial communication
  Serial.println(count); // ส่งค่าที่อยู่ในตัวแปร count
  count = count + 1; // เพิ่มค่า count 1
  if (count >= 1000) count = 0; // ถ้าค่าในตัวแปร count มากกว่าเท่ากับ 1000 กำหนดให้ count = 0
  delay(5000); // หน่วงเวลา 5 วินาที
}




