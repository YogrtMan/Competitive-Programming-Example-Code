#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

#define FOR(i, max) for(int i = 0; i < max; i++)

unsigned long long merge(vector<int> &original, const vector<int> &a1, const vector<int> &a2) {
	int i = 0, j = 0, k = 0
	unsigned long long counter = 0;
	while (i < a1.size() && j < a2.size()) {
		if (a1[i] > a2[j]) {
			original[k] = a2[j];
			counter += a1.size()-i;
			j++;
		}
		else {
			original[k] = a1[i];
			i++;
		}
		k++;
	}
	while (i < a1.size()) {
		original[k] = a1[i];
		i++;
		k++;
	}
	while (j < a2.size()) {
		original[k] = a2[j];
		j++;
		k++;
	}
	return counter;
}

unsigned long long numInversions(vector<int> &arr) {
	if (arr.size() <= 1)
		return 0;
	vector<int>::iterator mid = arr.begin()+(arr.size()/2);
	vector<int> a1(arr.begin(), mid), a2(mid, arr.end());
	return numInversions(a1) + numInversions(a2) + merge(arr, a1, a2);
}

//mergesort?
int main() {
	int n;
	cin >> n;
	vector<long> arr(n);
	FOR(i, n)
		cin >> arr[i];
	cout << numInversions(arr);
}
