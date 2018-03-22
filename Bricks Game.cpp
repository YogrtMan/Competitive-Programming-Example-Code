#include <iostream>
#include <vector>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)

vector<int> bricks;
vector<vector<long long> > maxScoreFrom;

long long getMaxScoreFrom(int pos, bool myMove) {
	if (pos >= bricks.size())
		return 0;
 	if (bricks.size()-1-pos <= 2) {
		long long sum = 0;
		for(int i = pos; i < bricks.size(); sum += bricks[i++]){}
		if (myMove)
			return sum;
		else
			return 0;
	}
	if (maxScoreFrom[myMove][pos] == -1) {
		if (myMove) {
			return maxScoreFrom[myMove][pos] = max(
				getMaxScoreFrom(pos+1, !myMove) + bricks[pos], max(
				getMaxScoreFrom(pos+2, !myMove) + bricks[pos]+bricks[pos+1],
				getMaxScoreFrom(pos+3, !myMove) + bricks[pos]+bricks[pos+1]+bricks[pos+2]));
		}
		else {
			return maxScoreFrom[myMove][pos] = min(
				getMaxScoreFrom(pos+1, !myMove), min(
				getMaxScoreFrom(pos+2, !myMove),
				getMaxScoreFrom(pos+3, !myMove)));
		}
	}
	return maxScoreFrom[myMove][pos];
}

int main() {
	maxScoreFrom.resize(2);
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		bricks.resize(n);
		maxScoreFrom[0].assign(n, -1);
		maxScoreFrom[1].assign(n, -1);
		FOR(i, n)
			cin >> bricks[i];
		cout << getMaxScoreFrom(0, true) << endl;
	}
}
