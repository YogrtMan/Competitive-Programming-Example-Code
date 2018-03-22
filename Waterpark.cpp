#include <iostream>
#include <vector>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)

vector<vector<int> > adjMat;
vector<int> dp;

int solve(int node) {
	if (node >= adjMat.size())
		return 0;
	if (node == adjMat.size()-1)
		return 1;
	if (dp[node] == -1) {
		int sum = 0;
		FOR(i, adjMat[node].size())
			sum += solve(adjMat[node][i]);
		dp[node] = sum;
	}
	return dp[node];
}

int main() {
	int n;
	cin >> n;
	adjMat.resize(n);
	dp.assign(n, -1);
	
	while(1) {
		int from, to;
		cin >> from >> to;
		if (!from && !to)
			break;
		adjMat[from-1].push_back(to-1);
	}
	
	cout << solve(0);
}
