#include <iostream>
#include <string>
#include <vector>
using namespace std;

class vec2d {
private:
	double **array;
	int cap; // Possible number of elements
	int sz; // Current number of elements 

public:
	vec2d(int capacity=12) {
		this->cap = capacity;
		array = new double*[capacity];
		array[0] = new double[2];
		this->sz = 0;
	}
	
	~vec2d() {
		delete [] array;
	}
	
	double& operator[][] (int i, int j) {
		if (i < this->sz && j < 2) {
			return array[i][j];
		}
		cerr << "Vector index out of bounds \n";
		exit(-1);
	}
	
	void push_back(double x, double y) {
		if (this->sz == this->cap) {
			this->cap *= 2;
			double **tmp_array = new double*[this->cap];
			for (int i =0; i < this->sz; ++i) {
				tmp_array[i] = new double[2];
				tmp_array[i][0] = this->array[i][0];
				tmp_array[i][1] = this->array[i][1];
			}
			delete [] array;
			array = tmp_array;
		}
		this->array[this->sz++][0] = x;
		this->array[this->sz++][1] = y;
	
	}
	
	int size() {
		return this->sz;
	}
	
};

int main() {
	vec2d v;
	cout << v[0][0] << endl;

}