#include<reg52.h> // ดึง library เพื่อใช้ควบคุม 8051

sfr CKCON = 0x8F; // กำหนดตัวแปรชื่อ CKCON เพื่อใช้ปรับความถี่ clock

void delayms(unsigned long); // ประกาศ prototype function

void main(){ // ฟังก์ชันหลัก
	CKCON = 0x01; // ตั้งค่าความถี่ clock ให้มีค่ามากกว่าปกติ 2 เท่า (58.9824)
	P2 = 0x00; // เซ็ต port P2 ให้เท่ากับ 0 ทุกบิต
	while (1){ // infinite loop
		P2 = 0x01; // เซ็ต port P2 ให้เท่ากับ 00000001
		delayms(1000); // ตั้งค่า delay
		P2 = 0x00; // เซ็ต port P2 ให้เท่ากับ 0 ทุกบิต
		delayms(1000); // ตั้งค่า delay
	}
}

void delayms(unsigned long i){ // ฟังก์ชัน delayms
	while (i>0){ // วนลูปจนกว่าค่า i จะเท่ากับ 0
		TMOD = 0x01; // ตั้งค่า timer mode ให้ใช้ timer 0 mode 1
		// EC77 = 60535 = delay 5000 clock cycle
		TH0 = 0xEC; // ตั้งค่าเวลา
		TL0 = 0x77; // ตั้งค่าเวลา
		TF0 = 0; // clear timer flag
		
		TR0 = 1; // เปิดใช้ timer 0
		
		while (!TF0){
			// เช็คว่าเกิด overflow รึยัง ถ้ายังให้ลูปจนกว่าจะเกิด overflow
		}
		TR0 = 0; // ปิดการใช้งาน timer 0
		TF0 = 0; // clear timer flag
		i--; // ลดค่า i ลง 1
	}
	return ; // ไม่ return ค่าอะไรกลับไป
}