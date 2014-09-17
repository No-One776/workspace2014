//============================================================================
// Name        : HW1.cpp
// Author      : Justin Rohr
// Version     : 1.0
// Description : Permutations Recursive Function
//============================================================================

#include <iostream>
#include <sstream>
#include <string>

using namespace std;
void perm_helper(string in, int i, int n) {
	int j;
	if (i == n)
		cout << in << endl;  //Output the Permutation
	else {
		for (j = i; j < n; j++) {
			swap(in[i], in[j]); // Choose which one out of a[j] to a[n] you will choose to swap
			perm_helper(in, i + 1, n);  // Choose the remaining letters
		}
	}
}
void permute(const string& input) {
	perm_helper(input, 0, input.length());
}
int main() {
	permute("EAT"); /* they several different strings */
	return 0;
}

