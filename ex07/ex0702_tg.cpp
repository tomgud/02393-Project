#include <iostream>
#include <string>
#include <vector>
#include <math.h>
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
	vec2d add(vec2d &v2) {
		vec2d result(get_x() + v2[0], get_y() + v2[1]);
		return result;
	}
	void mul(double k) {
		this->x *= k;
		this->y *= k;
	}
	double product(vec2d &v2) {
		return (get_x() * v2[0]) + (get_y() * v2[1]);
	}
	
	double length() {
		return sqrt(product(*this));	
	}
};

int main() {
	vec2d v1(3,5);
	vec2d v2(2,6);
	vec2d v3 = v1.add(v2);
	cout << "v1 [" << v1[0] << "," << v1[1] << "]" << endl;
	cout << "v2 [" << v2[0] << "," << v2[1] << "]" << endl;

	cout << "v3: [" << v3[0] << "," << v3[1] << "]" << endl;
	v1.mul(4.5);
	cout << "v1*(k=4.5): [" << v1[0] << "," << v1[1] << "]" << endl;
	cout << "product(v1, v2) : " << v1.product(v2) << endl;
	cout << "length(v1) : " << v1.length() << endl;
	
}