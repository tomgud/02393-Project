#include <iostream>
#include <string>
#include <vector>
using namespace std;

class vec2d {
private:
	double x,y;
	double get_x() {
		return this->x;
	}
	
	double get_y() {
		return this->y;
	}
public:
	vec2d(double x, double y) {
		this->x = x;
		this->y = y;
	}
	
	
	double operator[] (int i) {
		switch (i) {
			case 0 : return get_x();
			case 1 : return get_y();
			default : 
				cerr << "Index out of bounds\n";
		}
	}
};

int main() {
	vec2d v(3,5);
	cout << "[" << v[0] << "," << v[1] << "]" << endl;
}