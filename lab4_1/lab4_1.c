#include<reg52.h> // ดึง library เพื่อใช้ควบคุม 8051
#include<stdio.h> // ดึง library เพื่อใช้ส่งข้อความผ่าน serial port

sfr CKCON = 0x8F; // กำหนดตัวแปรชื่อ CKCON เพื่อใช้ปรับความถี่ clock

void delay(unsigned long); // ประกาศ prototype function

void main(){ // ฟังก์ชันหลัก
	CKCON = 0x01; // ตั้งค่าความถี่ clock ให้มีค่ามากกว่าปกติ 2 เท่า (58.9824)
	P2 = 0x00; // เซ็ต port P2 ให้เท่ากับ 0 ทุกบิต
	
	/*Initial MCS51 Serial Port */
	// (1) Reset old Timer1 Mode Config
	// (2) Update Timer1 = 8 Bit Auto Reload
	// (3) Serial Port Mode 1 (N,8,1)
	// (4) Disable Serial Interrupt
	// (5) Disable Timer1 Interrupt
	// (6) SMOD1 = 0 (Disable Double Baudrate)
	// (7) Setup Timer1 Baudrate
	// (8) 9600BPS / 58.9824 MHz
	// (9) Start Timer1 Generate Baudrate
	// (10) Set TI to send First char of UART
	TMOD &= 0x0F;
	TMOD |= 0x20;
	SCON = 0x50;
	ES = 0;
	ET1 = 0;
	PCON &= 0x7F;
	TH1 = 0xF0;
	TL1 = 0xF0;
	TR1 = 1;
	TI = 1;
	
	while (1){ // infinite loop
		printf("HELLO\n\r"); // ส่งข้อความผ่าน Serial Port
		delay(100000); // ตั้งค่า delay
	}
}

void delay(unsigned long i){ // ฟังก์ชัน delay
	while (i>0){ // วนลูปจนกว่าค่า i จะเท่ากับ 0
		i--; // ลดค่า i ลง 1
	}
	return ; // ไม่ return ค่าอะไรกลับไป
}