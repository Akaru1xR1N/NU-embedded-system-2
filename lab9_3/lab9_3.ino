int LED_Pins[] = {2,3,4,5,6,7,8,9}; // กำหนด array ของ pin LED
int pinCount = 8; // กำหนดตัวแปรสำหรับเก็บจำนวนของ LED
int timer = 1000; // กำหนดตัวแปร timer สำหรับหน่วงเวลา

void setup(){
  for (int thisPin = 0; thisPin < pinCount; thisPin++){ // ลูปสำหรับประกาศขา pin เป็น output
    pinMode(LED_Pins[thisPin], OUTPUT); // ตั้งค่าให้ขา pin นั้นๆเป็น output
  }
  Serial.begin(9600); // กำหนด baud rate ของการส่งข้อมูลแบบ serial communication
}

void loop(){
  int R_Volume_Value = analogRead(A0); // อ่านค่าจาก pin A0 เก็บไว้ในตัวแปร R_Volume_Value
  int LDR_Value = analogRead(A1); // อ่านค่าจาก pin A1 เก็บไว้ในตัวแปร LDR_Value

  Serial.print("R_Volume_Value"); // ส่งข้อความว่า R_Volume_Value ผ่าน serial communication
  Serial.print(R_Volume_Value); // ส่งค่าที่อยู่ในตัวแปร R_Volume_Value
  Serial.print(" LDR_Value"); // ส่งข้อความว่า  LDR_Value ผ่าน serial communication
  Serial.println(LDR_Value); // ส่งค่าที่อยู่ในตัวแปร LDR_Value
  delay(200); // หน่วงเวลา 0.2 วินาที

  if (LDR_Value > R_Volume_Value){ // ถ้า LDR_Value มากกว่า R_Volume_Value
    LED_R_to_L(); // เรียกใช้ฟังก์ชั่น LED_R_to_L()
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



