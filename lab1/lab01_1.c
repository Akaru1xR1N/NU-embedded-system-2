#include<reg52.h> // ดึง library เพื่อใช้ควบคุม 8051

sfr CKCON = 0x8F; // กำหนดตัวแปรชื่อ CKCON เพื่อใช้ปรับความถี่ clock

void delay(unsigned long); // ประกาศ prototype function

void main(){ // ฟังก์ชันหลัก
	unsigned int j; // ประกาศตัวแปร j เป็นจำนวนเต็มบวก
	
	CKCON = 0x01; // ตั้งค่าความถี่ clock ให้มีค่ามากกว่าปกติ 2 เท่า (58.9824)
	
	P2 = 0x00; // เซ็ต port P2 ให้เท่ากับ 0 ทุกบิต
	
	while (1){ // infinite loop
		P2 = 0x01; // เซ็ตให้ P2 บิตที่ 0 เท่ากับ 1
		delay(50000); // ตั้งค่า delay
		P2 = 0x02; // เซ็ตให้ P2 บิตที่ 1 เท่ากับ 1
		delay(50000); // ตั้งค่า delay
		P2 = 0x04; // เซ็ตให้ P2 บิตที่ 2 เท่ากับ 1
		delay(50000); // ตั้งค่า delay
		P2 = 0x08; // เซ็ตให้ P2 บิตที่ 3 เท่ากับ 1
		delay(50000); // ตั้งค่า delay
		P2 = 0x10; // เซ็ตให้ P2 บิตที่ 4 เท่ากับ 1
		delay(50000); // ตั้งค่า delay
		P2 = 0x20; // เซ็ตให้ P2 บิตที่ 5 เท่ากับ 1
		delay(50000); // ตั้งค่า delay
		P2 = 0x40; // เซ็ตให้ P2 บิตที่ 6 เท่ากับ 1
		delay(50000); // ตั้งค่า delay
		P2 = 0x80; // เซ็ตให้ P2 บิตที่ 7 เท่ากับ 1
		delay(50000); // ตั้งค่า delay
	}
}

void delay(unsigned long i){ // ฟังก์ชั่น delay
	while (i>0){i--;} // วนลูปจนกว่าค่า i จะเท่ากับ 0
	return ; // ไม่ return ค่าอะไรกลับไป
}