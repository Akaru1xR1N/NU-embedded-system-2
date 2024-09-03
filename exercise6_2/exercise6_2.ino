int LED_Pins[] = {10, 11, 12, 13, 6, 7, 8, 9}; // ประกาศตัวแปร LED_Pins เป็น array ของ integer
int pinCount = 8; // กำหนดตัวแปร จำนวน pin = 8
int timer = 1000; // กำหนดตัวแปร timer = 1000

void setup() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++){ // วนลูปตั้งแต่ 0 ถึง 7
    pinMode(LED_Pins[thisPin], OUTPUT); // กำหนด LED_Pins ตัวที่ thisPin เป็น output
  }
}

void loop() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++){ // วนลูปตั้งแต่ 0 ถึง 7
    digitalWrite(LED_Pins[thisPin], HIGH); // กำหนด LED_Pins ตัวที่ thisPin เป็น HIGH
    delay(timer); // delay 1 second
    digitalWrite(LED_Pins[thisPin], LOW); // กำหนด LED_Pins ตัวที่ thisPin เป็น LOW
  }
}



