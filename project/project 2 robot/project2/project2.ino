#include<string.h>

class Path{
	public:
		String line[6][11] = {
			{"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10", "A11"},
			{"B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "B10", "B11"},
			{"C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10", "C11"},
			{"D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10", "D11"},
			{"E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "E10", "E11"},
			{"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11"}
		};
		
		String currentPosition;
		String destinationPosition;
		String frontPosition;
		String backPosition;
		String leftPosition;
		String rightPosition;
		
		char direction = 'N';

		String path[20] = {};
		unsigned int lenPath = 0;
		
		Path(String startPosition){
			currentPosition = startPosition;
		}
		
		void setDestination(String position){
			destinationPosition = position;
			lenPath = findPath();
		}
		
		int findPath(){
			path[0] = '\0';
			lenPath = 0;
			path[lenPath] = currentPosition;
			Serial.println("Walking in column line.");
			while (1){
        Serial.print("Current Position: ");
        Serial.println(currentPosition);
				if (currentPosition[0] > destinationPosition[0]) currentPosition[0] = (char)((int)currentPosition[0] - 1);
				else if (currentPosition[0] < destinationPosition[0]) currentPosition[0] = (char)((int)currentPosition[0] + 1);
				else break;
				lenPath += 1;
				path[lenPath] = currentPosition;
			}
			Serial.println("\n\n\nWalking in row line.");
			while (1){
        Serial.print("Current Position: ");
        Serial.println(currentPosition);
				if (currentPosition[1] > destinationPosition[1]) currentPosition[1] = (char)((int)currentPosition[1] - 1);
				else if (currentPosition[1] < destinationPosition[1]) currentPosition[1] = (char)((int)currentPosition[1] + 1);
				else break;
				lenPath += 1;
				path[lenPath] = currentPosition;
			}
			return lenPath;
		}
		
		void calculateNearbyPosition(){
			if (direction == 'N'){
				if (((int)currentPosition[0] - 1) < ((int)'A')) leftPosition = "";
				else if (((int)currentPosition[0] - 1) > ((int)'A')) leftPosition = String(String((char)(currentPosition[0]-1)) + String((char)(currentPosition[1])));
				
				if (((int)currentPosition[0] + 1) > ((int)'K')) rightPosition = "";
				else if (((int)currentPosition[0] + 1) < ((int)'K')) rightPosition = String(String((char)(currentPosition[0]+1)) + String((char)(currentPosition[1])));
				
				if (((int)currentPosition[1] - 1) < ((int)'1')) frontPosition = "";
				else if (((int)currentPosition[1] + 1) > ((int)'1')) frontPosition = String(String((char)(currentPosition[0])) + String((char)(currentPosition[1]-1)));
				
				if (((int)currentPosition[1] + 1) > ((int)'6')) backPosition = "";
				else if (((int)currentPosition[1] + 1) < ((int)'6')) backPosition = String(String((char)(currentPosition[0])) + String((char)(currentPosition[1]+1)));
			}
			else if (direction == 'W'){
				// CONTINUE HERE !!! Just copy and paste
				if (((int)currentPosition[0] - 1) < ((int)'A')) leftPosition = "";
				else if (((int)currentPosition[0] - 1) > ((int)'A')) leftPosition = String(String(currentPosition[0]-1) + String(currentPosition[1]));
				
				if (((int)currentPosition[0] + 1) > ((int)'K')) rightPosition = "";
				else if (((int)currentPosition[0] + 1) < ((int)'K')) rightPosition = String(String(currentPosition[0]+1) + String(currentPosition[1]));
				
				if (((int)currentPosition[1] - 1) < ((int)'1')) frontPosition = "";
				else if (((int)currentPosition[1] + 1) > ((int)'1')) frontPosition = String(String(currentPosition[0]) + String(currentPosition[1]-1));
				
				if (((int)currentPosition[1] + 1) > ((int)'6')) backPosition = "";
				else if (((int)currentPosition[1] + 1) < ((int)'6')) backPosition = String(String(currentPosition[0]) + String(currentPosition[1]+1));
			}
			else if (direction == 'S'){
				
			}
			else if (direction == 'E'){
				
			}
		}
		
		void pathTurnLeft(){
			switch (direction){ case 'N': direction = 'W'; case 'W': direction = 'S'; case 'S': direction = 'E'; case 'E': direction = 'N'; }
			
			String temp = frontPosition;
			frontPosition = leftPosition;
			leftPosition = backPosition;
			backPosition = rightPosition;
			rightPosition = temp;
		}
		
		void pathTurnRight(){
			String temp = frontPosition;
			frontPosition = rightPosition;
			rightPosition = backPosition;
			backPosition = leftPosition;
			leftPosition = temp;
		}
		
};

class Car: public Path{
	public:
		unsigned int speed = 255;
		
		Car(String startPosition) : Path(startPosition){
			
		}
		
};

void setup(){
  Serial.begin(9600);
	Car myCar("F6");
	myCar.setDestination("C2");
	
	myCar.calculateNearbyPosition();
  Serial.print("front: ");
  Serial.println(myCar.frontPosition);
  Serial.print("left: ");
  Serial.println(myCar.leftPosition);
  Serial.print("back: ");
  Serial.println(myCar.backPosition);
  Serial.print("right: ");
  Serial.println(myCar.rightPosition);
	
//	cout << myCar.lenPath << endl;
//	for (int i = 0; i <= myCar.lenPath; i++){
//		cout << myCar.path[i] << endl;
//	}
//	
	
	Serial.println("\n\nTurn Left!!\n\n");
	myCar.pathTurnLeft();
//	cout << myCar.currentPosition << endl;
//	cout << myCar.frontPosition << myCar.leftPosition << myCar.backPosition << myCar.rightPosition << endl;
//	myCar.calculateNearbyPosition();
	myCar.calculateNearbyPosition();
  Serial.print("front: ");
  Serial.println(myCar.frontPosition);
  Serial.print("left: ");
  Serial.println(myCar.leftPosition);
  Serial.print("back: ");
  Serial.println(myCar.backPosition);
  Serial.print("right: ");
  Serial.println(myCar.rightPosition);
}

void loop(){

}
