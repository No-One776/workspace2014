/*
 * stringmatch.cpp
 *
 * Justin Rohr, Alex Zurek, & Alex Banker
 */

#include <string>
#include <iostream>
#include <math.h>
using namespace std;
const int PRIME_BASE = 53;  // 37 in the textbook
long long hashOf(const string& s) {
	long long hash;
	for (auto x = s.rbegin(); x < s.rend(); x++)
		hash = PRIME_BASE * hash + *x;
	return hash;
}

int findFirst(const string& pattern, const string& input) {
	long long matchHash = hashOf(pattern);
	int length = pattern.length();
	int end = input.length() - length;
	//if (end < 0 || length < 0)
	//	return -1;
	long long hash2 = hashOf(input.substr(0, length));
	for (int x = 0; x <= end; x++) {
		cout << matchHash << " = " << hash2 << endl;
		if (matchHash == hash2)
			if (pattern.compare(input.substr(x, length)) == 0)
				return x;
		// newHash = [Prime_base * (oldHash - (oldChar * Prime_base ^ (length-1))] + newChar
		hash2 = hash2 - (input[x] * (long long) pow(PRIME_BASE, length - 1));
		hash2 = (PRIME_BASE * hash2) + input[x + length];
	}

	return -1;
}

