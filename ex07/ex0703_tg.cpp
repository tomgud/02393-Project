#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

class vecNd {
private:
	double *elements;
	int N; // Number of elemnts in this array
public:
	vecNd(int N = 1) {
		elements = new double[N];
	}
	
	int get_N() {
		return this->N;
	}
	
	double operator[] (int i) {
		if (n < this-N) {
			return elements[n];
		}
	}
	
	/* Not done yet
	vecNd add(vecNd &v2) {
		vecNd result(get_x() + v2[0], get_y() + v2[1]);
		return result;
	}
	void mul(double k) {
		this->x *= k;
		this->y *= k;
	}
	double product(vecNd &v2) {
		return (get_x() * v2[0]) + (get_y() * v2[1]);
	}
	
	double length() {
		return sqrt(product(*this));	
	}
	*/
};

int main() {
	vecNd v1(3,5);
	vecNd v2(2,6);
	vecNd v3 = v1.add(v2);
	cout << "v1 [" << v1[0] << "," << v1[1] << "]" << endl;
	cout << "v2 [" << v2[0] << "," << v2[1] << "]" << endl;

	cout << "v3: [" << v3[0] << "," << v3[1] << "]" << endl;
	v1.mul(4.5);
	cout << "v1*(k=4.5): [" << v1[0] << "," << v1[1] << "]" << endl;
	cout << "product(v1, v2) : " << v1.product(v2) << endl;
	cout << "length(v1) : " << v1.length() << endl;
	
}