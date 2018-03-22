#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)
#define LARGE 1000000
int soul;
vector<int> object;
vector<int> sumArray;
vector<vector<int> > minEnergyAt;

int rangeSum(int l, int r) {
	if (l < 0 || r >= object.size())
		return -1;
	if (l > 0)
		return sumArray[r] - sumArray[l-1];
	else
		return sumArray[r];
}

int minEnergy(int l, int r) {
	if (l > r)
		return LARGE;
	if (l == r)
		return 0;
			
	if (rangeSum(l, r) > soul)
		return LARGE;
	
	if (minEnergyAt[l][r] == -1) {
		if (r - l == 1)
			return minEnergyAt[l][r] = rangeSum(l, r);
			
		minEnergyAt[l][r] = LARGE;
		for (int i = l; i <= r; i++) {
			minEnergyAt[l][r] = min(minEnergy(l, i)+minEnergy(i+1, r), minEnergyAt[l][r]);
		}
		minEnergyAt[l][r] += rangeSum(l, r);
	}
	
	return minEnergyAt[l][r];
}
int main() {
	int n;
	cin >> n >> soul;
	object.resize(n);
	sumArray.resize(n);
	minEnergyAt.resize(n);
	FOR(i, n)
		minEnergyAt[i].assign(n, -1);
		
	FOR(i, n)
		cin >> object[i];
			
	sumArray[0] = object[0];
	for(int i =1; i < n; i++)
		sumArray[i] = sumArray[i-1] + object[i];
	
	if (minEnergy(0, n-1) >= LARGE || minEnergy(0, n-1) == 0)
		cout << "A soul can't be cut" << endl;
	else
		cout << minEnergy(0, n-1) << endl;
}
