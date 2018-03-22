#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)

vector<int> obstacles;
vector<unsigned long long> sumArray;

int main() {
	int n, m;
	cin >> n >> m;
	obstacles.resize(n);
	sumArray.assign(n, 0);

	FOR(i, n)
		cin >> obstacles[i];
	sumArray[0] = obstacles[0];
	for(int i = 1; i < n; i++)
		sumArray[i] = sumArray[i-1] + obstacles[i];
	FOR(i, m) {
		unsigned long long athletics;
		cin >> athletics;

		vector<unsigned long long>::iterator to = lower_bound(sumArray.begin(), sumArray.end(), athletics+1);
		if ((to - sumArray.begin())+1 > obstacles.size())
			cout << "Success!" << endl;
		else
			cout << (to - sumArray.begin())+1<< endl;
	}	
}
