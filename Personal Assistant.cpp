#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)
#define INF 1000000000

vector<pair<long long, int> > startTime;
vector<long long> runTime, happiness;
vector<long long> dp;

long long maxHappiness(int cur) {
//	cout << cur << endl;
	if (cur == startTime.size()-1)
		return happiness[startTime.back().second];
	else if (cur >= startTime.size())
		return 0;

	if (dp[cur] == -1) {
		dp[cur] = max(maxHappiness(cur+1),
			maxHappiness(upper_bound(startTime.begin(), startTime.end(), make_pair(startTime[cur].first+runTime[startTime[cur].second], 0))-startTime.begin())
			+happiness[startTime[cur].second]);
	}
	return dp[cur];
}

int main() {
	int n;
	cin >> n;
	
	startTime.resize(n);
	runTime.resize(n);
	happiness.resize(n);
	dp.assign(n, -1);
	
	FOR(i, n) {
//		cin >> startTime[i].first >> runTime[i] >> happiness[i];
		scanf("%lld %lld %lld", &startTime[i].first, &runTime[i], &happiness[i]);
		startTime[i].second = i;
	}
	sort(startTime.begin(), startTime.end());
	
	printf("%lld", maxHappiness(0));
}
