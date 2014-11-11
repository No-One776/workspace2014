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
long hashOf(const string& s) {
	long hash = 0;
	/* Use a polynomial with a prime number (Refer to Section 5.2,
	 * Figure 5.4)
	 */
	for (char c : s)
		hash = 37 * hash + c;
	return hash;
}

int findFirst(const string& pattern, const string& input) {
	/* TODO: Complete this function as described in Question 5.15 */
	long hash1 = hashOf(pattern);
	long hash2 = hashOf(input);
	int length = pattern.length();
	int inputEnd = input.length();
	for (int x = 0; x < inputEnd - length; x++) {
		if (hash1 == hash2) //TODO: Actually figure out how to implement the right compare
			if (pattern.compare(input.substr(x, length)) == 0)
				return x;
	}
	/* Return the position where pattern is found within input,
	 * or return -1 if pattern is not found in the input
	 */
	return -1;
}
