#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)
#define INF 1000000000

vector<int> riceballs;
vector<vector<short> > canCombineAt;
vector<int> sumArray;

int rangeSum(int l, int r) {
	if (l < 0 || r >= riceballs.size())
		return -1;
	if (l > 0)
		return sumArray[r] - sumArray[l-1];
	else
		return sumArray[r];
}

bool canCombine(int l, int r) {
	if (l < 0 || l >= riceballs.size() || r < 0 || r >= riceballs.size() || l > r) {
		return false;
	}
	
	if (canCombineAt[l][r] == -1) {
		canCombineAt[l][r] = false;
		if (l == r) {
			return canCombineAt[l][r] = 1;
		}
		else if (r - l == 1 && riceballs[l] == riceballs[r]) {
			return canCombineAt[l][r] = 1;
		}
		else if (r - l == 2 && riceballs[l] == riceballs[r]) {
			return canCombineAt[l][r] = 1;
		}
		
		int sl = l, sr = r;

		while (sl < sr) {
			if (rangeSum(l, sl) > rangeSum(sr, r))
				sr--;
			else if (rangeSum(l, sl) < rangeSum(sr, r))
				sl++;
			else if (rangeSum(l, sl) == rangeSum(sr, r) && canCombine(l, sl) && canCombine(sl+1, sr-1) && canCombine(sr, r))
				return canCombineAt[l][r] = 1;
			else
				sr--;
		}

		for(int i = l; i <= r; i++) {
			bool cLeft, cRight, cMid;
			
			cLeft = canCombine(l, i);
			cRight = canCombine(i+1, r);
			if (cLeft && cRight && rangeSum(l, i) == rangeSum(i+1, r)) {
				canCombineAt[l][r] = 1;
				break;
			}
		}
	}

	return canCombineAt[l][r];
}

int main() {
	int n;
	cin >> n;
	riceballs.resize(n);
	sumArray.assign(n, 0);
	canCombineAt.resize(n);
	FOR(i, n) {
		canCombineAt[i].assign(n, -1);
	}
	FOR(i, n) {
		cin >> riceballs[i];
		canCombineAt[i][i] = true;
	}
	sumArray[0] = riceballs[0];
	for(int i = 1; i < n; i++)
		sumArray[i] = riceballs[i] + sumArray[i-1];

	int maxSize = 0;
	FOR(i, n) {
		FOR(j, n) {
			if (canCombine(i, j))
				maxSize = max(maxSize, rangeSum(i, j));
		}
	}

	cout << maxSize;
}
