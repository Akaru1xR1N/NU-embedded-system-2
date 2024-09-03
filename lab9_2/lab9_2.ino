void setup(){
  Serial.begin(9600); // กำหนด baud rate ของการส่งข้อมูลแบบ serial communication
}

void loop(){
  int sensorValue = analogRead(A1); // อ่านค่าจาก pin A1 เก็บไว้ในตัวแปร sensorValue
  Serial.println(sensorValue); // ส่งค่าที่อยู่ในตัวแปร sensorValue
  delay(200); // หน่วงเวลา 0.2 วินาที
}



