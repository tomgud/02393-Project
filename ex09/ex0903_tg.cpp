#include <iostream>
#include <string>
using namespace std;

int Permute(string soFar, string rest)
{
	int val = 0;
    if (rest == "") { 
        cout << soFar + "\n";
    } 
    else {
        for (int i = 0; i < rest.length(); i++) 
        {
            string remaining = rest.substr(0, i) + rest.substr(i+1);
			val += remaining.length();
			Permute(soFar + rest[i], remaining);
			
        }
        return val;
    }
}

int main() {
	cout << Permute("", "abc");
}