void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // ตั้งค่า pin LED_BUILTIN เป็น output
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // กำหนดให้ LED_BUILTIN เป็น HIGH
  delay(1000); // delay 1 second
  digitalWrite(LED_BUILTIN, LOW); // กำหนดให้ LED_BUILTIN เป็น LOW
  delay(1000); // delay 1 second
}












