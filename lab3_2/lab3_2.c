#include<reg52.h> // ดึง library เพื่อใช้ควบคุม 8051

sfr CKCON = 0x8F; // กำหนดตัวแปรชื่อ CKCON เพื่อใช้ปรับความถี่ clock

unsigned char j = 20; // กำหนดตัวแปร j = 20

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
	TMOD = 0x20; // ตั้งค่า timer mode ให้ใช้ timer 1 mode 2
	TH1 = 0x05; // ตั้งค่าเวลา
	// 05 = 5 = 2**8-5 = delay 250 machine cycle
	while (i>0){ // วนลูปจนกว่าค่า i จะเท่ากับ 0
		j = 20; // กำหนดให้ j = 20
		// 250 mc * 20 = 5000 machine cycle
		while (j>0){ // วนลูปจนกว่าค่า j จะเท่ากับ 0
			TF1 = 0; // clear timer flag
			TR1 = 1; // เปิดใช้ timer 1
			while (!TF1){
				// เช็คว่าเกิด overflow รึยัง ถ้ายังให้ลูปจนกว่าจะเกิด overflow
			}
			TF1 = 0; // clear timer flag
			j--; // ลดค่า j ลง 1
		}
		i--; // ลดค่า i ลง 1
	}
	TR1 = 0; // ปิดการใช้งาน timer 1
	return ; // ไม่ return ค่าอะไรกลับไป
}