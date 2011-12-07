#include <iostream>

using namespace std;

enum directionT {
	North,
	East,
	South,
	West
};

directionT LeftFrom(directionT dir) {
	return directionT((dir+3)%4);
}

directionT RightFrom(directionT dir) {
	return directionT((dir+1)%4);
}

string DirString(directionT dir) {
	switch (dir) {
		case North : return "North";
		case East : return "East";
		case South : return "South";
		case West : return "West";
		default : return "";
		
	}
}

int main() {
	directionT dir = directionT(North);
	
	dir = LeftFrom(dir);
	cout << "Left From North " << DirString(dir) << endl;
	dir = LeftFrom(dir);
	cout << "Left From West " << DirString(dir) << endl;
	dir = LeftFrom(dir);
	cout << "Left From South " << DirString(dir) << endl;
	dir =  LeftFrom(dir);
	cout << "Left From East " << DirString(dir) << endl;
	
	dir = RightFrom(dir);
	cout << "Right From North " << DirString(dir) << endl;
	dir = RightFrom(dir);
	cout << "Right From East " << DirString(dir) << endl;
	dir = RightFrom(dir);
	cout << "Right From South " << DirString(dir) << endl;
	dir =  RightFrom(dir);
	cout << "Right From West " << DirString(dir) << endl;
}