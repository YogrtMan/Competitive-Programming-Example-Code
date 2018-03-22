#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		vector<string> input(n);
		FOR(i, n)
			cin >> input[i];
			
		vector<string> tree(1, input.back());
		int maxHeight = 0;
		FOR(i, n) {
			if (tree.size() >= 2 && input[i] == tree[tree.size()-2]) {
				tree.pop_back();
			}
			else {
				tree.push_back(input[i]);
			}
			maxHeight = max(maxHeight, int(tree.size()));
		}
		cout << (n-((maxHeight-1)*2))*10 << endl;
	}
}
