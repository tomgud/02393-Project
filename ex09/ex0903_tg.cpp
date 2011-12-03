#include <iostream>
#include <string>
#include <vector>
using namespace std;

int Permute(string soFar, string rest, vector<string> allPerms)
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