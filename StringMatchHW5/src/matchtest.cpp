/*******
 * WARNING!
 * This file must be compiled using the c++11 standard
 */
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <time.h>
#include <cstdlib>
#include <string>

using namespace std;

int findFirst(const string&, const string&);

int next_int(int N) {
	return (int) (rand() * (float) N / RAND_MAX);
}

char next_alpha(bool lowerOnly = false) {
	if (lowerOnly)
		return 'a' + next_int(26);
	else
		return (rand() % 2 ? 'a' : 'A') + next_int(26);
}

string genRandomString(int len, bool lower = false) {
	string text;
	for (int k = 0; k < len; k++)
		text += next_alpha(lower);
	return text;
}

TEST_CASE ("Find in random string")
{
	srand (time(0));
	for (int k = 0; k < 100; k++)
	CHECK (findFirst ("RANDOM", genRandomString(100, true)) == -1);
}

TEST_CASE ("substring match")
{
	srand (time(0));
	const int LEN = 50;
	int count = 0;
	while (count < 100)
	{
		string inp = genRandomString(LEN);
		int pos = next_int(LEN);
		string pat = inp.substr (pos, next_int(11));
		if (inp.find_first_of (pat) == (size_t) pos)
		{
			//cout << "Searching for " << pat << " in " << inp << endl;
			CHECK (pos == findFirst (pat, inp));
			count++;
		}
	}
}

TEST_CASE ("simple match")
{
	CHECK (6 == findFirst ("val", "grand valley"));
	CHECK (-1 == findFirst ("cal", "grand valley"));
}
