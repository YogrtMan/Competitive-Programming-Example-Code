#include <iostream>
#include <vector>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, k, w;
		cin >> n >> k >> w;

		vector<int> scorePerWidth(n, 0);

		FOR(i, n) {
			int points;
			cin >> points;
			for(int j = 0; j < w && i-j >= 0; j++) {
				scorePerWidth[i-j] += points;
			}
		}

		vector<vector<int> > dp(k);
		
		for (int i = 0; i < k; i++) {
			dp[i].resize(n);
			for (int j = n-1; j >= 0; j--) {
				dp[i][j] = max(
					(j+1 < n ? dp[i][j+1] : 0),
					scorePerWidth[j] + (j+w < n && i-1 >= 0 ? dp[i-1][j+w] : 0));
			}
		}
		cout << dp[k-1][0] << endl;
	}
}
