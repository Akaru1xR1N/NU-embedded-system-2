#include<reg52.h> // ดึง library เพื่อใช้ควบคุม 8051

sfr CKCON = 0x8F; // กำหนดตัวแปรชื่อ CKCON เพื่อใช้ปรับความถี่ clock

sbit P0_0 = P0^0; // ประกาศตัวแปร P0_0 เท่ากับ port p0.0
sbit P0_1 = P0^1; // ประกาศตัวแปร P0_1 เท่ากับ port p0.1
sbit P0_2 = P0^2; // ประกาศตัวแปร P0_2 เท่ากับ port p0.2
sbit P0_3 = P0^3; // ประกาศตัวแปร P0_3 เท่ากับ port p0.3
sbit P0_4 = P0^4; // ประกาศตัวแปร P0_4 เท่ากับ port p0.4
sbit P0_5 = P0^5; // ประกาศตัวแปร P0_5 เท่ากับ port p0.5
sbit P0_6 = P0^6; // ประกาศตัวแปร P0_6 เท่ากับ port p0.6
sbit P0_7 = P0^7; // ประกาศตัวแปร P0_7 เท่ากับ port p0.7

unsigned int baseDelayTime = 10000; // กำหนดตัวแปร baseDelayTime
unsigned int delayTime; // กำหนดตัวแปร delayTime

void delay(unsigned long); // ประกาศ prototype function
void blink(unsigned short); // ประกาศ prototype function

void main(){ // ฟังก์ชันหลัก
	unsigned int j; // ประกาศตัวแปร j เป็นจำนวนเต็มบวก
	
	CKCON = 0x01; // ตั้งค่าความถี่ clock ให้มีค่ามากกว่าปกติ 2 เท่า (58.9824)
	
	P2 = 0x00; // เซ็ต port P2 ให้เท่ากับ 0 ทุกบิต
	
	while (1){ // infinite loop
		if (P0_0 || P0_1){ // เมื่อ P0_0 หรือ P0_1 เท่ากับ 1
			for (j=0x01;j<=0x80;j<<=1){
				P2 = j; // กำหนดให้ P2 เท่ากับ j
				delay(50000); // ตั้งค่า delay
			}
		}
		else if (P0_2 || P0_3){ // เมื่อ P0_2 หรือ P0_3 เท่ากับ 1
			for (j=0x80;j>=0x01;j>>=1){
				P2 = j; // กำหนดให้ P2 เท่ากับ j
				delay(50000); // ตั้งค่า delay
			}
		}
		else if (P0_4 || P0_5){ // เมื่อ P0_4 หรือ P0_5 เท่ากับ 1
			blink(2); // ทำให้ไฟกระพริบ 2 ครั้ง
		}
		else if (P0_6 || P0_7){ // เมื่อ P0_6 หรือ P0_7 เท่ากับ 1
			blink(4); // ทำให้ไฟกระพริบ 4 ครั้ง
		}
	}
}

void delay(unsigned long i){ // ฟังก์ชั่น delay
	while (i>0){i--;} // วนลูปจนกว่าค่า i จะเท่ากับ 0
	return ; // ไม่ return ค่าอะไรกลับไป
}

void blink(unsigned short i){ // ฟังก์ชัน delay
	while (i>0){ // วนลูปจนกว่าค่า i จะเท่ากับ 0
		P2 = 0xFF; // กำหนดให้ P2 เท่ากับ FF เพื่อให้ไฟติดทั้งหมด
		delay(25000); // ตั้งค่า delay
		P2 = 0x00; // กำหนดให้ P2 เท่ากับ FF เพื่อให้ไฟดับทั้งหมด
		delay(25000); // ตั้งค่า delay
		i--; // ลดค่า i
	}
	return ; // ไม่ return ค่าอะไรกลับไป
}