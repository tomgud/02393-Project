#include <iostream>
#include <string>
#include <vector>
using namespace std;

void Permute(string soFar, string rest, vector<string> &allPerms)
{
    if (rest == "") { 
		bool dontprint = false;
		for (int i = 0; i < allPerms.size(); ++i) {
			if (soFar == allPerms[i])
				dontprint = true;
		}
		if (!dontprint) {
			cout << soFar + "\n";
			allPerms.push_back(soFar);
		}
    } 
    else {
        for (int i = 0; i < rest.length(); i++) 
        {
            string remaining = rest.substr(0, i) + rest.substr(i+1);
			Permute(soFar + rest[i], remaining, allPerms);
        }
        
    }
}

int main() {
	vector<string> all;
	Permute("", "aabb", all);
	cout << "Number of permutations without duplication: " << all.size() << endl;
}