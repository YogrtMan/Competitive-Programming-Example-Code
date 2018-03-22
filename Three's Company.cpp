#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)

vector<int> factMod;
typedef unsigned long long ull;

int factorial(int n) {
	if (n == 1)
		return factMod[n] = 1;
		
	if (factMod[n] == -1) {
		factMod[n] = ((n%2017)*factorial(n-1))% 2017;
	}
	return factMod[n];	
}

int main() {
	int n;
	cin >> n;
	factMod.assign(n+1, -1);
	FOR(i, 
}

