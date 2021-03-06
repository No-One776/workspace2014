//
//  2045 Closest Common Ancestor
//
#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace std;

int main(int argc, const char * argv[]) {
#ifndef ONLINE_JUDGE
	istringstream input("5\n"
			"  5:(3) 1 4 2\n"
			"  1:(0)\n"
			"  4:(0)\n"
			"  2:(1) 3\n"
			"  3:(0)\n"
			"6\n"
			"  (1 5) (1 4) (4 2)\n"
			"  (2 3)\n"
			"  (1 3) (4 3)\n");
#else
	istream& input = cin;
#endif

	unordered_map<int, int> tree;
	unordered_map<int, int> end;
	int ancestor = 0;
	int N;
	while (input >> N) {

		for (int k = 0; k < N; k++) /* read the tree structure */
		{
			char ignore_me;
			int parent, child, num_children;
			input >> parent >> std::ws >> ignore_me >> std::ws >> ignore_me;
			input >> num_children >> std::ws >> ignore_me;
			for (int n = 0; n < num_children; n++) {
				input >> child;
				tree[child] = parent;
			}
		}

		int Npairs;
		input >> Npairs;
		/* read the pair inquiries */
		for (int k = 0; k < Npairs; k++) {
			char ignore_me;
			int n1, n2;
			input >> ws >> ignore_me >> n1 >> n2 >> ws >> ignore_me;
			int parent1 = tree[n1];
			int parent2 = tree[n2];
			int p1 = n1, p2 = n2;
			while (parent1 != parent2) {
				if (parent1 == 0) {
					ancestor = p1;
					break;
				} else if (parent2 == 0) {
					ancestor = p2;
					break;
				} else if (parent1 == n2) {
					ancestor = parent1;
					break;
				} else if (parent2 == n1) {
					ancestor = parent2;
					break;
				} else
					ancestor = parent1;
				p1 = parent1;
				p2 = parent2;
				parent1 = tree[parent1];
				parent2 = tree[parent2];
			}
			end[ancestor]++;
#ifndef ONLINE_JUDGE
			cerr << "Who is the common ancestor of " << n1 << " and " << n2
					<< "? " << ancestor << endl;
#endif
		}
	}
	for (auto x : end)
		cout << x.first << ":" << x.second << endl;
	return 0;
}
