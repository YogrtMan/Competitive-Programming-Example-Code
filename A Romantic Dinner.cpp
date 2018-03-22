#include <iostream>
#include <vector>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)

int M, U, R;
vector<int> impVal, timeVal, foodVal;
vector<vector<vector<long long> > > dp;

long long maxImpVal(int cur, int timeLeft, int unitsEaten) {
	if (cur >= R)
		return 0;
	if (cur == R-1) {
		if (unitsEaten-foodVal[cur] >= 0 && timeLeft-timeVal[cur] >= 0)
			return impVal[cur];
	}
	if (dp[cur][timeLeft][unitsEaten] == -1) {
		dp[cur][timeLeft][unitsEaten] = maxImpVal(cur+1, timeLeft, unitsEaten);
		if (unitsEaten-foodVal[cur] >= 0 && timeLeft-timeVal[cur] >= 0)
			dp[cur][timeLeft][unitsEaten] = max(dp[cur][timeLeft][unitsEaten], maxImpVal(cur+1, timeLeft-timeVal[cur], unitsEaten-foodVal[cur])+impVal[cur]);
	}
	return dp[cur][timeLeft][unitsEaten];
}

int main(){
	cin >> M >> U >> R;

	impVal.resize(R);
	timeVal.resize(R);
	foodVal.resize(R);

	dp.resize(R);
	FOR(i, R) {
		dp[i].resize(M+1);
		FOR(j, M+1) {
			dp[i][j].assign(U+1, -1);
		}
	}

	FOR(i, R) {
		cin >> impVal[i] >> timeVal[i] >> foodVal[i];
	}

	cout << maxImpVal(0, M, U);
}
