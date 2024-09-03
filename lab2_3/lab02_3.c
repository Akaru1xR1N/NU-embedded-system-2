#include<reg52.h> // ดึง library เพื่อใช้ควบคุม 8051

sfr CKCON = 0x8F; // กำหนดตัวแปรชื่อ CKCON เพื่อใช้ปรับความถี่ clock

sbit sw0 = P3^2; // กำหนดให้ตัวแปร sw0 เท่ากับ port 3.2
sbit sw1 = P3^3; // กำหนดให้ตัวแปร sw1 เท่ากับ port 3.3

void delay(unsigned long); // ประกาศ prototype function

void main(){ // ฟังก์ชันหลัก
	unsigned int j; // ประกาศตัวแปร j เป็นจำนวนเต็มบวก
	
	CKCON = 0x01; // ตั้งค่าความถี่ clock ให้มีค่ามากกว่าปกติ 2 เท่า (58.9824)
	
	P2 = 0x00; // เซ็ต port P2 ให้เท่ากับ 0 ทุกบิต
	
	while (1){ // infinite loop
		if (sw0 == 0){ // ถ้า sw0 เท่ากับ 0
			for (j=0x01;j<=0x80;j<<=1){ // กำหนดให้ j เลื่อนบิตไปทางซ้ายทีละบิต
				P2 = j; // กำหนดให้ P2 เท่ากับ j
				delay(50000); // ตั้งค่า delay
			}
		}
		if (sw1 == 0){ // ถ้า sw1 เท่ากับ 0
			for (j=0x80;j>=0x01;j>>=1){ // กำหนดให้ j เลื่อนบิตไปทางขวาทีละบิต
				P2 = j; // กำหนดให้ P2 เท่ากับ j
				delay(50000); // ตั้งค่า delay
			}
		}
	}
}

void delay(unsigned long i){ // ฟังก์ชั่น delay
	while (i>0){i--;} // วนลูปจนกว่าค่า i จะเท่ากับ 0
	return ; // ไม่ return ค่าอะไรกลับไป
}