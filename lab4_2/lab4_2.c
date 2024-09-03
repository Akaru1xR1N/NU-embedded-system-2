#include<reg52.h> // ดึง library เพื่อใช้ควบคุม 8051
#include<stdio.h> // ดึง library เพื่อใช้ส่งข้อความผ่าน serial port

sfr CKCON = 0x8F; // กำหนดตัวแปรชื่อ CKCON เพื่อใช้ปรับความถี่ clock
sbit sw0 = P0^0; // ประกาศตัวแปร sw0 เท่ากับ port p0.0
sbit sw1 = P0^1; // ประกาศตัวแปร sw1 เท่ากับ port p0.1
sbit sw2 = P0^2; // ประกาศตัวแปร sw2 เท่ากับ port p0.2
sbit sw3 = P0^3; // ประกาศตัวแปร sw3 เท่ากับ port p0.3

void delay(unsigned long); // ประกาศ prototype function

void main(){ // ฟังก์ชันหลัก
	CKCON = 0x01; // ตั้งค่าความถี่ clock ให้มีค่ามากกว่าปกติ 2 เท่า (58.9824)
	
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
		if (sw0 == 0){ // ถ้า sw0 == 0
			printf("A"); // ส่งข้อความ A ผ่านทาง serial port
			delay(50000); // ตั้งค่า delay
		}
		else if (sw1 == 0){ // ถ้า sw1 == 0
			printf("B"); // ส่งข้อความ B ผ่านทาง serial port
			delay(50000); // ตั้งค่า delay
		}
		else if (sw2 == 0){ // ถ้า sw2 == 0
			printf("C"); // ส่งข้อความ C ผ่านทาง serial port
			delay(50000); // ตั้งค่า delay
		}
		else if (sw3 == 0){ // ถ้า sw3 == 0
			printf("D"); // ส่งข้อความ D ผ่านทาง serial port
			delay(50000); // ตั้งค่า delay
		}
	}
}

void delay(unsigned long i){ // ฟังก์ชัน delay
	while (i>0){ // วนลูปจนกว่าค่า i จะเท่ากับ 0
		i--; // ลดค่า i ลง 1
	}
	return ; // ไม่ return ค่าอะไรกลับไป
}