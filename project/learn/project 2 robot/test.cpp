/*

#include<iostream>
#include<string>
using namespace std;

class Path{
	public:
		string line[][] = {
			{"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10", "A11"},
			{"B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "B10", "B11"},
			{"C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10", "C11"},
			{"D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10", "D11"},
			{"E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "E10", "E11"},
			{"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11"}
		};
		
		string currentPosition;
		string destinationPosition;
		string frontPosition;
		string backPosition;
		string leftPosition;
		string rightPosition;
		
		char direction = 'N';

		string path[20] = {};
		unsigned int lenPath = 0;
		
		Path(string startPosition){
			currentPosition = startPosition;
		}
		
		void setDestination(string position){
			destinationPosition = position;
//			lenPath = findPath();
		}
		
		int findPath(){
			path[0] = '\0';
			lenPath = 0;
			path[lenPath] = currentPosition;
			cout << "Walking in column line." << endl;
			while (1){
				cout << "Current Position: " << currentPosition << endl;
				if (currentPosition[0] > destinationPosition[0]) currentPosition[0] = (char)((int)currentPosition[0] - 1);
				else if (currentPosition[0] < destinationPosition[0]) currentPosition[0] = (char)((int)currentPosition[0] + 1);
				else break;
				lenPath += 1;
				path[lenPath] = currentPosition;
			}
			cout << "\n\n\nWalking in row line." << endl;
			while (1){
				cout << "Current Position: " << currentPosition << endl;
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
				else if (((int)currentPosition[0] - 1) > ((int)'A')) leftPosition = string(1, currentPosition[0]-1) + string(1, currentPosition[1]);
				
				if (((int)currentPosition[0] + 1) > ((int)'K')) rightPosition = "";
				else if (((int)currentPosition[0] + 1) < ((int)'K')) rightPosition = string(1, currentPosition[0]+1) + string(1, currentPosition[1]);
				
				if (((int)currentPosition[1] - 1) < ((int)'1')) frontPosition = "";
				else if (((int)currentPosition[1] + 1) > ((int)'1')) frontPosition = string(1, currentPosition[0]) + string(1, currentPosition[1]-1);
				
				if (((int)currentPosition[1] + 1) > ((int)'6')) backPosition = "";
				else if (((int)currentPosition[1] + 1) < ((int)'6')) backPosition = string(1, currentPosition[0]) + string(1, currentPosition[1]+1);
			}
			else if (direction == 'W'){
				// CONTINUE HERE !!! Just copy and paste
				if (((int)currentPosition[0] - 1) < ((int)'A')) leftPosition = "";
				else if (((int)currentPosition[0] - 1) > ((int)'A')) leftPosition = string(1, currentPosition[0]-1) + string(1, currentPosition[1]);
				
				if (((int)currentPosition[0] + 1) > ((int)'K')) rightPosition = "";
				else if (((int)currentPosition[0] + 1) < ((int)'K')) rightPosition = string(1, currentPosition[0]+1) + string(1, currentPosition[1]);
				
				if (((int)currentPosition[1] - 1) < ((int)'1')) frontPosition = "";
				else if (((int)currentPosition[1] + 1) > ((int)'1')) frontPosition = string(1, currentPosition[0]) + string(1, currentPosition[1]-1);
				
				if (((int)currentPosition[1] + 1) > ((int)'6')) backPosition = "";
				else if (((int)currentPosition[1] + 1) < ((int)'6')) backPosition = string(1, currentPosition[0]) + string(1, currentPosition[1]+1);
			}
			else if (direction == 'S'){
				
			}
			else if (direction == 'E'){
				
			}
		}
		
		void pathTurnLeft(){
			switch (direction){ case 'N': direction = 'W'; case 'W': direction = 'S'; case 'S': direction = 'E'; case 'E': direction = 'N'; }
			
			string temp = frontPosition;
			frontPosition = leftPosition;
			leftPosition = backPosition;
			backPosition = rightPosition;
			rightPosition = temp;
		}
		
		void pathTurnRight(){
			string temp = frontPosition;
			frontPosition = rightPosition;
			rightPosition = backPosition;
			backPosition = leftPosition;
			leftPosition = temp;
		}
		
};

class Car: public Path{
	public:
		unsigned int speed = 255;
		
		Car(string startPosition) : Path(startPosition){
			
		}
		
};

int main(){
	Car myCar("F6");
	myCar.setDestination("A1");
	
	myCar.calculateNearbyPosition();
	cout << "front: " << myCar.frontPosition << endl;
	cout << "left: " << myCar.leftPosition << endl;
	cout << "back: " << myCar.backPosition << endl;
	cout << "right: " << myCar.rightPosition << endl;
	
//	cout << myCar.lenPath << endl;
//	for (int i = 0; i <= myCar.lenPath; i++){
//		cout << myCar.path[i] << endl;
//	}
//	
	
	cout << "\n\nTurn Left!!\n\n" << endl;
	myCar.pathTurnLeft();
//	cout << myCar.currentPosition << endl;
//	cout << myCar.frontPosition << myCar.leftPosition << myCar.backPosition << myCar.rightPosition << endl;
//	myCar.calculateNearbyPosition();
	myCar.calculateNearbyPosition();
	cout << "front: " << myCar.frontPosition << endl;
	cout << "left: " << myCar.leftPosition << endl;
	cout << "back: " << myCar.backPosition << endl;
	cout << "right: " << myCar.rightPosition << endl;
}
*/

#include<iostream>
#include<string>

using namespace std;

string* function();

int main(){
	string* result = function();
	cout << (*(result+0)) << endl;
//	for (int i = 0; i < 6; i++){
//		cout << result[i] << endl;
//	}
}

string* function(){
	string name[6] = {"Hello", "World", "Watashi", "wa", "Buraito", "desu"};
	string *result = name;
	return result;
}