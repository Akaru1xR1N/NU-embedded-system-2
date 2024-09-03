#include<reg52.h> // ดึง library เพื่อใช้ควบคุม 8051
#include<stdio.h> // ดึง library เพื่อใช้ส่งข้อความผ่าน serial port

sfr CKCON = 0x8F; // กำหนดตัวแปรชื่อ CKCON เพื่อใช้ปรับความถี่ clock
sbit LED0 = P2^0; // ประกาศตัวแปร sw0 เท่ากับ port p0.0
sbit LED1 = P2^1; // ประกาศตัวแปร sw0 เท่ากับ port p0.0
char uart_data; // ประกาศตัวแปรชื่อ uart_data

void delay(unsigned long); // ประกาศ prototype function
void blink0(unsigned short); // ประกาศ prototype function
void blink1(unsigned short); // ประกาศ prototype function

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
	
	P2 = 0x00; // เซ็ต port P2 ให้เท่ากับ 0 ทุกบิต
	
	while (1){ // infinite loop
		uart_data = _getkey(); // รับ input จาก serial port
		if (uart_data == 'A'){ // ถ้า uart_data == 'A'
			blink0(2);
		}
		else if (uart_data == 'B'){ // ถ้า uart_data == 'B'
			blink0(4);
		}
		else if (uart_data == 'C'){ // ถ้า uart_data == 'C'
			blink1(3);
		}
		else if (uart_data == 'D'){ // ถ้า uart_data == 'D'
			blink1(6);
		}
		else if (uart_data == 'F'){ // ถ้า uart_data == 'F'
			blink0(1);
			blink1(1);
			blink0(1);
			blink1(1);
			blink0(1);
			blink1(1);
			blink0(1);
			blink1(1);
			blink0(1);
			blink1(1);
		}
	}
}

void delay(unsigned long i){ // ฟังก์ชัน delay
	while (i>0){ // วนลูปจนกว่าค่า i จะเท่ากับ 0
		i--; // ลดค่า i ลง 1
	}
	return ; // ไม่ return ค่าอะไรกลับไป
}

void blink0(unsigned short i){ // ฟังก์ชัน delay
	while (i>0){ // วนลูปจนกว่าค่า i จะเท่ากับ 0
		LED0 = 1; // กำหนดให้ P2 เท่ากับ FF เพื่อให้ไฟติดทั้งหมด
		delay(25000); // ตั้งค่า delay
		LED0 = 0; // กำหนดให้ P2 เท่ากับ FF เพื่อให้ไฟดับทั้งหมด
		delay(25000); // ตั้งค่า delay
		i--; // ลดค่า i
	}
	return ; // ไม่ return ค่าอะไรกลับไป
}

void blink1(unsigned short i){ // ฟังก์ชัน delay
	while (i>0){ // วนลูปจนกว่าค่า i จะเท่ากับ 0
		LED1 = 1; // กำหนดให้ P2 เท่ากับ FF เพื่อให้ไฟติดทั้งหมด
		delay(25000); // ตั้งค่า delay
		LED1 = 0; // กำหนดให้ P2 เท่ากับ FF เพื่อให้ไฟดับทั้งหมด
		delay(25000); // ตั้งค่า delay
		i--; // ลดค่า i
	}
	return ; // ไม่ return ค่าอะไรกลับไป
}