#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

class vecNd {
private:
	double *elements;
	int N; // Number of elemntes allowed in this array
public:
	vecNd(int N = 1) {
		elements = new double[N];
		this->N = N;
	}
	
	int get_N() {
		return this->N;
	}
	
	double operator[] (int i) {
		if (i < this->N) {
			return elements[i];
		}
	}
	void set_elem_at(int i, double val) {
		if (i < this->N) {
			elements[i] = val;
		}
	}
	
	vecNd add(vecNd &v2) {
		int larger = (this->N > v2.get_N()) ? this->N : v2.get_N();
		vecNd result(larger);
		for (int i = 0; i < larger; ++i) {
			result.set_elem_at(i, 
				((this->N > i) ? elements[i] : 0) +
				((v2.get_N() > i ) ? v2[i] : 0));
		}
		 return result;
	}
	
	void mul(double k) {
		for (int i = 0; i < N; ++i) {
			elements[i] *= k;
		}
	}
	double product(vecNd &v2) {
		int smaller = (this->N < v2.get_N()) ? this->N : v2.get_N();
		double result = 0.0;
		for (int i = 0; i < smaller; ++i) {
			result += elements[i] * v2[i];
		}
		return result;

	}
	
	double length() {
		return sqrt(product(*this));	
	}
	
};

int main() {
	vecNd v1(2);
	v1.set_elem_at(0, 3);
	v1.set_elem_at(1, 6);
	vecNd v2(3);
	v2.set_elem_at(0, 2);
	v2.set_elem_at(1, 5);
	v2.set_elem_at(2, 7);
	
	vecNd v3 = v2.add(v1);
	vecNd v4 = v1.add(v2);

	cout << "v1 [" << v1[0] << "," << v1[1] << "]" << endl;
	cout << "v2 [" << v2[0] << "," << v2[1] << "," << v2[2] << "]" << endl;

	cout << "v3: [" << v3[0] << "," << v3[1] << "," << v3[2] << "]" << endl;
	cout << "v4: [" << v4[0] << "," << v4[1] << "," << v4[2] << "]" << endl;

	v1.mul(4.5);
	cout << "v1*(k=4.5): [" << v1[0] << "," << v1[1] << "]" << endl;
	cout << "product(v1, v2) : " << v1.product(v2) << endl;
	cout << "length(v1) : " << v1.length() << endl;
	cout << "length(v3) : " << v3.length() << endl;
	
}