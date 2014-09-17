//============================================================================
// Name        : Homework1.cpp
// Author      : Justin Rohr
// Version     : 1.0
// Description : Permutations Recursive Function
//============================================================================

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void perm_helper(const string& in, int i, int n) {
	int j;
	if (i == n)
		cout << in << endl;
	else {
		for (j = i; j <= n; j++) // Otherwise, we've chosen characters a[0] to a[j-1]
				{               // so let's try all possible characters for a[j]
			swap(in[i], in[j]); // Choose which one out of a[j] to a[n] you will choose to swap
			perm_helper(in, i + 1, n);  // Choose the remaining letters
		}
	}
}

void permute(const string& input) {
	perm_helper(input, 0, 0);
}

int main() {
	permute("POSTED"); /* they several different strings */
	return 0;
}

